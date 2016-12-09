/**************************************************************************
**
** Copyright (C) 2013 Denis Mingulov.
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

#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <coreplugin/editormanager/ieditor.h>
#include <coreplugin/idocument.h>

#include <QScopedPointer>
#include <QStringList>

QT_BEGIN_NAMESPACE
class QAbstractButton;
class QAction;
QT_END_NAMESPACE

namespace ImageViewer {
namespace Internal {
class ImageViewerFile;

class ImageViewer : public Core::IEditor
{
    Q_OBJECT

public:
    explicit ImageViewer(QWidget *parent = 0);
    ~ImageViewer();

    bool createNew(const QString &contents = QString());
    bool open(QString *errorString, const QString &fileName, const QString &realFileName);
    Core::IDocument *document();
    Core::Id id() const;
    QString displayName() const;
    void setDisplayName(const QString &title);
    bool isTemporary() const;
    QWidget *toolBar();

public slots:
    void imageSizeUpdated(const QSize &size);
    void scaleFactorUpdate(qreal factor);

    void switchViewBackground();
    void switchViewOutline();
    void zoomIn();
    void zoomOut();
    void resetToOriginalSize();
    void fitToScreen();
    void togglePlay();

private slots:
    void playToggled();

private:

    bool updateButtonIconByTheme(QAbstractButton *button, const QString &name);
    void setPaused(bool paused);

private:
    struct ImageViewerPrivate *d;
};

} // namespace Internal
} // namespace ImageViewer

#endif // IMAGEVIEWER_H
