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

#ifndef SELECTIONTOOL_H
#define SELECTIONTOOL_H


#include "abstractformeditortool.h"
#include "rubberbandselectionmanipulator.h"
#include "singleselectionmanipulator.h"
#include "selectionindicator.h"
#include "resizeindicator.h"

#include <QTime>

namespace QmlDesigner {


class SelectionTool : public AbstractFormEditorTool
{
public:
    SelectionTool(FormEditorView* editorView);
    ~SelectionTool();

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

    void dragLeaveEvent(QGraphicsSceneDragDropEvent * event) QTC_OVERRIDE;
    void dragMoveEvent(QGraphicsSceneDragDropEvent * event) QTC_OVERRIDE;

    void itemsAboutToRemoved(const QList<FormEditorItem*> &itemList) QTC_OVERRIDE;
    //    QVariant itemChange(const QList<QGraphicsItem*> &itemList,
//                        QGraphicsItem::GraphicsItemChange change,
//                        const QVariant &value );

//    void update();

    void clear() QTC_OVERRIDE;

    void selectedItemsChanged(const QList<FormEditorItem*> &itemList) QTC_OVERRIDE;

    void formEditorItemsChanged(const QList<FormEditorItem*> &itemList) QTC_OVERRIDE;

    void instancesCompleted(const QList<FormEditorItem*> &itemList) QTC_OVERRIDE;
    void instancesParentChanged(const QList<FormEditorItem *> &itemList) QTC_OVERRIDE;
    void instancePropertyChange(const QList<QPair<ModelNode, PropertyName> > &propertyList) QTC_OVERRIDE;

    void selectUnderPoint(QGraphicsSceneMouseEvent *event);

    void setSelectOnlyContentItems(bool selectOnlyContentItems);

    void setCursor(const QCursor &cursor);

private:
    RubberBandSelectionManipulator m_rubberbandSelectionManipulator;
    SingleSelectionManipulator m_singleSelectionManipulator;
    SelectionIndicator m_selectionIndicator;
    ResizeIndicator m_resizeIndicator;
    QTime m_mousePressTimer;
    bool m_selectOnlyContentItems;
    QCursor m_cursor;
};

}
#endif // SELECTIONTOOL_H
