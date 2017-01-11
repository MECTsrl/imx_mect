/* -*- mode: C++ ; c-file-style: "stroustrup" -*- *****************************
 * Qwt Widget Library
 * Copyright (C) 1997   Josef Wilgen
 * Copyright (C) 2002   Uwe Rathmann
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the Qwt License, Version 1.0
 *****************************************************************************/

#include "qwt_plot_opengl_canvas.h"
#include "qwt_plot.h"
#include <qevent.h>
#include <qpainter.h>
#include <qdrawutil.h>
#include <qstyle.h>
#include <qstyleoption.h>
#include "qwt_painter.h"

static QWidget *qwtBGWidget2( QWidget *widget )
{
    QWidget *w = widget;

    for ( ; w->parentWidget() != NULL; w = w->parentWidget() )
    {
        if ( w->autoFillBackground() || 
            w->testAttribute( Qt::WA_StyledBackground ) )
        {
            return w;
        }
    }

    return w;
}

static void qwtUpdateContentsRect2( QwtPlotOpenGLCanvas *canvas )
{
    const int fw = canvas->frameWidth();
    canvas->setContentsMargins( fw, fw, fw, fw );
}

class QwtPlotOpenGLCanvas::PrivateData
{
public:
    PrivateData():
        frameStyle( QFrame::Panel | QFrame::Sunken),
        lineWidth( 2 ),
        midLineWidth( 0 )
    {
    }

    int frameStyle;
    int lineWidth;
    int midLineWidth;
};

QwtPlotOpenGLCanvas::QwtPlotOpenGLCanvas( QwtPlot *plot ):
    QOpenGLWidget( plot )
{
    d_data = new PrivateData;

    QSurfaceFormat fmt = format();
    fmt.setSamples(4);
    setFormat( fmt );

#ifndef QT_NO_CURSOR
    setCursor( Qt::CrossCursor );
#endif

    setAutoFillBackground( true );
    qwtUpdateContentsRect2( this );
}

QwtPlotOpenGLCanvas::~QwtPlotOpenGLCanvas()
{
    delete d_data;
}

void QwtPlotOpenGLCanvas::setFrameStyle( int style )
{
    if ( style != d_data->frameStyle )
    {
        d_data->frameStyle = style;
        qwtUpdateContentsRect2( this );

        update();
    }
}

int QwtPlotOpenGLCanvas::frameStyle() const
{
    return d_data->frameStyle;
}

void QwtPlotOpenGLCanvas::setFrameShadow( Shadow shadow )
{
    setFrameStyle(( d_data->frameStyle & QFrame::Shape_Mask ) | shadow );
}

QwtPlotOpenGLCanvas::Shadow QwtPlotOpenGLCanvas::frameShadow() const
{
    return (Shadow) ( d_data->frameStyle & QFrame::Shadow_Mask );
}

void QwtPlotOpenGLCanvas::setFrameShape( Shape shape )
{
    setFrameStyle( ( d_data->frameStyle & QFrame::Shadow_Mask ) | shape );
}

QwtPlotOpenGLCanvas::Shape QwtPlotOpenGLCanvas::frameShape() const
{
    return (Shape) ( d_data->frameStyle & QFrame::Shape_Mask );
}

void QwtPlotOpenGLCanvas::setLineWidth( int width )
{
    width = qMax( width, 0 );
    if ( width != d_data->lineWidth )
    {
        d_data->lineWidth = qMax( width, 0 );
        qwtUpdateContentsRect2( this );
        update();
    }
}

int QwtPlotOpenGLCanvas::lineWidth() const
{
    return d_data->lineWidth;
}

void QwtPlotOpenGLCanvas::setMidLineWidth( int width )
{
    width = qMax( width, 0 );
    if ( width != d_data->midLineWidth )
    {
        d_data->midLineWidth = width;
        qwtUpdateContentsRect2( this );
        update();
    }
}

int QwtPlotOpenGLCanvas::midLineWidth() const
{
    return d_data->midLineWidth;
}

int QwtPlotOpenGLCanvas::frameWidth() const
{
    return ( frameStyle() != NoFrame ) ? d_data->lineWidth : 0;
}

void QwtPlotOpenGLCanvas::paintEvent( QPaintEvent *event )
{
    Q_UNUSED( event );

    QPainter painter( this );

    if ( painter.paintEngine()->type() == QPaintEngine::OpenGL2 )
    {
        // work around a translation bug of QPaintEngine::OpenGL2
        painter.translate( 1, 1 );
    }

    drawBackground( &painter );
    drawItems( &painter );

    if ( !testAttribute( Qt::WA_StyledBackground ) )
    {
        if ( frameWidth() > 0 )
            drawBorder( &painter );
    }
}

bool QwtPlotOpenGLCanvas::event( QEvent *event )
{
    const bool ok = QOpenGLWidget::event( event );

    if ( event->type() == QEvent::PolishRequest ||
        event->type() == QEvent::StyleChange )
    {
        // assuming, that we always have a styled background
        // when we have a style sheet

        setAttribute( Qt::WA_StyledBackground,
            testAttribute( Qt::WA_StyleSheet ) );
    }

    return ok;
}

void QwtPlotOpenGLCanvas::drawItems( QPainter *painter )
{
    painter->save();

    painter->setClipRect( contentsRect(), Qt::IntersectClip );

    QwtPlot *plot = qobject_cast< QwtPlot *>( parent() );
    if ( plot )
        plot->drawCanvas( painter );

    painter->restore();
}

void QwtPlotOpenGLCanvas::drawBackground( QPainter *painter )
{
    painter->save();

    QWidget *w = qwtBGWidget2( this );

    const QPoint off = mapTo( w, QPoint() );
    painter->translate( -off );

    const QRect fillRect = rect().translated( off );

    if ( w->testAttribute( Qt::WA_StyledBackground ) )
    {
        painter->setClipRect( fillRect );

        QStyleOption opt;
        opt.initFrom( w );
        w->style()->drawPrimitive( QStyle::PE_Widget, &opt, painter, w);
    }
    else 
    {
        if ( !autoFillBackground() )
        {
            painter->fillRect( fillRect,
                w->palette().brush( w->backgroundRole() ) );
        }
    }

    painter->restore();
}

void QwtPlotOpenGLCanvas::drawBorder( QPainter *painter )
{
    const int fw = frameWidth();
    if ( fw <= 0 )
        return;

    if ( frameShadow() == QwtPlotOpenGLCanvas::Plain )
    {
        qDrawPlainRect( painter, frameRect(), 
            palette().shadow().color(), lineWidth() );
    }
    else
    {
        if ( frameShape() == QwtPlotOpenGLCanvas::Box )
        {
            qDrawShadeRect( painter, frameRect(), palette(),
                frameShadow() == Sunken, lineWidth(), midLineWidth() );
        }
        else
        {
            qDrawShadePanel( painter, frameRect(), palette(), 
                frameShadow() == Sunken, lineWidth() );
        }
    }
}

void QwtPlotOpenGLCanvas::replot()
{
    repaint();
}

QPainterPath QwtPlotOpenGLCanvas::borderPath( const QRect &rect ) const
{
    Q_UNUSED( rect );
    return QPainterPath();
}

QRect QwtPlotOpenGLCanvas::frameRect() const
{
    const int fw = frameWidth();
    return contentsRect().adjusted( -fw, -fw, fw, fw );
}
