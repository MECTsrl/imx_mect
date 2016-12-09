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

#include "cmakevalidator.h"

#include <QProcess>
#include <QFileInfo>
#include <QTextDocument>

using namespace CMakeProjectManager::Internal;

///////////////////////////
// CMakeValidator
///////////////////////////
CMakeValidator::CMakeValidator()
    : m_state(Invalid), m_process(0), m_hasCodeBlocksMsvcGenerator(false), m_hasCodeBlocksNinjaGenerator(false)
{

}

CMakeValidator::~CMakeValidator()
{
    cancel();
}

void CMakeValidator::cancel()
{
    if (m_process) {
        disconnect(m_process, SIGNAL(finished(int)));
        m_process->waitForFinished();
        delete m_process;
        m_process = 0;
    }
}

void CMakeValidator::setCMakeExecutable(const QString &executable)
{
    cancel();
    m_process = new QProcess();
    connect(m_process, SIGNAL(finished(int)),
            this, SLOT(finished(int)));

    m_executable = executable;
    QFileInfo fi(m_executable);
    if (fi.exists() && fi.isExecutable()) {
        // Run it to find out more
        m_state = CMakeValidator::RunningBasic;
        if (!startProcess(QStringList(QLatin1String("--help"))))
            m_state = CMakeValidator::Invalid;
    } else {
        m_state = CMakeValidator::Invalid;
    }
}

void CMakeValidator::finished(int exitCode)
{
    if (exitCode) {
        m_state = CMakeValidator::Invalid;
        return;
    }
    if (m_state == CMakeValidator::RunningBasic) {
        QByteArray response = m_process->readAll();
        QRegExp versionRegexp(QLatin1String("^cmake version ([\\d\\.]*)"));
        versionRegexp.indexIn(QString::fromLocal8Bit(response));

        m_hasCodeBlocksMsvcGenerator = response.contains("CodeBlocks - NMake Makefiles");
        m_hasCodeBlocksNinjaGenerator = response.contains("CodeBlocks - Ninja");
        m_version = versionRegexp.cap(1);
        if (versionRegexp.capturedTexts().size() > 3)
            m_version += QLatin1Char('.') + versionRegexp.cap(3);

        if (m_version.isEmpty()) {
            m_state = CMakeValidator::Invalid;
        } else {
            m_state = CMakeValidator::RunningFunctionList;
            if (!startProcess(QStringList(QLatin1String("--help-command-list"))))
                finished(0); // should never happen, just continue
        }
    } else if (m_state == CMakeValidator::RunningFunctionList) {
        parseFunctionOutput(m_process->readAll());
        m_state = CMakeValidator::RunningFunctionDetails;
        if (!startProcess(QStringList(QLatin1String("--help-commands"))))
            finished(0); // should never happen, just continue
    } else if (m_state == CMakeValidator::RunningFunctionDetails) {
        parseFunctionDetailsOutput(m_process->readAll());
        m_state = CMakeValidator::RunningPropertyList;
        if (!startProcess(QStringList(QLatin1String("--help-property-list"))))
            finished(0); // should never happen, just continue
    } else if (m_state == CMakeValidator::RunningPropertyList) {
        parseVariableOutput(m_process->readAll());
        m_state = CMakeValidator::RunningVariableList;
        if (!startProcess(QStringList(QLatin1String("--help-variable-list"))))
            finished(0); // should never happen, just continue
    } else if (m_state == CMakeValidator::RunningVariableList) {
        parseVariableOutput(m_process->readAll());
        parseDone();
        m_state = CMakeValidator::RunningDone;
    }
}

bool CMakeValidator::isValid() const
{
    if (m_state == CMakeValidator::Invalid)
        return false;
    if (m_state == CMakeValidator::RunningBasic)
        m_process->waitForFinished();
    return (m_state != CMakeValidator::Invalid);
}

bool CMakeValidator::startProcess(const QStringList &args)
{
    m_process->start(m_executable, args);
    return m_process->waitForStarted(2000);
}

QString CMakeValidator::cmakeExecutable() const
{
    return m_executable;
}

bool CMakeValidator::hasCodeBlocksMsvcGenerator() const
{
    if (!isValid())
        return false;
    return m_hasCodeBlocksMsvcGenerator;
}

bool CMakeValidator::hasCodeBlocksNinjaGenerator() const
{
    if (!isValid())
        return false;
    return m_hasCodeBlocksNinjaGenerator;
}

TextEditor::Keywords CMakeValidator::keywords()
{
    while (m_state != RunningDone && m_state != CMakeValidator::Invalid) {
        m_process->waitForFinished();
    }

    if (m_state == CMakeValidator::Invalid)
        return TextEditor::Keywords(QStringList(), QStringList(), QMap<QString, QStringList>());

    return TextEditor::Keywords(m_variables, m_functions, m_functionArgs);
}

