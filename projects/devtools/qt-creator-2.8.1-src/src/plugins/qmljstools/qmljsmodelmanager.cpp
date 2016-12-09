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

#include "qmljsmodelmanager.h"
#include "qmljstoolsconstants.h"
#include "qmljsplugindumper.h"
#include "qmljsfindexportedcpptypes.h"
#include "qmljssemanticinfo.h"
#include "qmljsbundleprovider.h"

#include <coreplugin/icore.h>
#include <coreplugin/progressmanager/progressmanager.h>
#include <coreplugin/messagemanager.h>
#include <cpptools/cppmodelmanagerinterface.h>
#include <qmljs/qmljsbind.h>
#include <texteditor/basetexteditor.h>
#include <projectexplorer/buildconfiguration.h>
#include <projectexplorer/project.h>
#include <projectexplorer/projectexplorer.h>
#include <projectexplorer/session.h>
#include <projectexplorer/target.h>
#include <qtsupport/qtkitinformation.h>
#include <qtsupport/qmldumptool.h>
#include <qtsupport/qtsupportconstants.h>
#include <utils/hostosinfo.h>
#include <extensionsystem/pluginmanager.h>

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <utils/runextensions.h>
#include <QTextStream>
#include <QTimer>
#include <QRegExp>
#include <QtAlgorithms>

#include <QDebug>

using namespace QmlJS;
using namespace QmlJSTools;
using namespace QmlJSTools::Internal;


ModelManagerInterface::ProjectInfo QmlJSTools::defaultProjectInfoForProject(
        ProjectExplorer::Project *project)
{
    ModelManagerInterface::ProjectInfo projectInfo(project);
    ProjectExplorer::Target *activeTarget = 0;
    if (project) {
        Core::MimeDatabase *db = Core::ICore::mimeDatabase();
        QList<Core::MimeGlobPattern> globs;
        QList<Core::MimeType> mimeTypes = db->mimeTypes();
        foreach (const Core::MimeType &mimeType, mimeTypes)
            if (mimeType.type() == QLatin1String(Constants::QML_MIMETYPE)
                    || mimeType.subClassesOf().contains(QLatin1String(Constants::QML_MIMETYPE)))
                globs << mimeType.globPatterns();
        if (globs.isEmpty()) {
            globs.append(Core::MimeGlobPattern(QLatin1String("*.qbs")));
            globs.append(Core::MimeGlobPattern(QLatin1String("*.qml")));
            globs.append(Core::MimeGlobPattern(QLatin1String("*.qmltypes")));
            globs.append(Core::MimeGlobPattern(QLatin1String("*.qmlproject")));
        }
        foreach (const QString &filePath
                 , project->files(ProjectExplorer::Project::ExcludeGeneratedFiles))
            foreach (const Core::MimeGlobPattern &glob, globs)
                if (glob.matches(filePath))
                    projectInfo.sourceFiles << filePath;
        activeTarget = project->activeTarget();
    }
    ProjectExplorer::Kit *activeKit = activeTarget ? activeTarget->kit() :
                                           ProjectExplorer::KitManager::instance()->defaultKit();
    QtSupport::BaseQtVersion *qtVersion = QtSupport::QtKitInformation::qtVersion(activeKit);

    bool preferDebugDump = false;
    bool setPreferDump = false;
    projectInfo.tryQmlDump = false;

    if (activeTarget) {
        if (ProjectExplorer::BuildConfiguration *bc = activeTarget->activeBuildConfiguration()) {
            preferDebugDump = bc->buildType() == ProjectExplorer::BuildConfiguration::Debug;
            setPreferDump = true;
        }
    }
    if (!setPreferDump && qtVersion)
        preferDebugDump = (qtVersion->defaultBuildConfig() & QtSupport::BaseQtVersion::DebugBuild);
    if (qtVersion && qtVersion->isValid()) {
        projectInfo.tryQmlDump = project && (
                    qtVersion->type() == QLatin1String(QtSupport::Constants::DESKTOPQT)
                    || qtVersion->type() == QLatin1String(QtSupport::Constants::SIMULATORQT));
        projectInfo.qtQmlPath = qtVersion->qmakeProperty("QT_INSTALL_QML");
        projectInfo.qtImportsPath = qtVersion->qmakeProperty("QT_INSTALL_IMPORTS");
        projectInfo.qtVersionString = qtVersion->qtVersionString();
    }

    if (projectInfo.tryQmlDump) {
        ProjectExplorer::ToolChain *toolChain =
                ProjectExplorer::ToolChainKitInformation::toolChain(activeKit);
        QtSupport::QmlDumpTool::pathAndEnvironment(project, qtVersion,
                                                   toolChain,
                                                   preferDebugDump, &projectInfo.qmlDumpPath,
                                                   &projectInfo.qmlDumpEnvironment);
        projectInfo.qmlDumpHasRelocatableFlag = qtVersion->hasQmlDumpWithRelocatableFlag();
    } else {
        projectInfo.qmlDumpPath.clear();
        projectInfo.qmlDumpEnvironment.clear();
        projectInfo.qmlDumpHasRelocatableFlag = true;
    }
    setupProjectInfoQmlBundles(projectInfo);
    return projectInfo;
}

