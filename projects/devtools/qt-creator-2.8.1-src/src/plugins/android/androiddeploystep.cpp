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

#include "androiddeploystep.h"

#include "androidconstants.h"
#include "androiddeploystepwidget.h"
#include "androidglobal.h"
#include "androidpackagecreationstep.h"
#include "androidrunconfiguration.h"
#include "androidmanager.h"
#include "androidtoolchain.h"

#include <coreplugin/messagemanager.h>
#include <projectexplorer/buildconfiguration.h>
#include <projectexplorer/projectexplorerconstants.h>
#include <projectexplorer/target.h>
#include <qt4projectmanager/qt4buildconfiguration.h>
#include <qt4projectmanager/qt4project.h>
#include <qt4projectmanager/qt4nodes.h>

#include <qtsupport/qtkitinformation.h>

#include <QDir>

#define ASSERT_STATE(state) ASSERT_STATE_GENERIC(State, state, m_state)

using namespace ProjectExplorer;
using namespace Qt4ProjectManager;

namespace Android {
namespace Internal {

static const char USE_LOCAL_QT_KEY[] = "Qt4ProjectManager.AndroidDeployStep.UseLocalQtLibs";
static const char DEPLOY_ACTION_KEY[] = "Qt4ProjectManager.AndroidDeployStep.DeployAction";

const Core::Id AndroidDeployStep::Id("Qt4ProjectManager.AndroidDeployStep");

AndroidDeployStep::AndroidDeployStep(ProjectExplorer::BuildStepList *parent)
    : BuildStep(parent, Id)
{
    ctor();
}

AndroidDeployStep::AndroidDeployStep(ProjectExplorer::BuildStepList *parent,
    AndroidDeployStep *other)
    : BuildStep(parent, other)
{
    ctor();
}

AndroidDeployStep::~AndroidDeployStep() { }

void AndroidDeployStep::ctor()
{
    //: AndroidDeployStep default display name
    setDefaultDisplayName(tr("Deploy to Android device"));
    m_deployAction = NoDeploy;

    QtSupport::BaseQtVersion *qt = QtSupport::QtKitInformation::qtVersion(target()->kit());
    m_bundleQtAvailable = qt && qt->qtVersion() >= QtSupport::QtVersionNumber(5, 0, 0);
    if (m_bundleQtAvailable)
        m_deployAction = BundleLibraries;


    connect(ProjectExplorer::KitManager::instance(), SIGNAL(kitUpdated(ProjectExplorer::Kit*)),
            this, SLOT(kitUpdated(ProjectExplorer::Kit *)));
}

bool AndroidDeployStep::init()
{
    m_packageName = AndroidManager::packageName(target());
    const QString targetSDK = AndroidManager::targetSDK(target());
    const QString targetArch = AndroidManager::targetArch(target());

    writeOutput(tr("Please wait, searching for a suitable device for target:%1.").arg(targetSDK));
    m_deviceAPILevel = targetSDK.mid(targetSDK.indexOf(QLatin1Char('-')) + 1).toInt();
    m_deviceSerialNumber = AndroidConfigurations::instance().getDeployDeviceSerialNumber(&m_deviceAPILevel, targetArch);
    if (!m_deviceSerialNumber.length()) {
        m_deviceSerialNumber.clear();
        raiseError(tr("Cannot deploy: no devices or emulators found for your package."));
        return false;
    }

    QtSupport::BaseQtVersion *version = QtSupport::QtKitInformation::qtVersion(target()->kit());
    if (!version)
        return false;

    const Qt4BuildConfiguration *bc = static_cast<Qt4BuildConfiguration *>(target()->activeBuildConfiguration());
    if (!bc)
        return false;

    m_qtVersionSourcePath = version->sourcePath().toString();
    m_qtVersionQMakeBuildConfig = bc->qmakeBuildConfiguration();
    m_androidDirPath = AndroidManager::dirPath(target());
    m_apkPathDebug = AndroidManager::apkPath(target(), AndroidManager::DebugBuild).toString();
    m_apkPathRelease = AndroidManager::apkPath(target(), AndroidManager::ReleaseBuildSigned).toString();
    m_buildDirectory = static_cast<Qt4Project *>(target()->project())->rootQt4ProjectNode()->buildDir();
    m_runDeployAction = m_deployAction;
    ToolChain *tc = ToolChainKitInformation::toolChain(target()->kit());
    if (!tc || tc->type() != QLatin1String(Constants::ANDROID_TOOLCHAIN_TYPE)) {
        raiseError(tr("No Android toolchain selected."));
        return false;
    }
    m_ndkToolChainVersion = static_cast<AndroidToolChain *>(tc)->ndkToolChainVersion();

    QString arch = static_cast<Qt4Project *>(project())->rootQt4ProjectNode()->singleVariableValue(Qt4ProjectManager::AndroidArchVar);
    if (!arch.isEmpty())
        m_libgnustl = AndroidManager::libGnuStl(arch, m_ndkToolChainVersion);
    return true;
}

void AndroidDeployStep::run(QFutureInterface<bool> &fi)
{
    fi.reportResult(deployPackage());
}

BuildStepConfigWidget *AndroidDeployStep::createConfigWidget()
{
    return new AndroidDeployStepWidget(this);
}

AndroidDeployStep::AndroidDeployAction AndroidDeployStep::deployAction()
{
    return m_deployAction;
}

bool AndroidDeployStep::fromMap(const QVariantMap &map)
{
    m_deployAction = AndroidDeployAction(map.value(QLatin1String(DEPLOY_ACTION_KEY), NoDeploy).toInt());
    QVariant useLocalQt = map.value(QLatin1String(USE_LOCAL_QT_KEY));
    if (useLocalQt.isValid()) { // old settings
        if (useLocalQt.toBool() && m_deployAction == NoDeploy)
            m_deployAction = BundleLibraries;
    }

    if (m_deployAction == InstallQASI)
        m_deployAction = NoDeploy;
    QtSupport::BaseQtVersion *qtVersion
            = QtSupport::QtKitInformation::qtVersion(target()->kit());
    if (m_deployAction == BundleLibraries)
        if (!qtVersion || qtVersion->qtVersion() < QtSupport::QtVersionNumber(5, 0, 0))
            m_deployAction = NoDeploy; // the kit changed to a non qt5 kit

    m_bundleQtAvailable = qtVersion && qtVersion->qtVersion() >= QtSupport::QtVersionNumber(5, 0, 0);

    return ProjectExplorer::BuildStep::fromMap(map);
}

QVariantMap AndroidDeployStep::toMap() const
{
    QVariantMap map = ProjectExplorer::BuildStep::toMap();
    map.insert(QLatin1String(DEPLOY_ACTION_KEY), m_deployAction);
    return map;
}

void AndroidDeployStep::cleanLibsOnDevice()
{
    const QString targetSDK = AndroidManager::targetSDK(target());
    const QString targetArch = AndroidManager::targetArch(target());

    int deviceAPILevel = targetSDK.mid(targetSDK.indexOf(QLatin1Char('-')) + 1).toInt();
    QString deviceSerialNumber = AndroidConfigurations::instance().getDeployDeviceSerialNumber(&deviceAPILevel, targetArch);
    if (!deviceSerialNumber.length()) {
        Core::MessageManager::instance()->printToOutputPane(tr("Could not run adb. No device found."), Core::MessageManager::NoModeSwitch);
        return;
    }
    QProcess *process = new QProcess(this);
    QStringList arguments = AndroidDeviceInfo::adbSelector(deviceSerialNumber);
    arguments << QLatin1String("shell") << QLatin1String("rm") << QLatin1String("-r") << QLatin1String("/data/local/tmp/qt");
    connect(process, SIGNAL(finished(int)), this, SLOT(processFinished()));
    const QString adb = AndroidConfigurations::instance().adbToolPath().toString();
    Core::MessageManager::instance()->printToOutputPane(adb + QLatin1String(" ")
                                                        + arguments.join(QLatin1String(" ")),
                                                        Core::MessageManager::NoModeSwitch);
    process->start(adb, arguments);
    if (!process->waitForStarted(500))
        delete process;
}

void AndroidDeployStep::processFinished()
{
    QProcess *process = qobject_cast<QProcess *>(sender());
    QTC_ASSERT(process, return);
    Core::MessageManager::instance()->printToOutputPane(QString::fromLocal8Bit(process->readAll()), Core::MessageManager::NoModeSwitch);
    Core::MessageManager::instance()->printToOutputPane(tr("adb finished with exit code %1.").arg(process->exitCode()),
                                                        Core::MessageManager::NoModeSwitch);
    process->deleteLater();
}

void AndroidDeployStep::kitUpdated(Kit *kit)
{
    if (kit != target()->kit())
        return;
    QtSupport::BaseQtVersion *qtVersion
            = QtSupport::QtKitInformation::qtVersion(target()->kit());

    bool newBundleQtAvailable = qtVersion && qtVersion->qtVersion() >= QtSupport::QtVersionNumber(5, 0, 0);
    if (m_bundleQtAvailable != newBundleQtAvailable) {
        m_bundleQtAvailable = newBundleQtAvailable;

        if (!m_bundleQtAvailable && m_deployAction == BundleLibraries)
            m_deployAction = NoDeploy; // the kit changed to a non qt5 kit

        emit deployOptionsChanged();
    }
}

void AndroidDeployStep::installQASIPackage(const QString &packagePath)
{
    const QString targetArch = AndroidManager::targetArch(target());
    const QString targetSDK = AndroidManager::targetSDK(target());
    int deviceAPILevel = targetSDK.mid(targetSDK.indexOf(QLatin1Char('-')) + 1).toInt();
    QString deviceSerialNumber = AndroidConfigurations::instance().getDeployDeviceSerialNumber(&deviceAPILevel, targetArch);
    if (!deviceSerialNumber.length()) {
        Core::MessageManager::instance()->printToOutputPane(tr("Could not run adb. No device found."), Core::MessageManager::NoModeSwitch);
        return;
    }

    QProcess *process = new QProcess(this);
    QStringList arguments = AndroidDeviceInfo::adbSelector(deviceSerialNumber);
    arguments << QLatin1String("install") << QLatin1String("-r ") << packagePath;

    connect(process, SIGNAL(finished(int)), this, SLOT(processFinished()));
    const QString adb = AndroidConfigurations::instance().adbToolPath().toString();
    Core::MessageManager::instance()->printToOutputPane(adb + QLatin1String(" ")
                                                        + arguments.join(QLatin1String(" ")),
                                                        Core::MessageManager::NoModeSwitch);
    process->start(adb, arguments);
    if (!process->waitForFinished(500))
        delete process;
}

bool AndroidDeployStep::bundleQtOptionAvailable()
{
    return m_bundleQtAvailable;
}

void AndroidDeployStep::setDeployAction(AndroidDeployStep::AndroidDeployAction deploy)
{
    m_deployAction = deploy;

    AndroidManager::updateDeploymentSettings(target());
}

bool AndroidDeployStep::runCommand(QProcess *buildProc,
    const QString &program, const QStringList &arguments)
{
    writeOutput(tr("Package deploy: Running command '%1 %2'.").arg(program).arg(arguments.join(QLatin1String(" "))), BuildStep::MessageOutput);
    buildProc->start(program, arguments);
    if (!buildProc->waitForStarted()) {
        writeOutput(tr("Packaging error: Could not start command '%1 %2'. Reason: %3")
            .arg(program).arg(arguments.join(QLatin1String(" "))).arg(buildProc->errorString()), BuildStep::ErrorMessageOutput);
        return false;
    }
    buildProc->waitForFinished(-1);
    if (buildProc->error() != QProcess::UnknownError
            || buildProc->exitCode() != 0) {
        QString mainMessage = tr("Packaging Error: Command '%1 %2' failed.")
                .arg(program).arg(arguments.join(QLatin1String(" ")));
        if (buildProc->error() != QProcess::UnknownError)
            mainMessage += tr(" Reason: %1").arg(buildProc->errorString());
        else
            mainMessage += tr("Exit code: %1").arg(buildProc->exitCode());
        writeOutput(mainMessage, BuildStep::ErrorMessageOutput);
        return false;
    }
    return true;
}

void AndroidDeployStep::handleBuildOutput()
{
    QProcess *const buildProc = qobject_cast<QProcess *>(sender());
    if (!buildProc)
        return;
    emit addOutput(QString::fromLocal8Bit(buildProc->readAllStandardOutput())
                   , BuildStep::NormalOutput);
}

void AndroidDeployStep::handleBuildError()
{
    QProcess *const buildProc = qobject_cast<QProcess *>(sender());
    if (!buildProc)
        return;
    emit addOutput(QString::fromLocal8Bit(buildProc->readAllStandardError())
                   , BuildStep::ErrorOutput);
}

QString AndroidDeployStep::deviceSerialNumber()
{
    return m_deviceSerialNumber;
}

int AndroidDeployStep::deviceAPILevel()
{
    return m_deviceAPILevel;
}

unsigned int AndroidDeployStep::remoteModificationTime(const QString &fullDestination, QHash<QString, unsigned int> *cache)
{
    QString destination = QFileInfo(fullDestination).absolutePath();
    QProcess process;
    QHash<QString, unsigned int>::const_iterator it = cache->find(fullDestination);
    if (it != cache->constEnd())
        return *it;
    QStringList arguments = AndroidDeviceInfo::adbSelector(m_deviceSerialNumber);
    arguments << QLatin1String("ls") << destination;
    process.start(AndroidConfigurations::instance().adbToolPath().toString(), arguments);
    process.waitForFinished(-1);
    if (process.error() != QProcess::UnknownError
            || process.exitCode() != 0)
        return -1;
    QByteArray output = process.readAll();
    output.replace("\r\n", "\n");
    QList<QByteArray> lines = output.split('\n');
    foreach (const QByteArray &line, lines) {
        // do some checks if we got what we expected..
        if (line.count() < (3 * 8 + 3))
            continue;
        if (line.at(8) != ' '
                || line.at(17) != ' '
                || line.at(26) != ' ')
            continue;
        bool ok;
        int time = line.mid(18, 8).toUInt(&ok, 16);
        if (!ok)
            continue;
        QString fileName = QString::fromLocal8Bit(line.mid(27));
        cache->insert(destination + QLatin1Char('/') + fileName, time);
    }
    it = cache->find(fullDestination);
    if (it != cache->constEnd())
        return *it;
    return 0;
}

void AndroidDeployStep::collectFiles(QList<DeployItem> *deployList, const QString &localPath, const QString &remotePath,
                  bool strip, const QStringList &filter)
{
    QDirIterator libsIt(localPath, filter, QDir::NoFilter, QDirIterator::Subdirectories);
    int pos = localPath.size();
    while (libsIt.hasNext()) {
        libsIt.next();
        const QString destFile(remotePath + libsIt.filePath().mid(pos));
        if (!libsIt.fileInfo().isDir()) {
            deployList->append(DeployItem(libsIt.filePath(),
                                          libsIt.fileInfo().lastModified().toTime_t(),
                                          destFile, strip));
        }
    }
}

void AndroidDeployStep::fetchRemoteModificationTimes(QList<DeployItem> *deployList)
{
    QHash<QString, unsigned int> cache;
    for (int i = 0; i < deployList->count(); ++i) {
        DeployItem &item = (*deployList)[i];
        item.remoteTimeStamp
                = remoteModificationTime(item.remoteFileName, &cache);
    }
}

void AndroidDeployStep::filterModificationTimes(QList<DeployItem> *deployList)
{
    QList<DeployItem>::iterator it = deployList->begin();
    while (it != deployList->end()) {
        int index = it - deployList->begin();
        Q_UNUSED(index);
        if ((*it).localTimeStamp <= (*it).remoteTimeStamp)
            it = deployList->erase(it);
        else
            ++it;
    }
}

void AndroidDeployStep::copyFilesToTemp(QList<DeployItem> *deployList, const QString &tempDirectory, const QString &sourcePrefix)
{
    QDir dir;

    int pos = sourcePrefix.size();
    for (int i = 0; i < deployList->count(); ++i) {
        DeployItem &item = (*deployList)[i];
        if (!item.needsStrip)
            continue;
        const QString destFile(tempDirectory + item.localFileName.mid(pos));
        dir.mkpath(QFileInfo(destFile).absolutePath());
        QFile::copy(item.localFileName, destFile);
        item.localFileName = destFile;
    }
}

void AndroidDeployStep::stripFiles(const QList<DeployItem> &deployList, Abi::Architecture architecture, const QString &ndkToolchainVersion)
{
    QProcess stripProcess;
    foreach (const DeployItem &item, deployList) {
        stripProcess.start(AndroidConfigurations::instance().stripPath(architecture, ndkToolchainVersion).toString(),
                           QStringList()<<QLatin1String("--strip-unneeded") << item.localFileName);
        stripProcess.waitForStarted();
        if (!stripProcess.waitForFinished())
            stripProcess.kill();
    }
}

void AndroidDeployStep::deployFiles(QProcess *process, const QList<DeployItem> &deployList)
{
    foreach (const DeployItem &item, deployList) {
        runCommand(process, AndroidConfigurations::instance().adbToolPath().toString(),
                   AndroidDeviceInfo::adbSelector(m_deviceSerialNumber)
                   << QLatin1String("push") << item.localFileName
                   << item.remoteFileName);
    }
}

bool AndroidDeployStep::deployPackage()
{
    QProcess *const deployProc = new QProcess;
    connect(deployProc, SIGNAL(readyReadStandardOutput()), this,
        SLOT(handleBuildOutput()));
    connect(deployProc, SIGNAL(readyReadStandardError()), this,
        SLOT(handleBuildError()));

    if (m_runDeployAction == DeployLocal) {
        writeOutput(tr("Deploy Qt libraries. This may take some time, please wait."));
        const QString tempPath = QDir::tempPath() + QLatin1String("/android_qt_libs_") + m_packageName;
        AndroidPackageCreationStep::removeDirectory(tempPath);

        const QString remoteRoot = QLatin1String("/data/local/tmp/qt");
        QList<DeployItem> deployList;
        collectFiles(&deployList,
                     m_qtVersionSourcePath + QLatin1String("/lib"),
                     remoteRoot + QLatin1String("/lib"),
                     true,
                     QStringList() << QLatin1String("*.so"));

        // don't use the libgnustl_shared.so from the qt directory
        for (int i = 0; i < deployList.count(); ++i) {
            if (deployList.at(i).remoteFileName == QLatin1String("/data/local/tmp/qt/lib/libgnustl_shared.so")) {
                deployList.removeAt(i);
                break;
            }
        }

        // We want to deploy that *always*
        // since even if the timestamps did not change, the toolchain might have changed
        // leading to a different file
        deployList.append(DeployItem(m_libgnustl,
                                     QDateTime::currentDateTimeUtc().toTime_t(),
                                     QLatin1String("/data/local/tmp/qt/lib/libgnustl_shared.so"), false));

        collectFiles(&deployList,
                     m_qtVersionSourcePath + QLatin1String("/plugins"),
                     remoteRoot + QLatin1String("/plugins"),
                     true);
        collectFiles(&deployList,
                     m_qtVersionSourcePath + QLatin1String("/imports"),
                     remoteRoot + QLatin1String("/imports"),
                     true);
        collectFiles(&deployList,
                     m_qtVersionSourcePath + QLatin1String("/qml"),
                     remoteRoot + QLatin1String("/qml"),
                     true);
        collectFiles(&deployList,
                     m_qtVersionSourcePath + QLatin1String("/jar"),
                     remoteRoot + QLatin1String("/jar"),
                     true);

        fetchRemoteModificationTimes(&deployList);
        filterModificationTimes(&deployList);
        copyFilesToTemp(&deployList, tempPath, m_qtVersionSourcePath);
        stripFiles(deployList, target()->activeRunConfiguration()->abi().architecture(), m_ndkToolChainVersion);
        deployFiles(deployProc, deployList);

        AndroidPackageCreationStep::removeDirectory(tempPath);
    }

    deployProc->setWorkingDirectory(m_androidDirPath.toString());

    writeOutput(tr("Installing package onto %1.").arg(m_deviceSerialNumber));
    runCommand(deployProc, AndroidConfigurations::instance().adbToolPath().toString(),
               AndroidDeviceInfo::adbSelector(m_deviceSerialNumber) << QLatin1String("uninstall") << m_packageName);
    QString package = m_apkPathDebug;

    if (!(m_qtVersionQMakeBuildConfig & QtSupport::BaseQtVersion::DebugBuild)
         && QFile::exists(m_apkPathRelease))
        package = m_apkPathRelease;

    if (!runCommand(deployProc, AndroidConfigurations::instance().adbToolPath().toString(),
                    AndroidDeviceInfo::adbSelector(m_deviceSerialNumber) << QLatin1String("install") << package)) {
        raiseError(tr("Package installation failed."));
        disconnect(deployProc, 0, this, 0);
        deployProc->deleteLater();
        return false;
    }

    writeOutput(tr("Pulling files necessary for debugging."));
    runCommand(deployProc, AndroidConfigurations::instance().adbToolPath().toString(),
               AndroidDeviceInfo::adbSelector(m_deviceSerialNumber)
               << QLatin1String("pull") << QLatin1String("/system/bin/app_process")
               << QString::fromLatin1("%1/app_process").arg(m_buildDirectory));
    runCommand(deployProc, AndroidConfigurations::instance().adbToolPath().toString(),
               AndroidDeviceInfo::adbSelector(m_deviceSerialNumber) << QLatin1String("pull")
               << QLatin1String("/system/lib/libc.so")
               << QString::fromLatin1("%1/libc.so").arg(m_buildDirectory));
    disconnect(deployProc, 0, this, 0);
    deployProc->deleteLater();
    return true;
}

void AndroidDeployStep::raiseError(const QString &errorString)
{
    emit addTask(Task(Task::Error, errorString, Utils::FileName::fromString(QString()), -1,
        ProjectExplorer::Constants::TASK_CATEGORY_BUILDSYSTEM));
}

void AndroidDeployStep::writeOutput(const QString &text, OutputFormat format)
{
    emit addOutput(text, format);
}

} // namespace Internal
} // namespace Qt4ProjectManager