static void extractKeywords(const QByteArray &input, QStringList *destination)
{
    if (!destination)
        return;

    QString keyword;
    int ignoreZone = 0;
    for (int i = 0; i < input.count(); ++i) {
        const QChar chr = QLatin1Char(input.at(i));
        if (chr == QLatin1Char('{'))
            ++ignoreZone;
        if (chr == QLatin1Char('}'))
            --ignoreZone;
        if (ignoreZone == 0) {
            if ((chr.isLetterOrNumber() && chr.isUpper())
                || chr == QLatin1Char('_')) {
                keyword += chr;
            } else {
                if (!keyword.isEmpty()) {
                    if (keyword.size() > 1)
                        *destination << keyword;
                    keyword.clear();
                }
            }
        }
    }
    if (keyword.size() > 1)
        *destination << keyword;
}

void CMakeValidator::parseFunctionOutput(const QByteArray &output)
{
    QList<QByteArray> cmakeFunctionsList = output.split('\n');
    m_functions.clear();
    if (!cmakeFunctionsList.isEmpty()) {
        cmakeFunctionsList.removeFirst(); //remove version string
        foreach (const QByteArray &function, cmakeFunctionsList)
            m_functions << QString::fromLocal8Bit(function.trimmed());
    }
}

QString CMakeValidator::formatFunctionDetails(const QString &command, const QString &args)
{
    return QString::fromLatin1("<table><tr><td><b>%1</b></td><td>%2</td></tr>")
            .arg(Qt::escape(command)).arg(Qt::escape(args));
}

void CMakeValidator::parseFunctionDetailsOutput(const QByteArray &output)
{
    QStringList cmakeFunctionsList = m_functions;
    QList<QByteArray> cmakeCommandsHelp = output.split('\n');
    for (int i = 0; i < cmakeCommandsHelp.count(); ++i) {
        QByteArray lineTrimmed = cmakeCommandsHelp.at(i).trimmed();
        if (cmakeFunctionsList.isEmpty())
            break;
        if (cmakeFunctionsList.first().toLatin1() == lineTrimmed) {
            QStringList commandSyntaxes;
            QString currentCommandSyntax;
            QString currentCommand = cmakeFunctionsList.takeFirst();
            ++i;
            for (; i < cmakeCommandsHelp.count(); ++i) {
                lineTrimmed = cmakeCommandsHelp.at(i).trimmed();

                if (!cmakeFunctionsList.isEmpty() && cmakeFunctionsList.first().toLatin1() == lineTrimmed) {
                    //start of next function in output
                    if (!currentCommandSyntax.isEmpty())
                        commandSyntaxes << currentCommandSyntax.append(QLatin1String("</table>"));
                    --i;
                    break;
                }
                if (lineTrimmed.startsWith(currentCommand.toLatin1() + "(")) {
                    if (!currentCommandSyntax.isEmpty())
                        commandSyntaxes << currentCommandSyntax.append(QLatin1String("</table>"));

                    QByteArray argLine = lineTrimmed.mid(currentCommand.length());
                    extractKeywords(argLine, &m_variables);
                    currentCommandSyntax = formatFunctionDetails(currentCommand, QString::fromUtf8(argLine));
                } else {
                    if (!currentCommandSyntax.isEmpty()) {
                        if (lineTrimmed.isEmpty()) {
                            commandSyntaxes << currentCommandSyntax.append(QLatin1String("</table>"));
                            currentCommandSyntax.clear();
                        } else {
                            extractKeywords(lineTrimmed, &m_variables);
                            currentCommandSyntax += QString::fromLatin1("<tr><td>&nbsp;</td><td>%1</td></tr>")
                                    .arg(Qt::escape(QString::fromLocal8Bit(lineTrimmed)));
                        }
                    }
                }
            }
            m_functionArgs[currentCommand] = commandSyntaxes;
        }
    }
    m_functions = m_functionArgs.keys();
}

void CMakeValidator::parseVariableOutput(const QByteArray &output)
{
    QList<QByteArray> variableList = output.split('\n');
    if (!variableList.isEmpty()) {
        variableList.removeFirst(); //remove version string
        foreach (const QByteArray &variable, variableList) {
            if (variable.contains("_<CONFIG>")) {
                m_variables << QString::fromLocal8Bit(variable).replace(QLatin1String("_<CONFIG>"), QLatin1String("_DEBUG"));
                m_variables << QString::fromLocal8Bit(variable).replace(QLatin1String("_<CONFIG>"), QLatin1String("_RELEASE"));
                m_variables << QString::fromLocal8Bit(variable).replace(QLatin1String("_<CONFIG>"), QLatin1String("_MINSIZEREL"));
                m_variables << QString::fromLocal8Bit(variable).replace(QLatin1String("_<CONFIG>"), QLatin1String("_RELWITHDEBINFO"));
            } else if (variable.contains("_<LANG>")) {
                m_variables << QString::fromLocal8Bit(variable).replace(QLatin1String("_<LANG>"), QLatin1String("_C"));
                m_variables << QString::fromLocal8Bit(variable).replace(QLatin1String("_<LANG>"), QLatin1String("_CXX"));
            } else if (!variable.contains("_<") && !variable.contains('[')) {
                m_variables << QString::fromLocal8Bit(variable);
            }
        }
    }
}

void CMakeValidator::parseDone()
{
    m_variables.sort();
    m_variables.removeDuplicates();
}