void QmlJSTools::setupProjectInfoQmlBundles(ModelManagerInterface::ProjectInfo &projectInfo)
{
    ProjectExplorer::Target *activeTarget = 0;
    if (projectInfo.project) {
        activeTarget = projectInfo.project->activeTarget();
    }
    ProjectExplorer::Kit *activeKit = activeTarget
            ? activeTarget->kit() : ProjectExplorer::KitManager::instance()->defaultKit();
    QHash<QString, QString> replacements;
    replacements.insert(QLatin1String("$(QT_INSTALL_IMPORTS)"), projectInfo.qtImportsPath);
    replacements.insert(QLatin1String("$(QT_INSTALL_QML)"), projectInfo.qtQmlPath);

    QList<IBundleProvider *> bundleProviders =
            ExtensionSystem::PluginManager::getObjects<IBundleProvider>();

    foreach (IBundleProvider *bp, bundleProviders) {
        if (bp)
            bp->mergeBundlesForKit(activeKit, projectInfo.activeBundle, replacements);
    }
    projectInfo.extendedBundle = projectInfo.activeBundle;

    if (projectInfo.project) {
        QSet<ProjectExplorer::Kit *> currentKits;
        foreach (const ProjectExplorer::Target *t, projectInfo.project->targets())
            if (t->kit())
                currentKits.insert(t->kit());
        currentKits.remove(activeKit);
        foreach (ProjectExplorer::Kit *kit, currentKits) {
            foreach (IBundleProvider *bp, bundleProviders)
                if (bp)
                    bp->mergeBundlesForKit(kit, projectInfo.extendedBundle, replacements);
        }
    }
}

static QStringList environmentImportPaths();

static void mergeSuffixes(QStringList &l1, const QStringList &l2)
{
    if (!l2.isEmpty())
        l1 = l2;
}

QmlJS::Document::Language QmlJSTools::languageOfFile(const QString &fileName)
{
    QStringList jsSuffixes(QLatin1String("js"));
    QStringList qmlSuffixes(QLatin1String("qml"));
    QStringList qmlProjectSuffixes(QLatin1String("qmlproject"));
    QStringList jsonSuffixes(QLatin1String("json"));
    QStringList qbsSuffixes(QLatin1String("qbs"));

    if (Core::ICore::instance()) {
        Core::MimeDatabase *db = Core::ICore::mimeDatabase();
        Core::MimeType jsSourceTy = db->findByType(QLatin1String(Constants::JS_MIMETYPE));
        mergeSuffixes(jsSuffixes, jsSourceTy.suffixes());
        Core::MimeType qmlSourceTy = db->findByType(QLatin1String(Constants::QML_MIMETYPE));
        mergeSuffixes(qmlSuffixes, qmlSourceTy.suffixes());
        Core::MimeType qbsSourceTy = db->findByType(QLatin1String(Constants::QBS_MIMETYPE));
        mergeSuffixes(qbsSuffixes, qbsSourceTy.suffixes());
        Core::MimeType qmlProjectSourceTy = db->findByType(QLatin1String(Constants::QMLPROJECT_MIMETYPE));
        mergeSuffixes(qmlProjectSuffixes, qmlProjectSourceTy.suffixes());
        Core::MimeType jsonSourceTy = db->findByType(QLatin1String(Constants::JSON_MIMETYPE));
        mergeSuffixes(jsonSuffixes, jsonSourceTy.suffixes());
    }

    const QFileInfo info(fileName);
    const QString fileSuffix = info.suffix();
    if (jsSuffixes.contains(fileSuffix))
        return QmlJS::Document::JavaScriptLanguage;
    if (qbsSuffixes.contains(fileSuffix))
        return QmlJS::Document::QmlQbsLanguage;
    if (qmlSuffixes.contains(fileSuffix) || qmlProjectSuffixes.contains(fileSuffix))
        return QmlJS::Document::QmlLanguage;
    if (jsonSuffixes.contains(fileSuffix))
        return QmlJS::Document::JsonLanguage;
    return QmlJS::Document::UnknownLanguage;
}

QStringList QmlJSTools::qmlAndJsGlobPatterns()
{
    QStringList pattern;
    if (Core::ICore::instance()) {
        Core::MimeDatabase *db = Core::ICore::mimeDatabase();
        Core::MimeType jsSourceTy = db->findByType(QLatin1String(Constants::JS_MIMETYPE));
        Core::MimeType qmlSourceTy = db->findByType(QLatin1String(Constants::QML_MIMETYPE));

        QStringList pattern;
        foreach (const Core::MimeGlobPattern &glob, jsSourceTy.globPatterns())
            pattern << glob.pattern();
        foreach (const Core::MimeGlobPattern &glob, qmlSourceTy.globPatterns())
            pattern << glob.pattern();
    } else {
        pattern << QLatin1String("*.qml") << QLatin1String("*.js");
    }
    return pattern;
}

ModelManager::ModelManager(QObject *parent):
        ModelManagerInterface(parent),
        m_pluginDumper(new PluginDumper(this))
{
    m_synchronizer.setCancelOnWait(true);

    m_updateCppQmlTypesTimer = new QTimer(this);
    m_updateCppQmlTypesTimer->setInterval(1000);
    m_updateCppQmlTypesTimer->setSingleShot(true);
    connect(m_updateCppQmlTypesTimer, SIGNAL(timeout()), SLOT(startCppQmlTypeUpdate()));

    m_asyncResetTimer = new QTimer(this);
    m_asyncResetTimer->setInterval(15000);
    m_asyncResetTimer->setSingleShot(true);
    connect(m_asyncResetTimer, SIGNAL(timeout()), SLOT(resetCodeModel()));

    qRegisterMetaType<QmlJS::Document::Ptr>("QmlJS::Document::Ptr");
    qRegisterMetaType<QmlJS::LibraryInfo>("QmlJS::LibraryInfo");
    qRegisterMetaType<QmlJSTools::SemanticInfo>("QmlJSTools::SemanticInfo");

    loadQmlTypeDescriptions();

    m_defaultImportPaths << environmentImportPaths();
    updateImportPaths();
}

