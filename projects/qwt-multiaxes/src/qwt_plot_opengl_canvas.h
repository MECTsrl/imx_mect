/* -*- mode: C++ ; c-file-style: "stroustrup" -*- *****************************
 * Qwt Widget Library
 * Copyright (C) 1997   Josef Wilgen
 * Copyright (C) 2002   Uwe Rathmann
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the Qwt License, Version 1.0
 *****************************************************************************/

#ifndef QWT_PLOT_OPENGL_CANVAS_H
#define QWT_PLOT_OPENGL_CANVAS_H

#include "qwt_global.h"
#include <qframe.h>
#include <qopenglwidget.h>

class QwtPlot;

class QWT_EXPORT QwtPlotOpenGLCanvas: public QOpenGLWidget
{
    Q_OBJECT

    Q_ENUMS( Shape Shadow )

    Q_PROPERTY( Shadow frameShadow READ frameShadow WRITE setFrameShadow )
    Q_PROPERTY( Shape frameShape READ frameShape WRITE setFrameShape )
    Q_PROPERTY( int lineWidth READ lineWidth WRITE setLineWidth )
    Q_PROPERTY( int midLineWidth READ midLineWidth WRITE setMidLineWidth )
    Q_PROPERTY( int frameWidth READ frameWidth )
    Q_PROPERTY( QRect frameRect READ frameRect DESIGNABLE false )

public:
    enum Shadow
    {
        Plain = QFrame::Plain,
        Raised = QFrame::Raised,
        Sunken = QFrame::Sunken
    };

    enum Shape
    {
        NoFrame = QFrame::NoFrame,

        Box = QFrame::Box,
        Panel = QFrame::Panel
    };

    explicit QwtPlotOpenGLCanvas( QwtPlot * = NULL );
    virtual ~QwtPlotOpenGLCanvas();

    void setFrameStyle( int style );
    int frameStyle() const;

    void setFrameShadow( Shadow );
    Shadow frameShadow() const;

    void setFrameShape( Shape );
    Shape frameShape() const;

    void setLineWidth( int );
    int lineWidth() const;

    void setMidLineWidth( int );
    int midLineWidth() const;

    int frameWidth() const;
    QRect frameRect() const;

    Q_INVOKABLE QPainterPath borderPath( const QRect & ) const;

    virtual bool event( QEvent * );

public Q_SLOTS:
    void replot();

protected:
    virtual void paintEvent( QPaintEvent * );

    virtual void drawBackground( QPainter * );
    virtual void drawBorder( QPainter * );
    virtual void drawItems( QPainter * );

private:
    class PrivateData;
    PrivateData *d_data;
};

#endif
