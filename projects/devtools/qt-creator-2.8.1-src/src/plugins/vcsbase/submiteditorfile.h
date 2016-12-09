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

#ifndef SUBMITEDITORFILE_H
#define SUBMITEDITORFILE_H

#include <coreplugin/idocument.h>

namespace VcsBase {
namespace Internal {

class SubmitEditorFile : public Core::IDocument
{
    Q_OBJECT
public:
    explicit SubmitEditorFile(const QString &mimeType,
                              QObject *parent = 0);

    QString fileName() const { return m_fileName; }
    QString defaultPath() const { return QString(); }
    QString suggestedFileName() const { return QString(); }

    bool isModified() const { return m_modified; }
    QString mimeType() const;
    bool isSaveAsAllowed() const { return false; }
    bool save(QString *errorString, const QString &fileName, bool autoSave);
    ReloadBehavior reloadBehavior(ChangeTrigger state, ChangeType type) const;
    bool reload(QString *errorString, ReloadFlag flag, ChangeType type);
    void rename(const QString &newName);

    void setFileName(const QString &name);
    void setModified(bool modified = true);

signals:
    void saveMe(QString *errorString, const QString &fileName, bool autoSave);

private:
    const QString m_mimeType;
    bool m_modified;
    QString m_fileName;
};


} // namespace Internal
} // namespace VcsBase

#endif // SUBMITEDITORFILE_H
