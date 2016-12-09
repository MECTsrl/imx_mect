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

#ifndef DEBUGGER_COMMONOPTIONSPAGE_H
#define DEBUGGER_COMMONOPTIONSPAGE_H

#include "debuggersourcepathmappingwidget.h"
#include "ui_localsandexpressionsoptionspage.h"

#include <coreplugin/dialogs/ioptionspage.h>
#include <utils/savedaction.h>

#include <QPointer>
#include <QSharedPointer>

QT_BEGIN_NAMESPACE
class QSpinBox;
QT_END_NAMESPACE

namespace Debugger {
namespace Internal {

class GlobalDebuggerOptions;

///////////////////////////////////////////////////////////////////////
//
// CommonOptionsPage
//
///////////////////////////////////////////////////////////////////////

class CommonOptionsPageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CommonOptionsPageWidget(const QSharedPointer<Utils::SavedActionSet> &group, QWidget *parent = 0);

    QString searchKeyWords() const;
    GlobalDebuggerOptions globalOptions() const;
    void setGlobalOptions(const GlobalDebuggerOptions &go);

private:
    QCheckBox *checkBoxUseAlternatingRowColors;
    QCheckBox *checkBoxFontSizeFollowsEditor;
    QCheckBox *checkBoxUseToolTipsInMainEditor;
    QCheckBox *checkBoxListSourceFiles;
    QCheckBox *checkBoxCloseBuffersOnExit;
    QCheckBox *checkBoxSwitchModeOnExit;
    QCheckBox *checkBoxBringToForegroundOnInterrrupt;
    QCheckBox *checkBoxShowQmlObjectTree;
    QCheckBox *checkBoxBreakpointsFullPath;
    QCheckBox *checkBoxRegisterForPostMortem;
    QCheckBox *checkBoxWarnOnReleaseBuilds;
    QLabel *labelMaximalStackDepth;
    QLabel *labelMaximalStringLength;
    QSpinBox *spinBoxMaximalStackDepth;
    QSpinBox *spinBoxMaximalStringLength;

    DebuggerSourcePathMappingWidget *sourcesMappingWidget;
    const QSharedPointer<Utils::SavedActionSet> m_group;
};

class CommonOptionsPage : public Core::IOptionsPage
{
    Q_OBJECT

public:
    explicit CommonOptionsPage(const QSharedPointer<GlobalDebuggerOptions> &go);
    ~CommonOptionsPage();

    // IOptionsPage
    QWidget *createPage(QWidget *parent);
    void apply();
    void finish();
    bool matches(const QString &s) const;

    static QString msgSetBreakpointAtFunction(const char *function);
    static QString msgSetBreakpointAtFunctionToolTip(const char *function,
                                                     const QString &hint = QString());

private:
    const QSharedPointer<GlobalDebuggerOptions> m_options;
    QSharedPointer<Utils::SavedActionSet> m_group;
    QString m_searchKeywords;
    QPointer<CommonOptionsPageWidget> m_widget;
};


///////////////////////////////////////////////////////////////////////
//
// LocalsAndExpressionsOptionsPage
//
///////////////////////////////////////////////////////////////////////

class LocalsAndExpressionsOptionsPage : public Core::IOptionsPage
{
public:
    LocalsAndExpressionsOptionsPage();

    // IOptionsPage
    QWidget *createPage(QWidget *parent);
    void apply();
    void finish();
    bool matches(const QString &s) const;

private:
    Ui::DebuggingHelperOptionPage m_ui;
    Utils::SavedActionSet m_group;
    QString m_searchKeywords;
};

} // namespace Internal
} // namespace Debugger

#endif // DEBUGGER_COMMONOPTIONSPAGE_H
