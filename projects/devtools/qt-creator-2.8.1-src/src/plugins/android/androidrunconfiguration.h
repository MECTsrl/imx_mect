/**************************************************************************
**
** Copyright (c) 2013 BogDan Vatra <bog_dan_ro@yahoo.com>
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

#ifndef ANDROIDRUNCONFIGURATION_H
#define ANDROIDRUNCONFIGURATION_H

#include "androidconstants.h"
#include "androidconfigurations.h"

#include <projectexplorer/runconfiguration.h>

namespace Android {
namespace Internal {

class AndroidDeployStep;
class AndroidRunConfigurationFactory;

class AndroidRunConfiguration : public ProjectExplorer::RunConfiguration
{
    Q_OBJECT
    friend class AndroidRunConfigurationFactory;

public:
    AndroidRunConfiguration(ProjectExplorer::Target *parent, Core::Id id, const QString &path);

    QWidget *createConfigurationWidget();
    Utils::OutputFormatter *createOutputFormatter() const;

    AndroidDeployStep *deployStep() const;

    void setArguments(const QString &args);
    AndroidConfig config() const;
    QString proFilePath() const;

    const QString remoteChannel() const;
    const QString dumperLib() const;

protected:
    AndroidRunConfiguration(ProjectExplorer::Target *parent, AndroidRunConfiguration *source);
    QString defaultDisplayName();

private:
    void init();

    QString m_proFilePath;
};

} // namespace Internal
} // namespace Android

#endif // ANDROIDRUNCONFIGURATION_H