ModelManager::~ModelManager()
{
    m_cppQmlTypesUpdater.cancel();
    m_cppQmlTypesUpdater.waitForFinished();
}

void ModelManager::delayedInitialization()
{
    CppTools::CppModelManagerInterface *cppModelManager =
            CppTools::CppModelManagerInterface::instance();
    if (cppModelManager) {
        // It's important to have a direct connection here so we can prevent
        // the source and AST of the cpp document being cleaned away.
        connect(cppModelManager, SIGNAL(documentUpdated(CPlusPlus::Document::Ptr)),
                this, SLOT(maybeQueueCppQmlTypeUpdate(CPlusPlus::Document::Ptr)), Qt::DirectConnection);
    }

    ProjectExplorer::SessionManager *sessionManager = ProjectExplorer::ProjectExplorerPlugin::instance()->session();
    connect(sessionManager, SIGNAL(projectRemoved(ProjectExplorer::Project*)),
            this, SLOT(removeProjectInfo(ProjectExplorer::Project*)));
}

void ModelManager::loadQmlTypeDescriptions()
{
    if (Core::ICore::instance()) {
        loadQmlTypeDescriptions(Core::ICore::resourcePath());
        loadQmlTypeDescriptions(Core::ICore::userResourcePath());
    }
}

void ModelManager::loadQmlTypeDescriptions(const QString &resourcePath)
{
    const QDir typeFileDir(resourcePath + QLatin1String("/qml-type-descriptions"));
    const QStringList qmlTypesExtensions = QStringList() << QLatin1String("*.qmltypes");
    QFileInfoList qmlTypesFiles = typeFileDir.entryInfoList(
                qmlTypesExtensions,
                QDir::Files,
                QDir::Name);

    QStringList errors;
    QStringList warnings;

    // filter out the actual Qt builtins
    for (int i = 0; i < qmlTypesFiles.size(); ++i) {
        if (qmlTypesFiles.at(i).baseName() == QLatin1String("builtins")) {
            QFileInfoList list;
            list.append(qmlTypesFiles.at(i));
            CppQmlTypesLoader::defaultQtObjects =
                    CppQmlTypesLoader::loadQmlTypes(list, &errors, &warnings);
            qmlTypesFiles.removeAt(i);
            break;
        }
    }

    // load the fallbacks for libraries
    CppQmlTypesLoader::defaultLibraryObjects.unite(
                CppQmlTypesLoader::loadQmlTypes(qmlTypesFiles, &errors, &warnings));

    Core::MessageManager *messageManager = Core::MessageManager::instance();
    foreach (const QString &error, errors)
        messageManager->printToOutputPane(error, Core::MessageManager::Flash);
    foreach (const QString &warning, warnings)
        messageManager->printToOutputPane(warning, Core::MessageManager::Flash);
}

ModelManagerInterface::WorkingCopy ModelManager::workingCopy() const
{
    WorkingCopy workingCopy;
    if (!Core::ICore::instance())
        return workingCopy;

    foreach (Core::IEditor *editor, Core::ICore::editorManager()->openedEditors()) {
        const QString key = editor->document()->fileName();

        if (TextEditor::ITextEditor *textEditor = qobject_cast<TextEditor::ITextEditor*>(editor)) {
            if (textEditor->context().contains(ProjectExplorer::Constants::LANG_QMLJS)) {
                if (TextEditor::BaseTextEditorWidget *ed = qobject_cast<TextEditor::BaseTextEditorWidget *>(textEditor->widget()))
                    workingCopy.insert(key, ed->toPlainText(), ed->document()->revision());
            }
        }
    }

    return workingCopy;
}

Snapshot ModelManager::snapshot() const
{
    QMutexLocker locker(&m_mutex);
    return _validSnapshot;
}

Snapshot ModelManager::newestSnapshot() const
{
    QMutexLocker locker(&m_mutex);
    return _newestSnapshot;
}

void ModelManager::updateSourceFiles(const QStringList &files,
                                     bool emitDocumentOnDiskChanged)
{
    refreshSourceFiles(files, emitDocumentOnDiskChanged);
}

QFuture<void> ModelManager::refreshSourceFiles(const QStringList &sourceFiles,
                                               bool emitDocumentOnDiskChanged)
{
    if (sourceFiles.isEmpty())
        return QFuture<void>();

    QFuture<void> result = QtConcurrent::run(&ModelManager::parse,
                                              workingCopy(), sourceFiles,
                                              this,
                                              emitDocumentOnDiskChanged);

    if (m_synchronizer.futures().size() > 10) {
        QList<QFuture<void> > futures = m_synchronizer.futures();

        m_synchronizer.clearFutures();

        foreach (const QFuture<void> &future, futures) {
            if (! (future.isFinished() || future.isCanceled()))
                m_synchronizer.addFuture(future);
        }
    }

    m_synchronizer.addFuture(result);

    if (sourceFiles.count() > 1) {
        Core::ICore::progressManager()->addTask(result, tr("Indexing"),
                        QLatin1String(Constants::TASK_INDEX));
    }

    return result;
}

