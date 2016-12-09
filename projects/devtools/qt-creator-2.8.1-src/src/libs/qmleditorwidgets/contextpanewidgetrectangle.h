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

#ifndef CONTEXTPANEWIDGETRECTANGLE_H
#define CONTEXTPANEWIDGETRECTANGLE_H

#include "qmleditorwidgets_global.h"
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
    class ContextPaneWidgetRectangle;
}
QT_END_NAMESPACE

namespace QmlJS {
    class PropertyReader;
}

namespace QmlEditorWidgets {

class QMLEDITORWIDGETS_EXPORT ContextPaneWidgetRectangle : public QWidget
{
    Q_OBJECT

public:
    explicit ContextPaneWidgetRectangle(QWidget *parent = 0);
    ~ContextPaneWidgetRectangle();
    void setProperties(QmlJS::PropertyReader *propertyReader);
    void enabableGradientEditing(bool);

public slots:
    void onBorderColorButtonToggled(bool);
    void onColorButtonToggled(bool);
    void onColorDialogApplied(const QColor &color);
    void onColorDialogCancled();
    void onGradientClicked();
    void onColorNoneClicked();
    void onColorSolidClicked();
    void onBorderNoneClicked();
    void onBorderSolidClicked();
    void onGradientLineDoubleClicked(const QPoint &);
    void onUpdateGradient();

signals:
    void propertyChanged(const QString &, const QVariant &);
    void removeProperty(const QString &);
    void removeAndChangeProperty(const QString &, const QString &, const QVariant &, bool removeFirst);

protected:
    void timerEvent(QTimerEvent *event);

private:
    void setColor();
    bool isGradientEditingEnabled() const
    { return m_enableGradientEditing; }
    Ui::ContextPaneWidgetRectangle *ui;
    bool m_hasBorder;
    bool m_hasGradient;
    bool m_none;
    bool m_gradientLineDoubleClicked;
    int m_gradientTimer;
    bool m_enableGradientEditing;
};

} //QmlDesigner

#endif // CONTEXTPANEWIDGETRECTANGLE_H
