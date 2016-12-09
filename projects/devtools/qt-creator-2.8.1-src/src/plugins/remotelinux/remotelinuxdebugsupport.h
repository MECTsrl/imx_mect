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

#ifndef REMOTELINUXDEBUGSUPPORT_H
#define REMOTELINUXDEBUGSUPPORT_H

#include "abstractremotelinuxrunsupport.h"

namespace Debugger {
class DebuggerEngine;
class DebuggerStartParameters;
}

namespace RemoteLinux {
class RemoteLinuxRunConfiguration;

namespace Internal { class LinuxDeviceDebugSupportPrivate; }

class REMOTELINUX_EXPORT LinuxDeviceDebugSupport : public AbstractRemoteLinuxRunSupport
{
    Q_OBJECT
public:
    static Debugger::DebuggerStartParameters startParameters(const RemoteLinuxRunConfiguration *runConfig);

    LinuxDeviceDebugSupport(RemoteLinuxRunConfiguration *runConfig,
            Debugger::DebuggerEngine *engine);
    ~LinuxDeviceDebugSupport();

protected:
    void startExecution();
    void handleAdapterSetupFailed(const QString &error);
    void handleAdapterSetupDone();

private slots:
    void handleRemoteSetupRequested();
    void handleAppRunnerError(const QString &error);
    void handleRemoteOutput(const QByteArray &output);
    void handleRemoteErrorOutput(const QByteArray &output);
    void handleAppRunnerFinished(bool success);
    void handleProgressReport(const QString &progressOutput);

    void handleRemoteProcessStarted();
    void handleDebuggingFinished();

private:
    void showMessage(const QString &msg, int channel);

    Internal::LinuxDeviceDebugSupportPrivate * const d;
};

} // namespace RemoteLinux

#endif // REMOTELINUXDEBUGSUPPORT_H
