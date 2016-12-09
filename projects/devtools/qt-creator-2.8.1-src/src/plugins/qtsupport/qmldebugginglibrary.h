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

#ifndef QMLDEBUGGINGLIBRARY_H
#define QMLDEBUGGINGLIBRARY_H

#include <utils/buildablehelperlibrary.h>

QT_FORWARD_DECLARE_CLASS(QDir)

namespace Utils {
    class Environment;
}

namespace ProjectExplorer {
    class Project;
}

namespace QtSupport {

class BaseQtVersion;

class QmlDebuggingLibrary : public Utils::BuildableHelperLibrary
{
public:
    static QString libraryByInstallData(const QString &qtInstallData, bool debugBuild);

    static bool canBuild(const BaseQtVersion *qtVersion, QString *reason = 0);
    static bool build(BuildHelperArguments arguments, QString *log, QString *errorMessage);

    static QString copy(const QString &qtInstallData, QString *errorMessage);

private:
    static QStringList recursiveFileList(const QDir &dir, const QString &prefix = QString());
    static QStringList installDirectories(const QString &qtInstallData);
    static QString sourcePath();
    static QStringList sourceFileNames();
};

} // namespace

#endif // QMLDEBUGGINGLIBRARY_H
