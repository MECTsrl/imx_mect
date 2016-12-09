/* -*- mode: C++ ; c-file-style: "stroustrup" -*- *****************************
 * Qwt Widget Library
 * Copyright (C) 1997   Josef Wilgen
 * Copyright (C) 2002   Uwe Rathmann
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the Qwt License, Version 1.0
 *****************************************************************************/

#ifndef QWT_SPLINE_H
#define QWT_SPLINE_H 1

#include "qwt_global.h"
#include <qpolygon.h>
#include <qline.h>
#include <qpainterpath.h>

namespace QwtSpline
{
    QWT_EXPORT QPolygonF fitBezier( const QPolygonF &, int numPoints );
    QWT_EXPORT QPolygonF fitNatural( const QPolygonF &, int numPoints );
    QWT_EXPORT QPolygonF fitParametric( const QPolygonF &, int numPoints );

    QWT_EXPORT QLineF bezierControlLine( const QPointF &p0, const QPointF &p1,
        const QPointF &p2, const QPointF &p3 );
    QPointF bezierPoint( const QLineF &controlLine, 
        const QPointF &p0, const QPointF &p1, double t );

    QWT_EXPORT QPainterPath bezierPath( const QPolygonF &, bool isClosed = false );
};

#endif