void ModelManager::fileChangedOnDisk(const QString &path)
{
    QtConcurrent::run(&ModelManager::parse,
                      workingCopy(), QStringList() << path,
                      this, true);
}

void ModelManager::removeFiles(const QStringList &files)
{
    emit aboutToRemoveFiles(files);

    QMutexLocker locker(&m_mutex);

    foreach (const QString &file, files) {
        _validSnapshot.remove(file);
        _newestSnapshot.remove(file);
    }
}

namespace {
bool pInfoLessThanActive(const ModelManager::ProjectInfo &p1, const ModelManager::ProjectInfo &p2)
{
    QStringList s1 = p1.activeResourceFiles;
    QStringList s2 = p2.activeResourceFiles;
    if (s1.size() < s2.size())
        return true;
    if (s1.size() > s2.size())
        return false;
    for (int i = 0; i < s1.size(); ++i) {
        if (s1.at(i) < s2.at(i))
            return true;
        else if (s1.at(i) > s2.at(i))
            return false;
    }
    return false;
}

bool pInfoLessThanAll(const ModelManager::ProjectInfo &p1, const ModelManager::ProjectInfo &p2)
{
    QStringList s1 = p1.allResourceFiles;
    QStringList s2 = p2.allResourceFiles;
    if (s1.size() < s2.size())
        return true;
    if (s1.size() > s2.size())
        return false;
    for (int i = 0; i < s1.size(); ++i) {
        if (s1.at(i) < s2.at(i))
            return true;
        else if (s1.at(i) > s2.at(i))
            return false;
    }
    return false;
}
}

QStringList ModelManager::filesAtQrcPath(const QString &path, const QLocale *locale,
                                         ProjectExplorer::Project *project,
                                         QrcResourceSelector resources)
{
    QString normPath = QrcParser::normalizedQrcFilePath(path);
    QList<ProjectInfo> pInfos;
    if (project)
        pInfos.append(projectInfo(project));
    else
        pInfos = projectInfos();

    QStringList res;
    QSet<QString> pathsChecked;
    foreach (const ModelManager::ProjectInfo &pInfo, pInfos) {
        QStringList qrcFilePaths;
        if (resources == ActiveQrcResources)
            qrcFilePaths = pInfo.activeResourceFiles;
        else
            qrcFilePaths = pInfo.allResourceFiles;
        foreach (const QString &qrcFilePath, qrcFilePaths) {
            if (pathsChecked.contains(qrcFilePath))
                continue;
            pathsChecked.insert(qrcFilePath);
            QrcParser::ConstPtr qrcFile = m_qrcCache.parsedPath(qrcFilePath);
            if (qrcFile.isNull())
                continue;
            qrcFile->collectFilesAtPath(normPath, &res, locale);
        }
    }
    res.sort(); // make the result predictable
    return res;
}

QMap<QString, QStringList> ModelManager::filesInQrcPath(const QString &path,
                                                        const QLocale *locale,
                                                        ProjectExplorer::Project *project,
                                                        bool addDirs,
                                                        QrcResourceSelector resources)
{
    QString normPath = QrcParser::normalizedQrcDirectoryPath(path);
    QList<ProjectInfo> pInfos;
    if (project) {
        pInfos.append(projectInfo(project));
    } else {
        pInfos = projectInfos();
        if (resources == ActiveQrcResources) // make the result predictable
            qSort(pInfos.begin(), pInfos.end(), &pInfoLessThanActive);
        else
            qSort(pInfos.begin(), pInfos.end(), &pInfoLessThanAll);
    }
    QMap<QString, QStringList> res;
    QSet<QString> pathsChecked;
    foreach (const ModelManager::ProjectInfo &pInfo, pInfos) {
        QStringList qrcFilePaths;
        if (resources == ActiveQrcResources)
            qrcFilePaths = pInfo.activeResourceFiles;
        else
            qrcFilePaths = pInfo.allResourceFiles;
        foreach (const QString &qrcFilePath, qrcFilePaths) {
            if (pathsChecked.contains(qrcFilePath))
                continue;
            pathsChecked.insert(qrcFilePath);
            QrcParser::ConstPtr qrcFile = m_qrcCache.parsedPath(qrcFilePath);

            if (qrcFile.isNull())
                continue;
            qrcFile->collectFilesInPath(normPath, &res, addDirs, locale);
        }
    }
    return res;
}

QList<ModelManager::ProjectInfo> ModelManager::projectInfos() const
{
    QMutexLocker locker(&m_mutex);

    return m_projects.values();
}

ModelManager::ProjectInfo ModelManager::projectInfo(ProjectExplorer::Project *project) const
{
    QMutexLocker locker(&m_mutex);

    return m_projects.value(project, ProjectInfo(project));
}

