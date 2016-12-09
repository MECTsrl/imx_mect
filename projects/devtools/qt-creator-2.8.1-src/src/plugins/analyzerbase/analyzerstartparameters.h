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

#ifndef ANALYZERSTARTPARAMETERS_H
#define ANALYZERSTARTPARAMETERS_H

#include "analyzerbase_global.h"
#include "analyzerconstants.h"

#include <QMetaType>

#include <coreplugin/id.h>
#include <ssh/sshconnection.h>
#include <utils/environment.h>

namespace Analyzer {

// Note: This is part of the "soft interface" of the analyzer plugin.
// Do not add anything that needs implementation in a .cpp file.

class ANALYZER_EXPORT AnalyzerStartParameters
{
public:
    AnalyzerStartParameters()
    {}

    StartMode startMode;
    QSsh::SshConnectionParameters connParams;

    Core::Id toolId;
    QString debuggee;
    QString debuggeeArgs;
    QString analyzerCmdPrefix;
    QString displayName;
    Utils::Environment environment;
    QString workingDirectory;
    QString sysroot;
    QString analyzerHost;
    quint16 analyzerPort;
};

} // namespace Analyzer

Q_DECLARE_METATYPE(Analyzer::AnalyzerStartParameters)

#endif // ANALYZERSTARTPARAMETERS_H
