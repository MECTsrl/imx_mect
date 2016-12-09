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

#include "qmlproject.h"
#include "qmlprojectfile.h"
#include "fileformat/qmlprojectitem.h"
#include "qmlprojectrunconfiguration.h"
#include "qmlprojectconstants.h"
#include "qmlprojectnodes.h"
#include "qmlprojectmanager.h"

#include <coreplugin/icore.h>
#include <coreplugin/messagemanager.h>
#include <coreplugin/documentmanager.h>
#include <qtsupport/baseqtversion.h>
#include <qtsupport/qtkitinformation.h>
#include <qmljstools/qmljsmodelmanager.h>
#include <projectexplorer/kitinformation.h>
#include <projectexplorer/kitmanager.h>
#include <projectexplorer/target.h>
#include <qtsupport/qtsupportconstants.h>

#include <QDeclarativeComponent>
#include <QDebug>

namespace QmlProjectManager {

namespace Internal {

class QmlProjectKitMatcher : public ProjectExplorer::KitMatcher
{
public:
    QmlProjectKitMatcher(const QmlProject::QmlImport &import)
        : import(import)
    {
    }

    bool matches(const ProjectExplorer::Kit *k) const
    {
        if (!k->isValid())
            return false;

        ProjectExplorer::IDevice::ConstPtr dev = ProjectExplorer::DeviceKitInformation::device(k);
        if (dev.isNull() || dev->type() != ProjectExplorer::Constants::DESKTOP_DEVICE_TYPE)
            return false;
        QtSupport::BaseQtVersion *version = QtSupport::QtKitInformation::qtVersion(k);
        if (!version || version->type() != QLatin1String(QtSupport::Constants::DESKTOPQT))
            return false;

        bool hasViewer = false; // Initialization needed for dumb compilers.
        QtSupport::QtVersionNumber minVersion;
        switch (import) {
        case QmlProject::UnknownImport:
            minVersion = QtSupport::QtVersionNumber(4, 7, 0);
            hasViewer = !version->qmlviewerCommand().isEmpty() || !version->qmlsceneCommand().isEmpty();
            break;
        case QmlProject::QtQuick1Import:
            minVersion = QtSupport::QtVersionNumber(4, 7, 1);
            hasViewer = !version->qmlviewerCommand().isEmpty();
            break;
        case QmlProject::QtQuick2Import:
            minVersion = QtSupport::QtVersionNumber(5, 0, 0);
            hasViewer = !version->qmlsceneCommand().isEmpty();
            break;
        }

        if (version->qtVersion() >= minVersion
                && hasViewer)
            return true;

        return false;
    }
private:
    QmlProject::QmlImport import;
};

} // namespace Internal

QmlProject::QmlProject(Internal::Manager *manager, const QString &fileName)
    : m_manager(manager),
      m_fileName(fileName),
      m_defaultImport(UnknownImport),
      m_modelManager(QmlJS::ModelManagerInterface::instance())
{
    setProjectContext(Core::Context(QmlProjectManager::Constants::PROJECTCONTEXT));
    setProjectLanguages(Core::Context(ProjectExplorer::Constants::LANG_QMLJS));

    QFileInfo fileInfo(m_fileName);
    m_projectName = fileInfo.completeBaseName();

    m_file = new Internal::QmlProjectFile(this, fileName);
    m_rootNode = new Internal::QmlProjectNode(this, m_file);

    Core::DocumentManager::addDocument(m_file, true);

    m_manager->registerProject(this);
}

QmlProject::~QmlProject()
{
    m_manager->unregisterProject(this);

    Core::DocumentManager::removeDocument(m_file);

    delete m_projectItem.data();
    delete m_rootNode;
}

void QmlProject::addedTarget(ProjectExplorer::Target *target)
{
    connect(target, SIGNAL(addedRunConfiguration(ProjectExplorer::RunConfiguration*)),
            this, SLOT(addedRunConfiguration(ProjectExplorer::RunConfiguration*)));
    foreach (ProjectExplorer::RunConfiguration *rc, target->runConfigurations())
        addedRunConfiguration(rc);
}

void QmlProject::onActiveTargetChanged(ProjectExplorer::Target * /*target*/)
{
    // make sure e.g. the default qml imports are adapted
    refresh(Configuration);
}

void QmlProject::addedRunConfiguration(ProjectExplorer::RunConfiguration *rc)
{
    // The enabled state of qml runconfigurations can only be decided after
    // they have been added to a project
    QmlProjectRunConfiguration *qmlrc = qobject_cast<QmlProjectRunConfiguration *>(rc);
    if (qmlrc)
        qmlrc->updateEnabled();
}

QDir QmlProject::projectDir() const
{
    return QFileInfo(document()->fileName()).dir();
}

QString QmlProject::filesFileName() const
{ return m_fileName; }

static QmlProject::QmlImport detectImport(const QString &qml) {
    static QRegExp qtQuick1RegExp(QLatin1String("import\\s+QtQuick\\s+1"));
    static QRegExp qtQuick2RegExp(QLatin1String("import\\s+QtQuick\\s+2"));

    if (qml.contains(qtQuick1RegExp))
        return QmlProject::QtQuick1Import;
    else if (qml.contains(qtQuick2RegExp))
        return QmlProject::QtQuick2Import;
    else
        return QmlProject::UnknownImport;
}

void QmlProject::parseProject(RefreshOptions options)
{
    Core::MessageManager *messageManager = Core::ICore::messageManager();
    if (options & Files) {
        if (options & ProjectFile)
            delete m_projectItem.data();
        if (!m_projectItem) {
            Utils::FileReader reader;
            if (reader.fetch(m_fileName)) {
                QDeclarativeComponent *component = new QDeclarativeComponent(&m_engine, this);
                component->setData(reader.data(), QUrl::fromLocalFile(m_fileName));
                if (component->isReady()
                    && qobject_cast<QmlProjectItem*>(component->create())) {
                    m_projectItem = qobject_cast<QmlProjectItem*>(component->create());
                    connect(m_projectItem.data(), SIGNAL(qmlFilesChanged(QSet<QString>,QSet<QString>)),
                            this, SLOT(refreshFiles(QSet<QString>,QSet<QString>)));
                } else {
                    messageManager->printToOutputPane(tr("Error while loading project file %1.").arg(m_fileName), Core::MessageManager::NoModeSwitch);
                    messageManager->printToOutputPane(component->errorString(), Core::MessageManager::NoModeSwitch);
                }
            } else {
                messageManager->printToOutputPane(tr("QML project: %1").arg(reader.errorString()), Core::MessageManager::NoModeSwitch);
            }
        }
        if (m_projectItem) {
            m_projectItem.data()->setSourceDirectory(projectDir().path());
            m_modelManager->updateSourceFiles(m_projectItem.data()->files(), true);

            QString mainFilePath = m_projectItem.data()->mainFile();
            if (!mainFilePath.isEmpty()) {
                mainFilePath = projectDir().absoluteFilePath(mainFilePath);
                Utils::FileReader reader;
                QString errorMessage;
                if (!reader.fetch(mainFilePath, &errorMessage)) {
                    messageManager->printToOutputPane(
                                tr("Warning while loading project file %1.").arg(m_fileName),
                                Core::MessageManager::NoModeSwitch);
                    messageManager->printToOutputPane(errorMessage, Core::MessageManager::NoModeSwitch);
                } else {
                    m_defaultImport = detectImport(QString::fromUtf8(reader.data()));
                }
            }
        }
        m_rootNode->refresh();
    }

    if (options & Configuration) {
        // update configuration
    }

    if (options & Files)
        emit fileListChanged();
}

void QmlProject::refresh(RefreshOptions options)
{
    parseProject(options);

    if (options & Files)
        m_rootNode->refresh();

    QmlJS::ModelManagerInterface::ProjectInfo projectInfo =
            QmlJSTools::defaultProjectInfoForProject(this);
    projectInfo.importPaths = customImportPaths();

    m_modelManager->updateProjectInfo(projectInfo);
}

QStringList QmlProject::convertToAbsoluteFiles(const QStringList &paths) const
{
    const QDir projectDir(QFileInfo(m_fileName).dir());
    QStringList absolutePaths;
    foreach (const QString &file, paths) {
        QFileInfo fileInfo(projectDir, file);
        absolutePaths.append(fileInfo.absoluteFilePath());
    }
    absolutePaths.removeDuplicates();
    return absolutePaths;
}

QStringList QmlProject::files() const
{
    QStringList files;
    if (m_projectItem)
        files = m_projectItem.data()->files();
    else
        files = m_files;
    return files;
}

QString QmlProject::mainFile() const
{
    if (m_projectItem)
        return m_projectItem.data()->mainFile();
    return QString();
}

bool QmlProject::validProjectFile() const
{
    return !m_projectItem.isNull();
}

QStringList QmlProject::customImportPaths() const
{
    QStringList importPaths;
    if (m_projectItem)
        importPaths = m_projectItem.data()->importPaths();

    return importPaths;
}

bool QmlProject::addFiles(const QStringList &filePaths)
{
    QStringList toAdd;
    foreach (const QString &filePath, filePaths) {
        if (!m_projectItem.data()->matchesFile(filePath))
            toAdd << filePaths;
    }
    return toAdd.isEmpty();
}

void QmlProject::refreshProjectFile()
{
    refresh(QmlProject::ProjectFile | Files);
}

QmlProject::QmlImport QmlProject::defaultImport() const
{
    return m_defaultImport;
}

void QmlProject::refreshFiles(const QSet<QString> &/*added*/, const QSet<QString> &removed)
{
    refresh(Files);
    if (!removed.isEmpty())
        m_modelManager->removeFiles(removed.toList());
}

QString QmlProject::displayName() const
{
    return m_projectName;
}

Core::Id QmlProject::id() const
{
    return Core::Id("QmlProjectManager.QmlProject");
}

Core::IDocument *QmlProject::document() const
{
    return m_file;
}

ProjectExplorer::IProjectManager *QmlProject::projectManager() const
{
    return m_manager;
}

bool QmlProject::supportsKit(ProjectExplorer::Kit *k, QString *errorMessage) const
{
    Core::Id deviceType = ProjectExplorer::DeviceTypeKitInformation::deviceTypeId(k);
    if (deviceType != ProjectExplorer::Constants::DESKTOP_DEVICE_TYPE) {
        if (errorMessage)
            *errorMessage = tr("Device type is not desktop.");
        return false;
    }

    QtSupport::BaseQtVersion *version = QtSupport::QtKitInformation::qtVersion(k);
    if (!version) {
        if (errorMessage)
            *errorMessage = tr("No Qt version set in kit.");
        return false;
    }

    if (version->qtVersion() < QtSupport::QtVersionNumber(4, 7, 0)) {
        if (errorMessage)
            *errorMessage = tr("Qt version is too old.");
        return false;
    }

    if (version->qtVersion() < QtSupport::QtVersionNumber(5, 0, 0)
            && defaultImport() == QtQuick2Import) {
        if (errorMessage)
            *errorMessage = tr("Qt version is too old.");
        return false;
    }
    return true;
}

ProjectExplorer::ProjectNode *QmlProject::rootProjectNode() const
{
    return m_rootNode;
}

QStringList QmlProject::files(FilesMode) const
{
    return files();
}

bool QmlProject::fromMap(const QVariantMap &map)
{
    if (!Project::fromMap(map))
        return false;

    // refresh first - project information is used e.g. to decide the default RC's
    refresh(Everything);

    if (!activeTarget()) {
        // find a kit that matches prerequisites (prefer default one)
        Internal::QmlProjectKitMatcher matcher(defaultImport());
        ProjectExplorer::KitManager *kitManager = ProjectExplorer::KitManager::instance();
        QList<ProjectExplorer::Kit*> kits = kitManager->kits(&matcher);

        if (!kits.isEmpty()) {
            ProjectExplorer::Kit *kit = 0;
            if (kits.contains(kitManager->defaultKit())) {
                kit = kitManager->defaultKit();
            } else {
                kit = kits.first();
            }
            addTarget(createTarget(kit));
        }
    }

    // addedTarget calls updateEnabled on the runconfigurations
    // which needs to happen after refresh
    foreach (ProjectExplorer::Target *t, targets())
        addedTarget(t);

    connect(this, SIGNAL(addedTarget(ProjectExplorer::Target*)),
            this, SLOT(addedTarget(ProjectExplorer::Target*)));

    connect(this, SIGNAL(activeTargetChanged(ProjectExplorer::Target*)),
            this, SLOT(onActiveTargetChanged(ProjectExplorer::Target*)));

    return true;
}

} // namespace QmlProjectManager