void ModelManager::updateProjectInfo(const ProjectInfo &pinfo)
{
    if (! pinfo.isValid())
        return;

    Snapshot snapshot;
    ProjectInfo oldInfo;
    {
        QMutexLocker locker(&m_mutex);
        oldInfo = m_projects.value(pinfo.project);
        m_projects.insert(pinfo.project, pinfo);
        snapshot = _validSnapshot;
    }

    if (oldInfo.qmlDumpPath != pinfo.qmlDumpPath
            || oldInfo.qmlDumpEnvironment != pinfo.qmlDumpEnvironment) {
        m_pluginDumper->scheduleRedumpPlugins();
        m_pluginDumper->scheduleMaybeRedumpBuiltins(pinfo);
    }


    updateImportPaths();

    // remove files that are no longer in the project and have been deleted
    QStringList deletedFiles;
    foreach (const QString &oldFile, oldInfo.sourceFiles) {
        if (snapshot.document(oldFile)
                && !pinfo.sourceFiles.contains(oldFile)
                && !QFile::exists(oldFile)) {
            deletedFiles += oldFile;
        }
    }
    removeFiles(deletedFiles);

    // parse any files not yet in the snapshot
    QStringList newFiles;
    foreach (const QString &file, pinfo.sourceFiles) {
        if (!snapshot.document(file))
            newFiles += file;
    }
    updateSourceFiles(newFiles, false);

    // update qrc cache
    foreach (const QString &newQrc, pinfo.allResourceFiles)
        m_qrcCache.addPath(newQrc);
    foreach (const QString &oldQrc, oldInfo.allResourceFiles)
        m_qrcCache.removePath(oldQrc);

    // dump builtin types if the shipped definitions are probably outdated and the
    // Qt version ships qmlplugindump
    if (QtSupport::QtVersionNumber(pinfo.qtVersionString) > QtSupport::QtVersionNumber(4, 8, 5))
        m_pluginDumper->loadBuiltinTypes(pinfo);

    emit projectInfoUpdated(pinfo);
}


void ModelManager::removeProjectInfo(ProjectExplorer::Project *project)
{
    ProjectInfo info(project);
    info.sourceFiles.clear();
    // update with an empty project info to clear data
    updateProjectInfo(info);

    {
        QMutexLocker locker(&m_mutex);
        m_projects.remove(project);
    }
}

ModelManagerInterface::ProjectInfo ModelManager::projectInfoForPath(QString path)
{
    QMutexLocker locker(&m_mutex);

    foreach (const ProjectInfo &p, m_projects)
        if (p.sourceFiles.contains(path))
            return p;
    return ProjectInfo();
}

void ModelManager::emitDocumentChangedOnDisk(Document::Ptr doc)
{ emit documentChangedOnDisk(doc); }

void ModelManager::updateQrcFile(const QString &path)
{
    m_qrcCache.updatePath(path);
}

void ModelManager::updateDocument(Document::Ptr doc)
{
    {
        QMutexLocker locker(&m_mutex);
        _validSnapshot.insert(doc);
        _newestSnapshot.insert(doc, true);
    }
    emit documentUpdated(doc);
}

void ModelManager::updateLibraryInfo(const QString &path, const LibraryInfo &info)
{
    {
        QMutexLocker locker(&m_mutex);
        _validSnapshot.insertLibraryInfo(path, info);
        _newestSnapshot.insertLibraryInfo(path, info);
    }
    // only emit if we got new useful information
    if (info.isValid())
        emit libraryInfoUpdated(path, info);
}

static QStringList qmlFilesInDirectory(const QString &path)
{
    const QStringList pattern = qmlAndJsGlobPatterns();
    QStringList files;

    const QDir dir(path);
    foreach (const QFileInfo &fi, dir.entryInfoList(pattern, QDir::Files))
        files += fi.absoluteFilePath();

    return files;
}

static void findNewImplicitImports(const Document::Ptr &doc, const Snapshot &snapshot,
                            QStringList *importedFiles, QSet<QString> *scannedPaths)
{
    // scan files that could be implicitly imported
    // it's important we also do this for JS files, otherwise the isEmpty check will fail
    if (snapshot.documentsInDirectory(doc->path()).isEmpty()) {
        if (! scannedPaths->contains(doc->path())) {
            *importedFiles += qmlFilesInDirectory(doc->path());
            scannedPaths->insert(doc->path());
        }
    }
}

static void findNewFileImports(const Document::Ptr &doc, const Snapshot &snapshot,
                        QStringList *importedFiles, QSet<QString> *scannedPaths)
{
    // scan files and directories that are explicitly imported
    foreach (const ImportInfo &import, doc->bind()->imports()) {
        const QString &importName = import.path();
        if (import.type() == ImportInfo::FileImport) {
            if (! snapshot.document(importName))
                *importedFiles += importName;
        } else if (import.type() == ImportInfo::DirectoryImport) {
            if (snapshot.documentsInDirectory(importName).isEmpty()) {
                if (! scannedPaths->contains(importName)) {
                    *importedFiles += qmlFilesInDirectory(importName);
                    scannedPaths->insert(importName);
                }
            }
        } else if (import.type() == ImportInfo::QrcFileImport) {
            QStringList importPaths = ModelManagerInterface::instance()->filesAtQrcPath(importName);
            foreach (const QString &importPath, importPaths) {
                if (! snapshot.document(importPath))
                    *importedFiles += importPath;
            }
        } else if (import.type() == ImportInfo::QrcDirectoryImport) {
            QMapIterator<QString,QStringList> dirContents(ModelManagerInterface::instance()->filesInQrcPath(importName));
            while (dirContents.hasNext()) {
                dirContents.next();
                if (Document::isQmlLikeOrJsLanguage(Document::guessLanguageFromSuffix(dirContents.key()))) {
                    foreach (const QString &filePath, dirContents.value()) {
                        if (! snapshot.document(filePath))
                            *importedFiles += filePath;
                    }
                }
            }
        }
    }
}

