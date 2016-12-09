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

#include "settingspage.h"
#include "subversionsettings.h"
#include "subversionplugin.h"

#include <coreplugin/icore.h>
#include <extensionsystem/pluginmanager.h>
#include <vcsbase/vcsbaseconstants.h>
#include <utils/pathchooser.h>

#include <QCoreApplication>
#include <QTextStream>
#include <QFileDialog>

using namespace Subversion::Internal;
using namespace Utils;

SettingsPageWidget::SettingsPageWidget(QWidget *parent) :
    QWidget(parent)
{
    m_ui.setupUi(this);
    m_ui.pathChooser->setExpectedKind(PathChooser::ExistingCommand);
    m_ui.pathChooser->setPromptDialogTitle(tr("Subversion Command"));
}

SubversionSettings SettingsPageWidget::settings() const
{
    SubversionSettings rc;
    rc.setValue(SubversionSettings::binaryPathKey, m_ui.pathChooser->rawPath());
    rc.setValue(SubversionSettings::useAuthenticationKey, m_ui.userGroupBox->isChecked());
    rc.setValue(SubversionSettings::userKey, m_ui.usernameLineEdit->text());
    rc.setValue(SubversionSettings::passwordKey, m_ui.passwordLineEdit->text());
    rc.setValue(SubversionSettings::timeoutKey, m_ui.timeOutSpinBox->value());
    if (rc.stringValue(SubversionSettings::userKey).isEmpty())
        rc.setValue(SubversionSettings::useAuthenticationKey, false);
    rc.setValue(SubversionSettings::promptOnSubmitKey, m_ui.promptToSubmitCheckBox->isChecked());
    rc.setValue(SubversionSettings::spaceIgnorantAnnotationKey,
                m_ui.spaceIgnorantAnnotationCheckBox->isChecked());
    rc.setValue(SubversionSettings::logCountKey, m_ui.logCountSpinBox->value());
    return rc;
}

void SettingsPageWidget::setSettings(const SubversionSettings &s)
{
    m_ui.pathChooser->setPath(s.binaryPath());
    m_ui.usernameLineEdit->setText(s.stringValue(SubversionSettings::userKey));
    m_ui.passwordLineEdit->setText(s.stringValue(SubversionSettings::passwordKey));
    m_ui.userGroupBox->setChecked(s.boolValue(SubversionSettings::useAuthenticationKey));
    m_ui.timeOutSpinBox->setValue(s.intValue(SubversionSettings::timeoutKey));
    m_ui.promptToSubmitCheckBox->setChecked(s.boolValue(SubversionSettings::promptOnSubmitKey));
    m_ui.spaceIgnorantAnnotationCheckBox->setChecked(
                s.boolValue(SubversionSettings::spaceIgnorantAnnotationKey));
    m_ui.logCountSpinBox->setValue(s.intValue(SubversionSettings::logCountKey));
}

QString SettingsPageWidget::searchKeywords() const
{
    QString rc;
    QLatin1Char sep(' ');
    QTextStream(&rc)
            << sep << m_ui.generalGroupBox->title()
            << sep << m_ui.commandLabel->text()
            << sep << m_ui.userGroupBox->title()
            << sep << m_ui.usernameLabel->text()
            << sep << m_ui.passwordLabel->text()
            << sep << m_ui.miscGroupBox->title()
            << sep << m_ui.logCountLabel->text()
            << sep << m_ui.timeOutLabel->text()
            << sep << m_ui.promptToSubmitCheckBox->text()
            << sep << m_ui.spaceIgnorantAnnotationCheckBox->text()
               ;
    rc.remove(QLatin1Char('&'));
    return rc;
}

SettingsPage::SettingsPage() :
    m_widget(0)
{
    setId(VcsBase::Constants::VCS_ID_SUBVERSION);
    setDisplayName(tr("Subversion"));
}

QWidget *SettingsPage::createPage(QWidget *parent)
{
    m_widget = new SettingsPageWidget(parent);
    m_widget->setSettings(SubversionPlugin::instance()->settings());
    if (m_searchKeywords.isEmpty())
        m_searchKeywords = m_widget->searchKeywords();
    return m_widget;
}

void SettingsPage::apply()
{
    SubversionPlugin::instance()->setSettings(m_widget->settings());
}

bool SettingsPage::matches(const QString &s) const
{
    return m_searchKeywords.contains(s, Qt::CaseInsensitive);
}
