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

#ifndef QT4MAEMODEPLOYCONFIGURATION_H
#define QT4MAEMODEPLOYCONFIGURATION_H

#include <remotelinux/remotelinuxdeployconfiguration.h>
#include <utils/fileutils.h>

namespace Madde {
namespace Internal {

class Qt4MaemoDeployConfigurationFactory : public ProjectExplorer::DeployConfigurationFactory
{
    Q_OBJECT

public:
    explicit Qt4MaemoDeployConfigurationFactory(QObject *parent = 0);

    QList<Core::Id> availableCreationIds(ProjectExplorer::Target *parent) const;
    QString displayNameForId(const Core::Id id) const;
    bool canCreate(ProjectExplorer::Target *parent, const Core::Id id) const;
    ProjectExplorer::DeployConfiguration *create(ProjectExplorer::Target *parent, const Core::Id id);
    bool canRestore(ProjectExplorer::Target *parent, const QVariantMap &map) const;
    ProjectExplorer::DeployConfiguration *restore(ProjectExplorer::Target *parent, const QVariantMap &map);
    ProjectExplorer::DeployConfiguration *clone(ProjectExplorer::Target *parent,
        ProjectExplorer::DeployConfiguration *product);

    bool canHandle(ProjectExplorer::Target *parent) const;
};

class Qt4MaemoDeployConfiguration : public RemoteLinux::RemoteLinuxDeployConfiguration
{
    Q_OBJECT

public:
    ~Qt4MaemoDeployConfiguration();

    ProjectExplorer::NamedWidget *createConfigWidget();

    static Core::Id fremantleWithPackagingId();
    static Core::Id fremantleWithoutPackagingId();
    static Core::Id harmattanId();

signals:
    void packagingChanged();

private slots:
    void debianDirChanged(const Utils::FileName &dir);
    void setupPackaging();

private:
    void init();
    void setupDebianPackaging();
    void addFilesToProject(const QStringList &files);

    friend class Internal::Qt4MaemoDeployConfigurationFactory;

    Qt4MaemoDeployConfiguration(ProjectExplorer::Target *target, const Core::Id id,
        const QString &displayName);
    Qt4MaemoDeployConfiguration(ProjectExplorer::Target *target,
        Qt4MaemoDeployConfiguration *source);
};

} // namespace Internal
} // namespace Madde

#endif // QT4MAEMODEPLOYCONFIGURATION_H
