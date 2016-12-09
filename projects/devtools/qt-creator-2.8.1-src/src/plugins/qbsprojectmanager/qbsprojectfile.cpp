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

#include "qbsprojectfile.h"

#include "qbsproject.h"
#include "qbsprojectmanagerconstants.h"

namespace QbsProjectManager {
namespace Internal {

QbsProjectFile::QbsProjectFile(QbsProject *parent, QString fileName) : Core::IDocument(parent),
    m_project(parent),
    m_fileName(fileName)
{ }

QbsProjectFile::~QbsProjectFile()
{ }

bool QbsProjectFile::save(QString *, const QString &, bool)
{
    return false;
}

QString QbsProjectFile::fileName() const
{
    return m_fileName;
}

bool QbsProjectFile::isReadOnly() const
{
    return true;
}

QString QbsProjectFile::defaultPath() const
{
    return QString();
}

QString QbsProjectFile::suggestedFileName() const
{
    return QString();
}

QString QbsProjectFile::mimeType() const
{
    return QLatin1String(Constants::MIME_TYPE);
}

bool QbsProjectFile::isModified() const
{
    return false;
}

bool QbsProjectFile::isSaveAsAllowed() const
{
    return false;
}

Core::IDocument::ReloadBehavior QbsProjectFile::reloadBehavior(ChangeTrigger state, ChangeType type) const
{
    Q_UNUSED(state);
    Q_UNUSED(type);
    return BehaviorSilent;
}

bool QbsProjectFile::reload(QString *errorString, ReloadFlag flag, ChangeType type)
{
    Q_UNUSED(errorString)
    Q_UNUSED(flag)
    if (type == TypePermissions)
        return true;
    m_project->delayForcedParsing();
    return true;
}

void QbsProjectFile::rename(const QString &newName)
{
    // Can't happen
    Q_UNUSED(newName);
    Q_ASSERT(false);
}

} // namespace Internal
} // namespace QbsProjectManager

