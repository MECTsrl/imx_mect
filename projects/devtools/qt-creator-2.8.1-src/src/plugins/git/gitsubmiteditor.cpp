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

#include "gitsubmiteditor.h"
#include "commitdata.h"
#include "gitclient.h"
#include "gitplugin.h"
#include "gitsubmiteditorwidget.h"

#include <coreplugin/editormanager/editormanager.h>
#include <utils/qtcassert.h>
#include <vcsbase/submitfilemodel.h>
#include <vcsbase/vcsbaseoutputwindow.h>

#include <QDebug>
#include <QStringList>
#include <QTextCodec>

namespace Git {
namespace Internal {

class GitSubmitFileModel : public VcsBase::SubmitFileModel
{
public:
    GitSubmitFileModel(QObject *parent = 0) : VcsBase::SubmitFileModel(parent)
    { }

    void updateSelections(SubmitFileModel *source)
    {
        QTC_ASSERT(source, return);
        GitSubmitFileModel *gitSource = static_cast<GitSubmitFileModel *>(source);
        int j = 0;
        for (int i = 0; i < rowCount() && j < source->rowCount(); ++i) {
            CommitData::StateFilePair stateFile = stateFilePair(i);
            for (; j < source->rowCount(); ++j) {
                CommitData::StateFilePair sourceStateFile = gitSource->stateFilePair(j);
                if (stateFile == sourceStateFile) {
                    if (isCheckable(i) && source->isCheckable(j))
                        setChecked(i, source->checked(j));
                    break;
                } else if (stateFile < sourceStateFile) {
                    break;
                }
            }
        }
    }

private:
    CommitData::StateFilePair stateFilePair(int row) const
    {
        return CommitData::StateFilePair(static_cast<FileStates>(extraData(row).toInt()), file(row));
    }
};

/* The problem with git is that no diff can be obtained to for a random
 * multiselection of staged/unstaged files; it requires the --cached
 * option for staged files. So, we sort apart the diff file lists
 * according to a type flag we add to the model. */

GitSubmitEditor::GitSubmitEditor(const VcsBase::VcsBaseSubmitEditorParameters *parameters, QWidget *parent) :
    VcsBaseSubmitEditor(parameters, new GitSubmitEditorWidget(parent)),
    m_model(0),
    m_commitType(SimpleCommit),
    m_forceClose(false)
{
    connect(this, SIGNAL(diffSelectedFiles(QList<int>)), this, SLOT(slotDiffSelected(QList<int>)));
    connect(submitEditorWidget(), SIGNAL(show(QString)), this, SLOT(showCommit(QString)));
}

GitSubmitEditorWidget *GitSubmitEditor::submitEditorWidget()
{
    return static_cast<GitSubmitEditorWidget *>(widget());
}

const GitSubmitEditorWidget *GitSubmitEditor::submitEditorWidget() const
{
    return static_cast<GitSubmitEditorWidget *>(widget());
}

void GitSubmitEditor::setCommitData(const CommitData &d)
{
    m_commitEncoding = d.commitEncoding;
    m_workingDirectory = d.panelInfo.repository;
    m_commitType = d.commitType;
    m_amendSHA1 = d.amendSHA1;

    GitSubmitEditorWidget *w = submitEditorWidget();
    w->initialize(m_commitType, m_workingDirectory);
    w->setPanelData(d.panelData);
    w->setPanelInfo(d.panelInfo);
    w->setHasUnmerged(false);

    setEmptyFileListEnabled(m_commitType == AmendCommit); // Allow for just correcting the message

    m_model = new GitSubmitFileModel(this);
    if (!d.files.isEmpty()) {
        for (QList<CommitData::StateFilePair>::const_iterator it = d.files.constBegin();
             it != d.files.constEnd(); ++it) {
            const FileStates state = it->first;
            const QString file = it->second;
            VcsBase::CheckMode checkMode;
            if (state & UnmergedFile) {
                checkMode = VcsBase::Uncheckable;
                w->setHasUnmerged(true);
            } else if (state & StagedFile) {
                checkMode = VcsBase::Checked;
            } else {
                checkMode = VcsBase::Unchecked;
            }
            m_model->addFile(file, CommitData::stateDisplayName(state), checkMode,
                             QVariant(static_cast<int>(state)));
        }
    }
    setFileModel(m_model, d.panelInfo.repository);
}

void GitSubmitEditor::slotDiffSelected(const QList<int> &rows)
{
    // Sort it apart into unmerged/staged/unstaged files
    QStringList unmergedFiles;
    QStringList unstagedFiles;
    QStringList stagedFiles;
    foreach (int row, rows) {
        const QString fileName = m_model->file(row);
        const FileStates state = static_cast<FileStates>(m_model->extraData(row).toInt());
        if (state & UnmergedFile)
            unmergedFiles.push_back(fileName);
        else if (state & StagedFile)
            stagedFiles.push_back(fileName);
        else if (state != UntrackedFile)
            unstagedFiles.push_back(fileName);
    }
    if (!unstagedFiles.empty() || !stagedFiles.empty())
        emit diff(unstagedFiles, stagedFiles);
    if (!unmergedFiles.empty())
        emit merge(unmergedFiles);
}

void GitSubmitEditor::showCommit(const QString &commit)
{
    if (!m_workingDirectory.isEmpty())
        emit show(m_workingDirectory, commit);
}

void GitSubmitEditor::updateFileModel()
{
    if (m_workingDirectory.isEmpty())
        return;
    GitClient *client = GitPlugin::instance()->gitClient();
    QString errorMessage, commitTemplate;
    CommitData data(m_commitType);
    if (client->getCommitData(m_workingDirectory, &commitTemplate, data, &errorMessage)) {
        setCommitData(data);
        submitEditorWidget()->refreshLog(m_workingDirectory);
    } else {
        VcsBase::VcsBaseOutputWindow::instance()->append(errorMessage);
        m_forceClose = true;
        Core::EditorManager::instance()->closeEditors(QList<IEditor*>() << this);
    }
}

GitSubmitEditorPanelData GitSubmitEditor::panelData() const
{
    return submitEditorWidget()->panelData();
}

QString GitSubmitEditor::amendSHA1() const
{
    QString commit = submitEditorWidget()->amendSHA1();
    return commit.isEmpty() ? m_amendSHA1 : commit;
}

QByteArray GitSubmitEditor::fileContents() const
{
    const QString &text = submitEditorWidget()->descriptionText();

    if (!m_commitEncoding.isEmpty()) {
        // Do the encoding convert, When use user-defined encoding
        // e.g. git config --global i18n.commitencoding utf-8
        QTextCodec *codec = QTextCodec::codecForName(m_commitEncoding.toLocal8Bit());
        if (codec)
            return codec->fromUnicode(text);
    }

    // Using utf-8 as the default encoding
    return text.toUtf8();
}

} // namespace Internal
} // namespace Git