static bool findNewQmlLibraryInPath(const QString &path,
                                    const Snapshot &snapshot,
                                    ModelManager *modelManager,
                                    QStringList *importedFiles,
                                    QSet<QString> *scannedPaths,
                                    QSet<QString> *newLibraries)
{
    // if we know there is a library, done
    const LibraryInfo &existingInfo = snapshot.libraryInfo(path);
    if (existingInfo.isValid())
        return true;
    if (newLibraries->contains(path))
        return true;
    // if we looked at the path before, done
    if (existingInfo.wasScanned())
        return false;

    const QDir dir(path);
    QFile qmldirFile(dir.filePath(QLatin1String("qmldir")));
    if (!qmldirFile.exists()) {
        LibraryInfo libraryInfo(LibraryInfo::NotFound);
        modelManager->updateLibraryInfo(path, libraryInfo);
        return false;
    }

    if (Utils::HostOsInfo::isWindowsHost()) {
        // QTCREATORBUG-3402 - be case sensitive even here?
    }

    // found a new library!
    qmldirFile.open(QFile::ReadOnly);
    QString qmldirData = QString::fromUtf8(qmldirFile.readAll());

    QmlDirParser qmldirParser;
    qmldirParser.parse(qmldirData);

    const QString libraryPath = QFileInfo(qmldirFile).absolutePath();
    newLibraries->insert(libraryPath);
    modelManager->updateLibraryInfo(libraryPath, LibraryInfo(qmldirParser));

    // scan the qml files in the library
    foreach (const QmlDirParser::Component &component, qmldirParser.components()) {
        if (! component.fileName.isEmpty()) {
            const QFileInfo componentFileInfo(dir.filePath(component.fileName));
            const QString path = QDir::cleanPath(componentFileInfo.absolutePath());
            if (! scannedPaths->contains(path)) {
                *importedFiles += qmlFilesInDirectory(path);
                scannedPaths->insert(path);
            }
        }
    }

    return true;
}

static void findNewQmlLibrary(
    const QString &path,
    const LanguageUtils::ComponentVersion &version,
    const Snapshot &snapshot,
    ModelManager *modelManager,
    QStringList *importedFiles,
    QSet<QString> *scannedPaths,
    QSet<QString> *newLibraries)
{
    QString libraryPath = QString::fromLatin1("%1.%2.%3").arg(
                path,
                QString::number(version.majorVersion()),
                QString::number(version.minorVersion()));
    findNewQmlLibraryInPath(
                libraryPath, snapshot, modelManager,
                importedFiles, scannedPaths, newLibraries);

    libraryPath = QString::fromLatin1("%1.%2").arg(
                path,
                QString::number(version.majorVersion()));
    findNewQmlLibraryInPath(
                libraryPath, snapshot, modelManager,
                importedFiles, scannedPaths, newLibraries);

    findNewQmlLibraryInPath(
                path, snapshot, modelManager,
                importedFiles, scannedPaths, newLibraries);
}

static void findNewLibraryImports(const Document::Ptr &doc, const Snapshot &snapshot,
                           ModelManager *modelManager,
                           QStringList *importedFiles, QSet<QString> *scannedPaths, QSet<QString> *newLibraries)
{
    // scan current dir
    findNewQmlLibraryInPath(doc->path(), snapshot, modelManager,
                            importedFiles, scannedPaths, newLibraries);

    // scan dir and lib imports
    const QStringList importPaths = modelManager->importPaths();
    foreach (const ImportInfo &import, doc->bind()->imports()) {
        if (import.type() == ImportInfo::DirectoryImport) {
            const QString targetPath = import.path();
            findNewQmlLibraryInPath(targetPath, snapshot, modelManager,
                                    importedFiles, scannedPaths, newLibraries);
        }

        if (import.type() == ImportInfo::LibraryImport) {
            if (!import.version().isValid())
                continue;
            foreach (const QString &importPath, importPaths) {
                const QString targetPath = QDir(importPath).filePath(import.path());
                findNewQmlLibrary(targetPath, import.version(), snapshot, modelManager,
                                  importedFiles, scannedPaths, newLibraries);
            }
        }
    }
}

