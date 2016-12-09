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

#include "blackberrydeviceconfigurationwizardpages.h"
#include "blackberryconfiguration.h"
#include "blackberrydebugtokenrequestdialog.h"
#include "blackberrysshkeysgenerator.h"
#include "ui_blackberrydeviceconfigurationwizardsetuppage.h"
#include "ui_blackberrydeviceconfigurationwizardsshkeypage.h"
#include "blackberryconfiguration.h"
#include "qnxutils.h"

#include <coreplugin/icore.h>
#include <ssh/sshkeygenerator.h>

#include <QDir>
#include <QFormLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QFileInfo>
#include <QHostInfo>

using namespace ProjectExplorer;
using namespace Qnx;
using namespace Qnx::Internal;

namespace {
const char DEVICENAME_FIELD_ID[] = "DeviceName";

QString defaultDeviceHostIp(IDevice::MachineType type)
{
    return type == IDevice::Hardware ? QLatin1String("169.254.0.1") : QString();
}
}

BlackBerryDeviceConfigurationWizardSetupPage::BlackBerryDeviceConfigurationWizardSetupPage(QWidget *parent)
    : QWizardPage(parent)
    , m_ui(new Ui::BlackBerryDeviceConfigurationWizardSetupPage)
{
    m_ui->setupUi(this);
    setTitle(tr("Connection Details"));

    m_ui->debugToken->setExpectedKind(Utils::PathChooser::File);
    m_ui->debugToken->setPromptDialogFilter(QLatin1String("*.bar"));

    QString debugTokenBrowsePath = QnxUtils::dataDirPath();
    if (!QFileInfo(debugTokenBrowsePath).exists())
        debugTokenBrowsePath = QDir::homePath();
    m_ui->debugToken->setInitialBrowsePathBackup(debugTokenBrowsePath);

    connect(m_ui->deviceName, SIGNAL(textChanged(QString)), this, SIGNAL(completeChanged()));
    connect(m_ui->deviceHostIp, SIGNAL(textChanged(QString)), this, SIGNAL(completeChanged()));
    connect(m_ui->physicalDevice, SIGNAL(toggled(bool)), this, SLOT(handleMachineTypeChanged()));
    connect(m_ui->physicalDevice, SIGNAL(toggled(bool)), this, SIGNAL(completeChanged()));
    connect(m_ui->debugToken, SIGNAL(changed(QString)), this, SIGNAL(completeChanged()));
    connect(m_ui->requestButton, SIGNAL(clicked()), this, SLOT(requestDebugToken()));

    registerField(QLatin1String(DEVICENAME_FIELD_ID), m_ui->deviceName);
}

BlackBerryDeviceConfigurationWizardSetupPage::~BlackBerryDeviceConfigurationWizardSetupPage()
{
    delete m_ui;
    m_ui = 0;
}

void BlackBerryDeviceConfigurationWizardSetupPage::initializePage()
{
    m_ui->deviceName->setText(tr("BlackBerry Device"));
    m_ui->password->setText(QString());
    m_ui->physicalDevice->setChecked(true);
    m_ui->deviceHostIp->setText(defaultDeviceHostIp(machineType()));
}

bool BlackBerryDeviceConfigurationWizardSetupPage::isComplete() const
{
    bool debugTokenComplete = m_ui->simulator->isChecked()
            || (m_ui->physicalDevice->isChecked() && !m_ui->debugToken->fileName().isEmpty()
                && QFileInfo(m_ui->debugToken->fileName().toString()).exists());

    return !m_ui->deviceHostIp->text().isEmpty() && !m_ui->deviceHostIp->text().isEmpty()
            && debugTokenComplete;
}

QString BlackBerryDeviceConfigurationWizardSetupPage::deviceName() const
{
    return m_ui->deviceName->text();
}

QString BlackBerryDeviceConfigurationWizardSetupPage::hostName() const
{
    return m_ui->deviceHostIp->text();
}

QString BlackBerryDeviceConfigurationWizardSetupPage::password() const
{
    return m_ui->password->text();
}

QString BlackBerryDeviceConfigurationWizardSetupPage::debugToken() const
{
    return m_ui->debugToken->fileName().toString();
}

IDevice::MachineType BlackBerryDeviceConfigurationWizardSetupPage::machineType() const
{
    return m_ui->physicalDevice->isChecked() ? IDevice::Hardware : IDevice::Emulator;
}

void BlackBerryDeviceConfigurationWizardSetupPage::handleMachineTypeChanged()
{
    if (m_ui->deviceHostIp->text().isEmpty())
        m_ui->deviceHostIp->setText(defaultDeviceHostIp(machineType()));
}

void BlackBerryDeviceConfigurationWizardSetupPage::requestDebugToken()
{
    BlackBerryDebugTokenRequestDialog dialog;

    if (!m_ui->deviceHostIp->text().isEmpty() && !m_ui->password->text().isEmpty())
        dialog.setTargetDetails(m_ui->deviceHostIp->text(), m_ui->password->text());

    const int result = dialog.exec();

    if (result != QDialog::Accepted)
        return;

    m_ui->debugToken->setPath(dialog.debugToken());
}

// ----------------------------------------------------------------------------


