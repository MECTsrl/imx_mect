/****************************************************************************
**
** Copyright (C) 2016 MECT srl.
** Contact: http://www.mect.it/
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General
** Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 3.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
****************************************************************************/

#include "cteplugin.h"
#include "ctedit.h"

#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/coreconstants.h>
#include <coreplugin/icore.h>
#include <coreplugin/id.h>
#include <coreplugin/imode.h>
#include <coreplugin/modemanager.h>
#include <projectexplorer/project.h>
#include <projectexplorer/projectexplorer.h>

#include <QAction>
#include <QFileInfo>
#include <QMenu>
#include <QString>
#include <QtPlugin>
#include <QDebug>
#include <iostream>

namespace CTE {
namespace Internal {

ctedit * ctEditor;

/*! A mode with a push button based on BaseMode */

class CTEMode : public Core::IMode
{
public:

    CTEMode()
    {
        ctEditor = new ctedit();
        setWidget(ctEditor);
        setContext(Core::Context("CTE.MainView"));
        setDisplayName(tr("XTable"));
        setIcon(QIcon());
        setPriority(0);
        setId("CTE.CTEMode");
        setContextHelpId(QString());
        setEnabled(false);
    }
};

/*! Constructs the Cross Table Editor plugin. Normally plugins don't do anything
    in their constructor except for initializing their member variables. The
    actual work is done later, in the initialize() and extensionsInitialized()
    methods.
*/
CTEPlugin::CTEPlugin()
{
}

/*! Plugins are responsible for deleting objects they created on the heap, and
    to unregister objects from the plugin manager that they registered there.
*/
CTEPlugin::~CTEPlugin()
{
}

/*! Initializes the plugin. Returns true on success.
    Plugins want to register objects with the plugin manager here.

    \a errorMessage can be used to pass an error message to the plugin system,
       if there was any.
*/
bool
CTEPlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments)
    Q_UNUSED(errorMessage)

    // Create a unique context for our own view, that will be used for the
    // menu entry later.
    Core::Context context("CTE.MainView");


    // Create an action to be triggered by a menu entry
    QAction *CTEAction = new QAction(tr("&XTable Editor"), this);
    connect(CTEAction, SIGNAL(triggered()), SLOT(enableIfCT()));

    // Register the action with the action manager
    Core::Command *command = Core::ActionManager::registerAction(CTEAction, "CTE.CTEAction", context);


    // Create our own menu to place in the Tools menu
    Core::ActionContainer *CTEMenu = Core::ActionManager::createMenu("CTE.CTEMenu");
    QMenu *menu = CTEMenu->menu();
    menu->setTitle(tr("&XTable Editor"));
    menu->setEnabled(true);

    // Add the Cross Table Editor action command to the menu
    CTEMenu->addAction(command);

    // Request the Tools menu and add the Cross Table Editor menu to it
    Core::ActionContainer *toolsMenu = Core::ActionManager::actionContainer(Core::Constants::M_TOOLS);
    toolsMenu->addMenu(CTEMenu);


    // Add a mode with a push button based on BaseMode. Like the BaseView,
    // it will unregister itself from the plugin manager when it is deleted.
    m_cteMode = new CTEMode;
    addAutoReleasedObject(m_cteMode);


    // Current project has changed.
    connect(
        ProjectExplorer::ProjectExplorerPlugin::instance(),
        SIGNAL(currentProjectChanged(ProjectExplorer::Project*)),
        SLOT(enableIfCT())
    );
    // Project files have changed.
    connect(
        ProjectExplorer::ProjectExplorerPlugin::instance(),
        SIGNAL(fileListChanged()),
        SLOT(enableIfCT())
    );

    return true;
}

/*! Notification that all extensions that this plugin depends on have been
    initialized. The dependencies are defined in the plugins .pluginspec file.

    Normally this method is used for things that rely on other plugins to have
    added objects to the plugin manager, that implement interfaces that we're
    interested in. These objects can now be requested through the
    PluginManagerInterface.

    The CTEPlugin doesn't need things from other plugins, so it does
    nothing here.
*/
void
CTEPlugin::extensionsInitialized()
{
}

/*! Enable the cross table editor only when there is an active
    project and if it has a cross table file (Crosstable.csv).
 */
void
CTEPlugin::enableIfCT()
{
    bool    fFileExists = false;
    QString szFileCT;

    // Clear Project Path for Editor
    szFileCT.clear();
    ctEditor->setProjectPath(szFileCT);
    // Retrieve current project if any
    ProjectExplorer::Project *p = ProjectExplorer::ProjectExplorerPlugin::currentProject();
    // No project
    if (p == NULL) {
        m_cteMode->setEnabled(false);
        return;
    }
    // Retrieve Project directory
    QString pd = p->projectDirectory();
    // No project path
    if (pd.isEmpty()) {
        m_cteMode->setEnabled(false);
        return;
    }
    // Building Cross Table File Name
    szFileCT = pd + QString::fromAscii("/") + QString::fromAscii(Constants::CT_PROJ_REL_PATH) + QString::fromAscii("/") + QString::fromAscii(Constants::CT_FILE_NAME);
    qDebug()  << "Checking File: " << szFileCT;
    // Any cross table in the project?
    QFileInfo ctFile(szFileCT);
    fFileExists = ctFile.exists() && ctFile.isFile();
    // Opening file
    if (fFileExists)  {
        qDebug()  << "File Found: " << szFileCT << "CTE Enabled";
        ctEditor->setProjectPath(pd);
        fFileExists = ctEditor->selectCTFile(szFileCT);
    }
    else
        qDebug()  << "File Not Found: " << szFileCT;
    // Enabling CTEditor
    m_cteMode->setEnabled(fFileExists);
}

} // namespace Internal
} // namespace CTE

Q_EXPORT_PLUGIN(CTE::Internal::CTEPlugin)
