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

#ifndef DRAGTOOL_H
#define DRAGTOOL_H

#include "abstractformeditortool.h"
#include "movemanipulator.h"
#include "selectionindicator.h"

#include <QObject>
#include <QScopedPointer>


namespace QmlDesigner {

class DragTool;

namespace Internal {

class TimerHandler : public QObject
{
    Q_OBJECT

public:
    TimerHandler(DragTool *tool) : QObject(), m_dragTool(tool) {}
public slots:
    void clearMoveDelay();

private:
    DragTool *m_dragTool;
};
}

class DragTool : public AbstractFormEditorTool
{
public:
    DragTool(FormEditorView* editorView);
    virtual ~DragTool();

    void mousePressEvent(const QList<QGraphicsItem*> &itemList,
                         QGraphicsSceneMouseEvent *event) QTC_OVERRIDE;
    void mouseMoveEvent(const QList<QGraphicsItem*> &itemList,
                        QGraphicsSceneMouseEvent *event) QTC_OVERRIDE;
    void mouseReleaseEvent(const QList<QGraphicsItem*> &itemList,
                           QGraphicsSceneMouseEvent *event) QTC_OVERRIDE;
    void mouseDoubleClickEvent(const QList<QGraphicsItem*> &itemList,
                               QGraphicsSceneMouseEvent *event) QTC_OVERRIDE;
    void hoverMoveEvent(const QList<QGraphicsItem*> &itemList,
                        QGraphicsSceneMouseEvent *event) QTC_OVERRIDE;

    void keyPressEvent(QKeyEvent *event) QTC_OVERRIDE;
    void keyReleaseEvent(QKeyEvent *keyEvent) QTC_OVERRIDE;

    void itemsAboutToRemoved(const QList<FormEditorItem*> &itemList) QTC_OVERRIDE;

    void selectedItemsChanged(const QList<FormEditorItem*> &itemList) QTC_OVERRIDE;
    void instancesParentChanged(const QList<FormEditorItem *> &itemList) QTC_OVERRIDE;
    void instancePropertyChange(const QList<QPair<ModelNode, PropertyName> > &propertyList) QTC_OVERRIDE;

    void updateMoveManipulator();

    void beginWithPoint(const QPointF &beginPoint);


    virtual void dropEvent(QGraphicsSceneDragDropEvent * event) QTC_OVERRIDE;
    virtual void dragEnterEvent(QGraphicsSceneDragDropEvent * event) QTC_OVERRIDE;
    virtual void dragLeaveEvent(QGraphicsSceneDragDropEvent * event) QTC_OVERRIDE;
    virtual void dragMoveEvent(QGraphicsSceneDragDropEvent * event) QTC_OVERRIDE;

    //void beginWithPoint(const QPointF &beginPoint);

    void clear() QTC_OVERRIDE;

    void formEditorItemsChanged(const QList<FormEditorItem*> &itemList) QTC_OVERRIDE;

    void instancesCompleted(const QList<FormEditorItem*> &itemList) QTC_OVERRIDE;

    void clearMoveDelay();

protected:
    void abort();


private:

    void createQmlItemNode(const ItemLibraryEntry &itemLibraryEntry, QmlItemNode parentNode, QPointF scenePos);
    void createQmlItemNodeFromImage(const QString &imageName, QmlItemNode parentNode, QPointF scenePos);
    FormEditorItem* calculateContainer(const QPointF &point, FormEditorItem * currentItem = 0);
    QList<Import> missingImportList(const ItemLibraryEntry &itemLibraryEntry);

    void begin(QPointF scenePos);
    void end();
    void end(Snapper::Snapping useSnapping);
    void move(QPointF scenePos);

    MoveManipulator m_moveManipulator;
    SelectionIndicator m_selectionIndicator;
    QWeakPointer<FormEditorItem> m_movingItem;
    RewriterTransaction m_rewriterTransaction;
    QmlItemNode m_dragNode;
    QScopedPointer<Internal::TimerHandler> m_timerHandler;
    bool m_blockMove;
    QPointF m_startPoint;
    bool m_Aborted;
};


}
#endif // DRAGTOOL_H
