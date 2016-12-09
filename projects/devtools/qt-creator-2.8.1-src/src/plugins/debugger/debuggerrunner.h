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

#ifndef DEBUGGERRUNNER_H
#define DEBUGGERRUNNER_H

#include "debugger_global.h"
#include "debuggerconstants.h"

#include <projectexplorer/runconfiguration.h>

namespace Utils {
class Environment;
}

namespace Debugger {
class DebuggerEngine;
class DebuggerRunControl;
class DebuggerStartParameters;

namespace Internal {
class DebuggerRunControlPrivate;
class DebuggerRunControlFactory;
} // namespace Internal


class DEBUGGER_EXPORT DebuggerRunControl
    : public ProjectExplorer::RunControl
{
    Q_OBJECT

public:
    DebuggerRunControl(ProjectExplorer::RunConfiguration *runConfiguration,
                       const DebuggerStartParameters &sp);
    ~DebuggerRunControl();

    // ProjectExplorer::RunControl
    void start();
    bool promptToStop(bool *prompt = 0) const;
    StopResult stop(); // Called from SnapshotWindow.
    bool isRunning() const;
    QString displayName() const;
    QIcon icon() const;

    void setCustomEnvironment(Utils::Environment env);
    void startFailed();
    void debuggingFinished();
    ProjectExplorer::RunConfiguration *runConfiguration() const;
    DebuggerEngine *engine(); // FIXME: Remove. Only used by Maemo support.

    void showMessage(const QString &msg, int channel);

signals:
    void engineRequestSetup();

private slots:
    void handleFinished();

protected:
    const DebuggerStartParameters &startParameters() const;

private:
    //friend class Internal::DebuggerRunControlFactory;
    Internal::DebuggerRunControlPrivate *d;
};

} // namespace Debugger

#endif // DEBUGGERRUNNER_H