void ModelManager::parse(QFutureInterface<void> &future,
                            WorkingCopy workingCopy,
                            QStringList files,
                            ModelManager *modelManager,
                            bool emitDocChangedOnDisk)
{
    int progressRange = files.size();
    future.setProgressRange(0, progressRange);

    // paths we have scanned for files and added to the files list
    QSet<QString> scannedPaths;
    // libraries we've found while scanning imports
    QSet<QString> newLibraries;

    for (int i = 0; i < files.size(); ++i) {
        future.setProgressValue(qreal(i) / files.size() * progressRange);

        const QString fileName = files.at(i);

        Document::Language language = languageOfFile(fileName);
        if (language == Document::UnknownLanguage) {
            if (fileName.endsWith(QLatin1String(".qrc")))
                modelManager->updateQrcFile(fileName);
            continue;
        }

        QString contents;
        int documentRevision = 0;

        if (workingCopy.contains(fileName)) {
            QPair<QString, int> entry = workingCopy.get(fileName);
            contents = entry.first;
            documentRevision = entry.second;
        } else {
            QFile inFile(fileName);

            if (inFile.open(QIODevice::ReadOnly)) {
                QTextStream ins(&inFile);
                contents = ins.readAll();
                inFile.close();
            }
        }

        Document::MutablePtr doc = Document::create(fileName, language);
        doc->setEditorRevision(documentRevision);
        doc->setSource(contents);
        doc->parse();

        // update snapshot. requires synchronization, but significantly reduces amount of file
        // system queries for library imports because queries are cached in libraryInfo
        const Snapshot snapshot = modelManager->snapshot();

        // get list of referenced files not yet in snapshot or in directories already scanned
        QStringList importedFiles;
        findNewImplicitImports(doc, snapshot, &importedFiles, &scannedPaths);
        findNewFileImports(doc, snapshot, &importedFiles, &scannedPaths);
        findNewLibraryImports(doc, snapshot, modelManager, &importedFiles, &scannedPaths, &newLibraries);

        // add new files to parse list
        foreach (const QString &file, importedFiles) {
            if (! files.contains(file))
                files.append(file);
        }

        modelManager->updateDocument(doc);
        if (emitDocChangedOnDisk)
            modelManager->emitDocumentChangedOnDisk(doc);
    }

    future.setProgressValue(progressRange);
}

// Check whether fileMimeType is the same or extends knownMimeType
bool ModelManager::matchesMimeType(const Core::MimeType &fileMimeType, const Core::MimeType &knownMimeType)
{
    Core::MimeDatabase *db = Core::ICore::mimeDatabase();

    const QStringList knownTypeNames = QStringList(knownMimeType.type()) + knownMimeType.aliases();

    foreach (const QString &knownTypeName, knownTypeNames)
        if (fileMimeType.matchesType(knownTypeName))
            return true;

    // recursion to parent types of fileMimeType
    foreach (const QString &parentMimeType, fileMimeType.subClassesOf()) {
        if (matchesMimeType(db->findByType(parentMimeType), knownMimeType))
            return true;
    }

    return false;
}

QStringList ModelManager::importPaths() const
{
    QMutexLocker l(&m_mutex);
    return m_allImportPaths;
}

QmlLanguageBundles ModelManager::activeBundles() const
{
    QMutexLocker l(&m_mutex);
    return m_activeBundles;
}

QmlLanguageBundles ModelManager::extendedBundles() const
{
    QMutexLocker l(&m_mutex);
    return m_extendedBundles;
}

static QStringList environmentImportPaths()
{
    QStringList paths;

    QByteArray envImportPath = qgetenv("QML_IMPORT_PATH");

    foreach (const QString &path, QString::fromLatin1(envImportPath)
             .split(Utils::HostOsInfo::pathListSeparator(), QString::SkipEmptyParts)) {
        QString canonicalPath = QDir(path).canonicalPath();
        if (!canonicalPath.isEmpty() && !paths.contains(canonicalPath))
            paths.append(canonicalPath);
    }

    return paths;
}

void ModelManager::updateImportPaths()
{
    QStringList allImportPaths;
    QmlLanguageBundles activeBundles;
    QmlLanguageBundles extendedBundles;
    QMapIterator<ProjectExplorer::Project *, ProjectInfo> it(m_projects);
    while (it.hasNext()) {
        it.next();
        foreach (const QString &path, it.value().importPaths) {
            const QString canonicalPath = QFileInfo(path).canonicalFilePath();
            if (!canonicalPath.isEmpty())
                allImportPaths += canonicalPath;
        }
    }
    it.toFront();
    while (it.hasNext()) {
        it.next();
        activeBundles.mergeLanguageBundles(it.value().activeBundle);
        foreach (Document::Language l, it.value().activeBundle.languages()) {
            foreach (const QString &path, it.value().activeBundle.bundleForLanguage(l)
                 .searchPaths().stringList()) {
                const QString canonicalPath = QFileInfo(path).canonicalFilePath();
                if (!canonicalPath.isEmpty())
                    allImportPaths += canonicalPath;
            }
        }
    }
    it.toFront();
    while (it.hasNext()) {
        it.next();
        extendedBundles.mergeLanguageBundles(it.value().extendedBundle);
        foreach (Document::Language l, it.value().extendedBundle.languages()) {
            foreach (const QString &path, it.value().extendedBundle.bundleForLanguage(l)
                     .searchPaths().stringList()) {
                const QString canonicalPath = QFileInfo(path).canonicalFilePath();
                if (!canonicalPath.isEmpty())
                    allImportPaths += canonicalPath;
            }
        }
    }
    allImportPaths += m_defaultImportPaths;
    allImportPaths.removeDuplicates();

    {
        QMutexLocker l(&m_mutex);
        m_allImportPaths = allImportPaths;
        m_activeBundles = activeBundles;
        m_extendedBundles = extendedBundles;
    }


    // check if any file in the snapshot imports something new in the new paths
    Snapshot snapshot = _validSnapshot;
    QStringList importedFiles;
    QSet<QString> scannedPaths;
    QSet<QString> newLibraries;
    foreach (const Document::Ptr &doc, snapshot)
        findNewLibraryImports(doc, snapshot, this, &importedFiles, &scannedPaths, &newLibraries);

    updateSourceFiles(importedFiles, true);
}

