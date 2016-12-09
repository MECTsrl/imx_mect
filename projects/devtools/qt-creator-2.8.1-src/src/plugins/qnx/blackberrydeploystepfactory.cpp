/**************************************************************************
**
** Copyright (C) 2011 - 2013 Research In Motion
**
** Contact: Research In Motion (blackberry-qt@qnx.com)
** Contact: KDAB (info@kdab.com)
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

#include "blackberrydeploystepfactory.h"
#include "qnxconstants.h"
#include "blackberrydeploystep.h"
#include "blackberrydeviceconfigurationfactory.h"

#include <projectexplorer/buildsteplist.h>
#include <projectexplorer/kitinformation.h>
#include <projectexplorer/projectexplorerconstants.h>
#include <projectexplorer/target.h>

using namespace Qnx;
using namespace Qnx::Internal;

BlackBerryDeployStepFactory::BlackBerryDeployStepFactory()
{
}

QList<Core::Id> BlackBerryDeployStepFactory::availableCreationIds(ProjectExplorer::BuildStepList *parent) const
{
    if (parent->id() != ProjectExplorer::Constants::BUILDSTEPS_DEPLOY)
        return QList<Core::Id>();

    Core::Id deviceType = ProjectExplorer::DeviceTypeKitInformation::deviceTypeId(parent->target()->kit());
    if (deviceType != BlackBerryDeviceConfigurationFactory::deviceType())
        return QList<Core::Id>();

    return QList<Core::Id>() << Core::Id(Constants::QNX_DEPLOY_PACKAGE_BS_ID);
}

QString BlackBerryDeployStepFactory::displayNameForId(const Core::Id id) const
{
    if (id == Constants::QNX_DEPLOY_PACKAGE_BS_ID)
        return tr("Deploy Package");
    return QString();
}

bool BlackBerryDeployStepFactory::canCreate(ProjectExplorer::BuildStepList *parent, const Core::Id id) const
{
    return availableCreationIds(parent).contains(id);
}

ProjectExplorer::BuildStep *BlackBerryDeployStepFactory::create(ProjectExplorer::BuildStepList *parent,
                                                         const Core::Id id)
{
    if (!canCreate(parent, id))
        return 0;
    return new BlackBerryDeployStep(parent);
}

bool BlackBerryDeployStepFactory::canRestore(ProjectExplorer::BuildStepList *parent,
                                      const QVariantMap &map) const
{
    return canCreate(parent, ProjectExplorer::idFromMap(map));
}

ProjectExplorer::BuildStep *BlackBerryDeployStepFactory::restore(ProjectExplorer::BuildStepList *parent,
                                                          const QVariantMap &map)
{
    if (!canRestore(parent, map))
        return 0;
    BlackBerryDeployStep *bs = new BlackBerryDeployStep(parent);
    if (bs->fromMap(map))
        return bs;
    delete bs;
    return 0;
}

bool BlackBerryDeployStepFactory::canClone(ProjectExplorer::BuildStepList *parent,
                                    ProjectExplorer::BuildStep *product) const
{
    return canCreate(parent, product->id());
}

ProjectExplorer::BuildStep *BlackBerryDeployStepFactory::clone(ProjectExplorer::BuildStepList *parent,
                                                        ProjectExplorer::BuildStep *product)
{
    if (!canClone(parent, product))
        return 0;
    return new BlackBerryDeployStep(parent, static_cast<BlackBerryDeployStep *>(product));
}