BlackBerryDeviceConfigurationWizardSshKeyPage::BlackBerryDeviceConfigurationWizardSshKeyPage(QWidget *parent)
    : QWizardPage(parent)
    , m_ui(new Ui::BlackBerryDeviceConfigurationWizardSshKeyPage)
    , m_sshKeysGenerator(new BlackBerrySshKeysGenerator(this))
{
    m_ui->setupUi(this);

    m_ui->privateKey->setExpectedKind(Utils::PathChooser::File);
    m_ui->progressBar->hide();

    QString initialBrowsePath = QnxUtils::dataDirPath();
    if (!QFileInfo(initialBrowsePath).exists())
        initialBrowsePath = QDir::homePath();
    m_ui->privateKey->setInitialBrowsePathBackup(initialBrowsePath);

    setTitle(tr("SSH Key Setup"));
    setSubTitle(tr("Please select an existing <b>4096</b>-bit key or click <b>Generate</b> to create a new one."));

    connect(m_ui->privateKey, SIGNAL(changed(QString)), this, SLOT(findMatchingPublicKey(QString)));
    connect(m_ui->privateKey, SIGNAL(changed(QString)), this, SIGNAL(completeChanged()));
    connect(m_ui->generate, SIGNAL(clicked()), this, SLOT(generateSshKeys()));
    connect(m_sshKeysGenerator, SIGNAL(sshKeysGenerationFinished(bool)), this, SLOT(processSshKeys(bool)));
}

BlackBerryDeviceConfigurationWizardSshKeyPage::~BlackBerryDeviceConfigurationWizardSshKeyPage()
{
    // Make sure the m_sshKeysGenerator thread is terminated before it's destroyed
    m_sshKeysGenerator->terminate();
    m_sshKeysGenerator->wait();

    delete m_ui;
    m_ui = 0;
}

void BlackBerryDeviceConfigurationWizardSshKeyPage::initializePage()
{
}

bool BlackBerryDeviceConfigurationWizardSshKeyPage::isComplete() const
{
    QFileInfo privateKeyFi(m_ui->privateKey->fileName().toString());
    QFileInfo publicKeyFi(m_ui->publicKey->text());

    return privateKeyFi.exists() && publicKeyFi.exists();
}

QString BlackBerryDeviceConfigurationWizardSshKeyPage::privateKey() const
{
    return m_ui->privateKey->fileName().toString();
}

QString BlackBerryDeviceConfigurationWizardSshKeyPage::publicKey() const
{
    return m_ui->publicKey->text();
}

void BlackBerryDeviceConfigurationWizardSshKeyPage::findMatchingPublicKey(const QString &privateKeyPath)
{
    const QString candidate = privateKeyPath + QLatin1String(".pub");
    if (QFileInfo(candidate).exists())
        m_ui->publicKey->setText(QDir::toNativeSeparators(candidate));
    else
        m_ui->publicKey->clear();
}

void BlackBerryDeviceConfigurationWizardSshKeyPage::processSshKeys(bool success)
{
    setBusy(false);

    if (!success) {
        QMessageBox::critical(this, tr("Key Generation Failed"), m_sshKeysGenerator->error());
        return;
    }

    const QString publicKeyPath = m_generatedPrivateKeyPath + QLatin1String(".pub");

    if (!saveKeys(m_generatedPrivateKeyPath, publicKeyPath)) // saveKeys(..) will show an error message if necessary
        return;

    m_ui->privateKey->setFileName(Utils::FileName::fromString(m_generatedPrivateKeyPath));
    m_ui->publicKey->setText(QDir::toNativeSeparators(publicKeyPath));

    emit completeChanged();
}

bool BlackBerryDeviceConfigurationWizardSshKeyPage::saveKeys(const QString &privateKeyFile, const QString &publicKeyFile)
{
    Utils::FileSaver privSaver(privateKeyFile);
    privSaver.write(m_sshKeysGenerator->keyGenerator()->privateKey());
    if (!privSaver.finalize(this))
        return false; // finalize shows an error message if necessary
    QFile::setPermissions(privateKeyFile, QFile::ReadOwner | QFile::WriteOwner);

    Utils::FileSaver pubSaver(publicKeyFile);

    // blackberry-connect requires an @ character to be included in the RSA comment
    const QString atHost = QLatin1Char('@') + QHostInfo::localHostName();
    QByteArray pubKeyContent = m_sshKeysGenerator->keyGenerator()->publicKey();
    pubKeyContent.append(atHost.toLocal8Bit());

    pubSaver.write(pubKeyContent);
    if (!pubSaver.finalize(this))
        return false;

    return true;
}

void BlackBerryDeviceConfigurationWizardSshKeyPage::generateSshKeys()
{
    QString lookInDir = QnxUtils::dataDirPath();
    if (!QFileInfo(lookInDir).exists())
        lookInDir = QDir::homePath();

    QString privateKeyPath = QFileDialog::getSaveFileName(this, tr("Choose Private Key File Name"), lookInDir);
    if (privateKeyPath.isEmpty())
        return;

    m_generatedPrivateKeyPath = privateKeyPath;

    setBusy(true);
    m_sshKeysGenerator->start();
}

void BlackBerryDeviceConfigurationWizardSshKeyPage::setBusy(bool busy)
{
    m_ui->privateKey->setEnabled(!busy);
    m_ui->publicKey->setEnabled(!busy);
    m_ui->generate->setEnabled(!busy);
    m_ui->progressBar->setVisible(busy);

    wizard()->button(QWizard::BackButton)->setEnabled(!busy);
    wizard()->button(QWizard::NextButton)->setEnabled(!busy);
    wizard()->button(QWizard::FinishButton)->setEnabled(!busy);
    wizard()->button(QWizard::CancelButton)->setEnabled(!busy);
}
// ----------------------------------------------------------------------------


BlackBerryDeviceConfigurationWizardFinalPage::BlackBerryDeviceConfigurationWizardFinalPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Setup Finished"));

    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *label = new QLabel(tr("The new device configuration will now be created."), this);
    layout->addWidget(label);
}