void ModelManager::loadPluginTypes(const QString &libraryPath, const QString &importPath,
                                   const QString &importUri, const QString &importVersion)
{
    m_pluginDumper->loadPluginTypes(libraryPath, importPath, importUri, importVersion);
}

// is called *inside a c++ parsing thread*, to allow hanging on to source and ast
void ModelManager::maybeQueueCppQmlTypeUpdate(const CPlusPlus::Document::Ptr &doc)
{
    // avoid scanning documents without source code available
    doc->keepSourceAndAST();
    if (doc->utf8Source().isEmpty()) {
        doc->releaseSourceAndAST();
        return;
    }

    // keep source and AST alive if we want to scan for register calls
    const bool scan = FindExportedCppTypes::maybeExportsTypes(doc);
    if (!scan)
        doc->releaseSourceAndAST();

    // delegate actual queuing to the gui thread
    QMetaObject::invokeMethod(this, "queueCppQmlTypeUpdate",
                              Q_ARG(CPlusPlus::Document::Ptr, doc), Q_ARG(bool, scan));
}

void ModelManager::queueCppQmlTypeUpdate(const CPlusPlus::Document::Ptr &doc, bool scan)
{
    QPair<CPlusPlus::Document::Ptr, bool> prev = m_queuedCppDocuments.value(doc->fileName());
    if (prev.first && prev.second)
        prev.first->releaseSourceAndAST();
    m_queuedCppDocuments.insert(doc->fileName(), qMakePair(doc, scan));
    m_updateCppQmlTypesTimer->start();
}

void ModelManager::startCppQmlTypeUpdate()
{
    // if a future is still running, delay
    if (m_cppQmlTypesUpdater.isRunning()) {
        m_updateCppQmlTypesTimer->start();
        return;
    }

    CppTools::CppModelManagerInterface *cppModelManager =
            CppTools::CppModelManagerInterface::instance();
    if (!cppModelManager)
        return;

    m_cppQmlTypesUpdater = QtConcurrent::run(
                &ModelManager::updateCppQmlTypes,
                this, cppModelManager->snapshot(), m_queuedCppDocuments);
    m_queuedCppDocuments.clear();
}

void ModelManager::asyncReset()
{
    m_asyncResetTimer->start();
}

void ModelManager::updateCppQmlTypes(QFutureInterface<void> &interface,
                                     ModelManager *qmlModelManager,
                                     CPlusPlus::Snapshot snapshot,
                                     QHash<QString, QPair<CPlusPlus::Document::Ptr, bool> > documents)
{
    CppDataHash newData = qmlModelManager->cppData();

    FindExportedCppTypes finder(snapshot);

    bool hasNewInfo = false;
    typedef QPair<CPlusPlus::Document::Ptr, bool> DocScanPair;
    foreach (const DocScanPair &pair, documents) {
        if (interface.isCanceled())
            return;

        CPlusPlus::Document::Ptr doc = pair.first;
        const bool scan = pair.second;
        const QString fileName = doc->fileName();
        if (!scan) {
            hasNewInfo = hasNewInfo || newData.remove(fileName) > 0;
            continue;
        }

        finder(doc);

        QList<LanguageUtils::FakeMetaObject::ConstPtr> exported = finder.exportedTypes();
        QHash<QString, QString> contextProperties = finder.contextProperties();
        if (exported.isEmpty() && contextProperties.isEmpty()) {
            hasNewInfo = hasNewInfo || newData.remove(fileName) > 0;
        } else {
            CppData &data = newData[fileName];
            // currently we have no simple way to compare, so we assume the worse
            hasNewInfo = true;
            data.exportedTypes = exported;
            data.contextProperties = contextProperties;
        }

        doc->releaseSourceAndAST();
    }

    QMutexLocker locker(&qmlModelManager->m_cppDataMutex);
    qmlModelManager->m_cppDataHash = newData;
    if (hasNewInfo)
        // one could get away with re-linking the cpp types...
        QMetaObject::invokeMethod(qmlModelManager, "asyncReset");
}

ModelManager::CppDataHash ModelManager::cppData() const
{
    QMutexLocker locker(&m_cppDataMutex);
    return m_cppDataHash;
}

LibraryInfo ModelManager::builtins(const Document::Ptr &doc) const
{
    ProjectExplorer::SessionManager *sessionManager = ProjectExplorer::ProjectExplorerPlugin::instance()->session();
    ProjectExplorer::Project *project = sessionManager->projectForFile(doc->fileName());
    if (!project)
        return LibraryInfo();

    QMutexLocker locker(&m_mutex);
    ProjectInfo info = m_projects.value(project);
    if (!info.isValid())
        return LibraryInfo();

    return _validSnapshot.libraryInfo(info.qtImportsPath);
}

void ModelManager::joinAllThreads()
{
    foreach (QFuture<void> future, m_synchronizer.futures())
        future.waitForFinished();
}

void ModelManager::resetCodeModel()
{
    QStringList documents;

    {
        QMutexLocker locker(&m_mutex);

        // find all documents currently in the code model
        foreach (Document::Ptr doc, _validSnapshot)
            documents.append(doc->fileName());

        // reset the snapshot
        _validSnapshot = Snapshot();
        _newestSnapshot = Snapshot();
    }

    // start a reparse thread
    updateSourceFiles(documents, false);
}
