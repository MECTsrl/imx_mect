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

#ifndef TABSETTINGS_H
#define TABSETTINGS_H

#include "texteditor_global.h"

#include <QTextBlock>

QT_BEGIN_NAMESPACE
class QSettings;
QT_END_NAMESPACE

namespace TextEditor {

// Tab settings: Data type the GeneralSettingsPage acts on
// with some convenience functions for formatting.
class TEXTEDITOR_EXPORT TabSettings
{
public:

    enum TabPolicy {
        SpacesOnlyTabPolicy = 0,
        TabsOnlyTabPolicy = 1,
        MixedTabPolicy = 2
    };

    // This enum must match the indexes of continuationAlignBehavior widget
    enum ContinuationAlignBehavior {
        NoContinuationAlign = 0,
        ContinuationAlignWithSpaces = 1,
        ContinuationAlignWithIndent = 2
    };

    TabSettings();

    void toSettings(const QString &category, QSettings *s) const;
    void fromSettings(const QString &category, const QSettings *s);

    void toMap(const QString &prefix, QVariantMap *map) const;
    void fromMap(const QString &prefix, const QVariantMap &map);

    int lineIndentPosition(const QString &text) const;
    int firstNonSpace(const QString &text) const;
    inline bool onlySpace(const QString &text) const { return firstNonSpace(text) == text.length(); }
    int columnAt(const QString &text, int position) const;
    int positionAtColumn(const QString &text, int column, int *offset = 0) const;
    int spacesLeftFromPosition(const QString &text, int position) const;
    int indentedColumn(int column, bool doIndent = true) const;
    QString indentationString(int startColumn, int targetColumn, const QTextBlock &currentBlock = QTextBlock()) const;
    QString indentationString(const QString &text) const;
    int indentationColumn(const QString &text) const;
    int maximumPadding(const QString &text) const;

    bool cursorIsAtBeginningOfLine(const QTextCursor &cursor) const;

    void indentLine(QTextBlock block, int newIndent, int padding = 0) const;
    void reindentLine(QTextBlock block, int delta) const;

    int trailingWhitespaces(const QString &text) const;
    void removeTrailingWhitespace(QTextCursor cursor, QTextBlock &block) const;
    bool isIndentationClean(const QTextBlock &block) const;
    bool guessSpacesForTabs(const QTextBlock &block) const;

    TabPolicy m_tabPolicy;
    int m_tabSize;
    int m_indentSize;
    ContinuationAlignBehavior m_continuationAlignBehavior;

    bool equals(const TabSettings &ts) const;
};

inline bool operator==(const TabSettings &t1, const TabSettings &t2) { return t1.equals(t2); }
inline bool operator!=(const TabSettings &t1, const TabSettings &t2) { return !t1.equals(t2); }

} // namespace TextEditor

Q_DECLARE_METATYPE(TextEditor::TabSettings)

#endif // TABSETTINGS_H
