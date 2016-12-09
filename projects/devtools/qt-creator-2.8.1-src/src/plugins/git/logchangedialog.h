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

#ifndef LOGCHANGEDDIALOG_H
#define LOGCHANGEDDIALOG_H

#include <QDialog>
#include <QTreeView>

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QComboBox;
class QStandardItemModel;
class QStandardItem;
QT_END_NAMESPACE

namespace Git {
namespace Internal {

// A widget that lists SHA1 and subject of the changes
// Used for reset and interactive rebase

class LogChangeWidget : public QTreeView
{
    Q_OBJECT

public:
    explicit LogChangeWidget(QWidget *parent = 0);
    bool init(const QString &repository, const QString &commit = QString(),
              bool includeRemote = true);
    QString commit() const;
    int commitIndex() const;
    QString earliestCommit() const;

signals:
    void doubleClicked(const QString &commit);

private slots:
    void emitDoubleClicked(const QModelIndex &index);

private:
    bool populateLog(const QString &repository, const QString &commit, bool includeRemote);
    const QStandardItem *currentItem(int column = 0) const;

    QStandardItemModel *m_model;
};

class LogChangeDialog : public QDialog
{
    Q_OBJECT
public:
    LogChangeDialog(bool isReset, QWidget *parent = 0);

    bool runDialog(const QString &repository, const QString &commit = QString(),
                   bool includeRemote = true);

    QString commit() const;
    int commitIndex() const;
    QString resetFlag() const;

private:
    LogChangeWidget *widget;
    QDialogButtonBox *m_dialogButtonBox;
    QComboBox *m_resetTypeComboBox;
};

} // namespace Internal
} // namespace Git

#endif // LOGCHANGEDDIALOG_H
