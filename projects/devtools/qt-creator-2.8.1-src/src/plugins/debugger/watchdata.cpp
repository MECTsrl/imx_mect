/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

// NOTE: Don't add dependencies to other files.
// This is used in the debugger auto-tests.

#include "watchdata.h"
#include "watchutils.h"
#include "debuggerprotocol.h"

#include <QTextDocument> // Qt::escape() in Qt 4
#include <QDebug>

////////////////////////////////////////////////////////////////////
//
// WatchData
//
////////////////////////////////////////////////////////////////////

namespace Debugger {
namespace Internal {

bool isPointerType(const QByteArray &type)
{
    return type.endsWith('*') || type.endsWith("* const");
}

bool isCharPointerType(const QByteArray &type)
{
    return type == "char *" || type == "const char *" || type == "char const *";
}

bool isIntType(const QByteArray &type)
{
    if (type.isEmpty())
        return false;
    switch (type.at(0)) {
        case 'b':
            return type == "bool";
        case 'c':
            return type == "char";
        case 'i':
            return type == "int";
        case 'l':
            return type == "long"
                || type == "long int"
                || type == "long unsigned int";
        case 'p':
            return type == "ptrdiff_t";
        case 'q':
            return type == "qint16" || type == "quint16"
                || type == "qint32" || type == "quint32"
                || type == "qint64" || type == "quint64"
                || type == "qlonglong" || type == "qulonglong";
        case 's':
            return type == "short"
                || type == "signed"
                || type == "size_t"
                || type == "std::size_t"
                || type == "std::ptrdiff_t"
                || (type.startsWith("signed") &&
                    (  type == "signed char"
                    || type == "signed short"
                    || type == "signed short int"
                    || type == "signed long"
                    || type == "signed long int"
                    || type == "signed long long"
                    || type == "signed long long int"));
        case 'u':
            return type == "unsigned"
                || (type.startsWith("unsigned") &&
                    (  type == "unsigned char"
                    || type == "unsigned short"
                    || type == "unsigned short int"
                    || type == "unsigned long"
                    || type == "unsigned long int"
                    || type == "unsigned long long"
                    || type == "unsigned long long int"));
        default:
            return false;
    }
}

bool isFloatType(const QByteArray &type)
{
    return type == "float" || type == "double" || type == "qreal";
}

bool isIntOrFloatType(const QByteArray &type)
{
    return isIntType(type) || isFloatType(type);
}

WatchData::WatchData() :
    id(0),
    state(InitialState),
    editformat(0),
    address(0),
    origaddr(0),
    size(0),
    bitpos(0),
    bitsize(0),
    hasChildren(false),
    valueEnabled(true),
    valueEditable(true),
    error(false),
    sortId(0),
    source(0)
{
}

bool WatchData::isEqual(const WatchData &other) const
{
    return iname == other.iname
      && exp == other.exp
      && name == other.name
      && value == other.value
      && editvalue == other.editvalue
      && valuetooltip == other.valuetooltip
      && type == other.type
      && displayedType == other.displayedType
      && variable == other.variable
      && address == other.address
      && size == other.size
      && hasChildren == other.hasChildren
      && valueEnabled == other.valueEnabled
      && valueEditable == other.valueEditable
      && error == other.error;
}

bool WatchData::isVTablePointer() const
{
    // First case: Cdb only. No user type can be named like this, this is safe.
    // Second case: Python dumper only.
    return type.startsWith("__fptr()")
        || (type.isEmpty() && name == QLatin1String("[vptr]"));
}

void WatchData::setError(const QString &msg)
{
    setAllUnneeded();
    value = msg;
    setHasChildren(false);
    valueEnabled = false;
    valueEditable = false;
    error = true;
}

void WatchData::setValue(const QString &value0)
{
    value = value0;
    if (value == QLatin1String("{...}")) {
        value.clear();
        hasChildren = true; // at least one...
    }
    // strip off quoted characters for chars.
    if (value.endsWith(QLatin1Char('\'')) && type.endsWith("char")) {
        const int blankPos = value.indexOf(QLatin1Char(' '));
        if (blankPos != -1)
            value.truncate(blankPos);
    }

    // avoid duplicated information
    if (value.startsWith(QLatin1Char('(')) && value.contains(QLatin1String(") 0x")))
        value.remove(0, value.lastIndexOf(QLatin1String(") 0x")) + 2);

    // doubles are sometimes displayed as "@0x6141378: 1.2".
    // I don't want that.
    if (/*isIntOrFloatType(type) && */ value.startsWith(QLatin1String("@0x"))
         && value.contains(QLatin1Char(':'))) {
        value.remove(0, value.indexOf(QLatin1Char(':')) + 2);
        setHasChildren(false);
    }

    // "numchild" is sometimes lying
    //MODEL_DEBUG("\n\n\nPOINTER: " << type << value);
    if (isPointerType(type))
        setHasChildren(value != QLatin1String("0x0") && value != QLatin1String("<null>")
            && !isCharPointerType(type));

    // pointer type information is available in the 'type'
    // column. No need to duplicate it here.
    if (value.startsWith(QLatin1Char('(') + QLatin1String(type) + QLatin1String(") 0x")))
        value = value.section(QLatin1Char(' '), -1, -1);

    setValueUnneeded();
}

enum GuessChildrenResult { HasChildren, HasNoChildren, HasPossiblyChildren };

static GuessChildrenResult guessChildren(const QByteArray &type)
{
    if (isIntOrFloatType(type))
        return HasNoChildren;
    if (isCharPointerType(type))
        return HasNoChildren;
    if (isPointerType(type))
        return HasChildren;
    if (type.endsWith("QString"))
        return HasNoChildren;
    return HasPossiblyChildren;
}

void WatchData::setType(const QByteArray &str, bool guessChildrenFromType)
{
    type = str.trimmed();
    bool changed = true;
    while (changed) {
        if (type.endsWith("const"))
            type.chop(5);
        else if (type.endsWith(' '))
            type.chop(1);
        else if (type.startsWith("const "))
            type = type.mid(6);
        else if (type.startsWith("volatile "))
            type = type.mid(9);
        else if (type.startsWith("class "))
            type = type.mid(6);
        else if (type.startsWith("struct "))
            type = type.mid(6);
        else if (type.startsWith(' '))
            type = type.mid(1);
        else
            changed = false;
    }
    setTypeUnneeded();
    if (guessChildrenFromType) {
        switch (guessChildren(type)) {
        case HasChildren:
            setHasChildren(true);
            break;
        case HasNoChildren:
            setHasChildren(false);
            break;
        case HasPossiblyChildren:
            setHasChildren(true); // FIXME: bold assumption
            break;
        }
    }
}

void WatchData::setHexAddress(const QByteArray &a)
{
    bool ok;
    const qint64 av = a.toULongLong(&ok, 0);
    if (ok) {
        address = av;
    } else {
        qWarning("WatchData::setHexAddress(): Failed to parse address value '%s' for '%s', '%s'",
                 a.constData(), iname.constData(), type.constData());
        address = 0;
    }
}

QString WatchData::toString() const
{
    const char *doubleQuoteComma = "\",";
    QString res;
    QTextStream str(&res);
    str << QLatin1Char('{');
    if (!iname.isEmpty())
        str << "iname=\"" << iname << doubleQuoteComma;
    str << "sortId=\"" << sortId << doubleQuoteComma;
    if (!name.isEmpty() && name != QLatin1String(iname))
        str << "name=\"" << name << doubleQuoteComma;
    if (error)
        str << "error,";
    if (address) {
        str.setIntegerBase(16);
        str << "addr=\"0x" << address << doubleQuoteComma;
        str.setIntegerBase(10);
    }
    if (origaddr) {
        str.setIntegerBase(16);
        str << "referencingaddr=\"0x" << origaddr << doubleQuoteComma;
        str.setIntegerBase(10);
    }
    if (!exp.isEmpty())
        str << "exp=\"" << exp << doubleQuoteComma;

    if (!variable.isEmpty())
        str << "variable=\"" << variable << doubleQuoteComma;

    if (isValueNeeded())
        str << "value=<needed>,";
    if (isValueKnown() && !value.isEmpty())
        str << "value=\"" << value << doubleQuoteComma;

    if (!editvalue.isEmpty())
        str << "editvalue=\"<...>\",";
    //    str << "editvalue=\"" << editvalue << doubleQuoteComma;

    if (!dumperFlags.isEmpty())
        str << "dumperFlags=\"" << dumperFlags << doubleQuoteComma;

    if (isTypeNeeded())
        str << "type=<needed>,";
    if (isTypeKnown() && !type.isEmpty())
        str << "type=\"" << type << doubleQuoteComma;

    if (isHasChildrenNeeded())
        str << "hasChildren=<needed>,";
    if (isHasChildrenKnown())
        str << "hasChildren=\"" << (hasChildren ? "true" : "false") << doubleQuoteComma;

    if (isChildrenNeeded())
        str << "children=<needed>,";
    str.flush();
    if (res.endsWith(QLatin1Char(',')))
        res.truncate(res.size() - 1);
    return res + QLatin1Char('}');
}

// Format a tooltip fow with aligned colon.
static void formatToolTipRow(QTextStream &str,
    const QString &category, const QString &value)
{
    QString val = Qt::escape(value);
    val.replace(QLatin1Char('\n'), QLatin1String("<br>"));
    str << "<tr><td>" << category << "</td><td> : </td><td>"
        << val << "</td></tr>";
}

QString WatchData::toToolTip() const
{
    QString res;
    QTextStream str(&res);
    str << "<html><body><table>";
    formatToolTipRow(str, tr("Name"), name);
    formatToolTipRow(str, tr("Expression"), QLatin1String(exp));
    formatToolTipRow(str, tr("Internal Type"), QLatin1String(type));
    if (!displayedType.isEmpty())
        formatToolTipRow(str, tr("Displayed Type"), displayedType);
    QString val = valuetooltip.isEmpty() ? value : valuetooltip;
    // Automatically display hex value for unsigned integers.
    if (!val.isEmpty() && val.at(0).isDigit() && isIntType(type)) {
        bool ok;
        const quint64 intValue = val.toULongLong(&ok);
        if (ok && intValue)
            val += QLatin1String(" (hex) ") + QString::number(intValue, 16);
    }
    if (val.size() > 1000) {
        val.truncate(1000);
        val += tr(" ... <cut off>");
    }
    formatToolTipRow(str, tr("Value"), val);
    if (address)
        formatToolTipRow(str, tr("Object Address"), formatToolTipAddress(address));
    if (origaddr)
        formatToolTipRow(str, tr("Pointer Address"), formatToolTipAddress(origaddr));
    if (size)
        formatToolTipRow(str, tr("Static Object Size"), tr("%n bytes", 0, size));
    formatToolTipRow(str, tr("Internal ID"), QLatin1String(iname));
    str << "</table></body></html>";
    return res;
}

QString WatchData::msgNotInScope()
{
    //: Value of variable in Debugger Locals display for variables out
    //: of scope (stopped above initialization).
    static const QString rc =
        QCoreApplication::translate("Debugger::Internal::WatchData", "<not in scope>");
    return rc;
}

const QString &WatchData::shadowedNameFormat()
{
    //: Display of variables shadowed by variables of the same name
    //: in nested scopes: Variable %1 is the variable name, %2 is a
    //: simple count.
    static const QString format =
        QCoreApplication::translate("Debugger::Internal::WatchData", "%1 <shadowed %2>");
    return format;
}

QString WatchData::shadowedName(const QString &name, int seen)
{
    if (seen <= 0)
        return name;
    return shadowedNameFormat().arg(name).arg(seen);
}

QByteArray WatchData::hexAddress() const
{
    if (address)
        return QByteArray("0x") + QByteArray::number(address, 16);
    return QByteArray();
}


////////////////////////////////////////////////////
//
// Protocol convienience
//
////////////////////////////////////////////////////

void WatchData::updateValue(const GdbMi &item)
{
    GdbMi value = item["value"];
    if (value.isValid()) {
        int encoding = item["valueencoded"].toInt();
        setValue(decodeData(value.data(), encoding));
    } else {
        setValueNeeded();
    }
}

void setWatchDataValueToolTip(WatchData &data, const GdbMi &mi,
    int encoding)
{
    if (mi.isValid())
        data.valuetooltip = decodeData(mi.data(), encoding);
}

void WatchData::updateChildCount(const GdbMi &mi)
{
    if (mi.isValid())
        setHasChildren(mi.toInt() > 0);
}

static void setWatchDataValueEnabled(WatchData &data, const GdbMi &mi)
{
    if (mi.data() == "true")
        data.valueEnabled = true;
    else if (mi.data() == "false")
        data.valueEnabled = false;
}

static void setWatchDataValueEditable(WatchData &data, const GdbMi &mi)
{
    if (mi.data() == "true")
        data.valueEditable = true;
    else if (mi.data() == "false")
        data.valueEditable = false;
}

static void setWatchDataAddress(WatchData &data, quint64 address)
{
    data.address = address;

    if (data.exp.isEmpty() && !data.dumperFlags.startsWith('$')) {
        if (data.iname.startsWith("local.") && data.iname.count('.') == 1)
            // Solve one common case of adding 'class' in
            // *(class X*)0xdeadbeef for gdb.
            data.exp = data.name.toLatin1();
        else
            data.exp = "*(" + gdbQuoteTypes(data.type) + "*)" + data.hexAddress();
    }
}

void WatchData::updateAddress(const GdbMi &mi)
{
    if (!mi.isValid())
        return;
    const QByteArray addressBA = mi.data();
    if (!addressBA.startsWith("0x")) { // Item model dumpers pull tricks.
        dumperFlags = addressBA;
        return;
    }
    const quint64 address = mi.toAddress();
    setWatchDataAddress(*this, address);
}

static void setWatchDataSize(WatchData &data, const GdbMi &mi)
{
    if (mi.isValid()) {
        bool ok = false;
        const unsigned size = mi.data().toUInt(&ok);
        if (ok)
            data.size = size;
    }
}

// Find the "type" and "displayedtype" children of root and set up type.
void WatchData::updateType(const GdbMi &item)
{
    if (item.isValid())
        setType(item.data());
    else if (type.isEmpty())
        setTypeNeeded();
}

void WatchData::updateDisplayedType(const GdbMi &item)
{
    if (item.isValid())
        displayedType = QString::fromLatin1(item.data());
}

// Utilities to decode string data returned by the dumper helpers.


template <class T>
void decodeArrayHelper(QList<WatchData> *list, const WatchData &tmplate,
    const QByteArray &rawData)
{
    const QByteArray ba = QByteArray::fromHex(rawData);
    const T *p = (const T *) ba.data();
    WatchData data;
    const QByteArray exp = "*(" + gdbQuoteTypes(tmplate.type) + "*)0x";
    for (int i = 0, n = ba.size() / sizeof(T); i < n; ++i) {
        data = tmplate;
        data.sortId = i;
        data.iname += QByteArray::number(i);
        data.name = QString::fromLatin1("[%1]").arg(i);
        data.value = QString::number(p[i]);
        data.address += i * sizeof(T);
        data.exp = exp + QByteArray::number(data.address, 16);
        data.setAllUnneeded();
        list->append(data);
    }
}

static void decodeArray(QList<WatchData> *list, const WatchData &tmplate,
    const QByteArray &rawData, int encoding)
{
    switch (encoding) {
        case Hex2EncodedInt1:
            decodeArrayHelper<signed char>(list, tmplate, rawData);
            break;
        case Hex2EncodedInt2:
            decodeArrayHelper<short>(list, tmplate, rawData);
            break;
        case Hex2EncodedInt4:
            decodeArrayHelper<int>(list, tmplate, rawData);
            break;
        case Hex2EncodedInt8:
            decodeArrayHelper<qint64>(list, tmplate, rawData);
            break;
        case Hex2EncodedUInt1:
            decodeArrayHelper<uchar>(list, tmplate, rawData);
            break;
        case Hex2EncodedUInt2:
            decodeArrayHelper<ushort>(list, tmplate, rawData);
            break;
        case Hex2EncodedUInt4:
            decodeArrayHelper<uint>(list, tmplate, rawData);
            break;
        case Hex2EncodedUInt8:
            decodeArrayHelper<quint64>(list, tmplate, rawData);
            break;
        case Hex2EncodedFloat4:
            decodeArrayHelper<float>(list, tmplate, rawData);
            break;
        case Hex2EncodedFloat8:
            decodeArrayHelper<double>(list, tmplate, rawData);
            break;
        default:
            qDebug() << "ENCODING ERROR: " << encoding;
    }
}

void parseWatchData(const QSet<QByteArray> &expandedINames,
    const WatchData &data0, const GdbMi &item,
    QList<WatchData> *list)
{
    //qDebug() << "HANDLE CHILDREN: " << data0.toString() << item.toString();
    WatchData data = data0;
    bool isExpanded = expandedINames.contains(data.iname);
    if (!isExpanded)
        data.setChildrenUnneeded();

    GdbMi children = item["children"];
    if (children.isValid() || !isExpanded)
        data.setChildrenUnneeded();

    data.updateType(item["type"]);
    GdbMi mi = item["editvalue"];
    if (mi.isValid())
        data.editvalue = mi.data();

    mi = item["editformat"];
    if (mi.isValid())
        data.editformat = mi.toInt();

    mi = item["typeformats"];
    if (mi.isValid())
        data.typeFormats = QString::fromUtf8(mi.data());

    mi = item["bitpos"];
    if (mi.isValid())
        data.bitpos = mi.toInt();

    mi = item["bitsize"];
    if (mi.isValid())
        data.bitsize = mi.toInt();

    mi = item["origaddr"];
    if (mi.isValid())
        data.origaddr = mi.toAddress();

    data.updateAddress(item["addr"]);
    data.updateValue(item);

    setWatchDataSize(data, item["size"]);

    mi = item["exp"];
    if (mi.isValid())
        data.exp = mi.data();

    setWatchDataValueEnabled(data, item["valueenabled"]);
    setWatchDataValueEditable(data, item["valueeditable"]);
    data.updateChildCount(item["numchild"]);
    //qDebug() << "\nAPPEND TO LIST: " << data.toString() << "\n";
    list->append(data);

    bool ok = false;
    qulonglong addressBase = item["addrbase"].data().toULongLong(&ok, 0);
    qulonglong addressStep = item["addrstep"].data().toULongLong(&ok, 0);

    // Try not to repeat data too often.
    WatchData childtemplate;
    childtemplate.updateType(item["childtype"]);
    childtemplate.updateChildCount(item["childnumchild"]);
    //qDebug() << "CHILD TEMPLATE:" << childtemplate.toString();

    mi = item["arraydata"];
    if (mi.isValid()) {
        int encoding = item["arrayencoding"].toInt();
        childtemplate.iname = data.iname + '.';
        childtemplate.address = addressBase;
        decodeArray(list, childtemplate, mi.data(), encoding);
    } else {
        for (int i = 0, n = children.children().size(); i != n; ++i) {
            const GdbMi &child = children.children().at(i);
            WatchData data1 = childtemplate;
            data1.sortId = i;
            GdbMi name = child["name"];
            if (name.isValid())
                data1.name = QString::fromLatin1(name.data());
            else
                data1.name = QString::number(i);
            GdbMi iname = child["iname"];
            if (iname.isValid()) {
                data1.iname = iname.data();
            } else {
                data1.iname = data.iname;
                data1.iname += '.';
                data1.iname += data1.name.toLatin1();
            }
            if (!data1.name.isEmpty() && data1.name.at(0).isDigit())
                data1.name = QLatin1Char('[') + data1.name + QLatin1Char(']');
            if (addressStep) {
                setWatchDataAddress(data1, addressBase);
                addressBase += addressStep;
            }
            QByteArray key = child["key"].data();
            if (!key.isEmpty()) {
                int encoding = child["keyencoded"].toInt();
                data1.name = decodeData(key, encoding);
            }
            parseWatchData(expandedINames, data1, child, list);
        }
    }
}

} // namespace Internal
} // namespace Debugger

