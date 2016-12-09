/**************************************************************************
**
** Copyright (c) 2013 Hugues Delorme
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
#ifndef BAZAARCLIENT_H
#define BAZAARCLIENT_H

#include "bazaarsettings.h"
#include "branchinfo.h"
#include <vcsbase/vcsbaseclient.h>

namespace Bazaar {
namespace Internal {

class BazaarSettings;

class BazaarClient : public VcsBase::VcsBaseClient
{
    Q_OBJECT

public:
    BazaarClient(BazaarSettings *settings);

    BazaarSettings *settings() const;

    bool synchronousSetUserId();
    BranchInfo synchronousBranchQuery(const QString &repositoryRoot) const;
    void commit(const QString &repositoryRoot, const QStringList &files,
                const QString &commitMessageFile, const QStringList &extraOptions = QStringList());
    void annotate(const QString &workingDir, const QString &file,
                  const QString revision = QString(), int lineNumber = -1,
                  const QStringList &extraOptions = QStringList());
    void view(const QString &source, const QString &id,
              const QStringList &extraOptions = QStringList());
    QString findTopLevelForFile(const QFileInfo &file) const;

protected:
    Core::Id vcsEditorKind(VcsCommand cmd) const;
    QString vcsCommandString(VcsCommand cmd) const;
    QStringList revisionSpec(const QString &revision) const;
    VcsBase::VcsBaseEditorParameterWidget *createDiffEditor(const QString &workingDir,
                                                            const QStringList &files,
                                                            const QStringList &extraOptions);
    VcsBase::VcsBaseEditorParameterWidget *createLogEditor(const QString &workingDir,
                                                           const QStringList &files,
                                                           const QStringList &extraOptions);
    StatusItem parseStatusLine(const QString &line) const;

private:
    friend class CloneWizard;
};

} // namespace Internal
} // namespace Bazaar

#endif // BAZAARCLIENT_H
