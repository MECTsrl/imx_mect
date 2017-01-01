/* -*- mode: C++ ; c-file-style: "stroustrup" -*- *****************************
 * Qwt Widget Library
 * Copyright (C) 1997   Josef Wilgen
 * Copyright (C) 2002   Uwe Rathmann
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the Qwt License, Version 1.0
 *****************************************************************************/

#include "qwt_spline.h"
#include "qwt_math.h"
#include <qline.h>

// - bezier

static inline double qwtLineLength( const QPointF &p1, const QPointF &p2 )
{
   const double dx = p1.x() - p2.x();
   const double dy = p1.y() - p2.y();

   return qSqrt( dx * dx + dy * dy );
}

static inline QLineF qwtBezierControlLine(const QPointF &p0, const QPointF &p1, 
    const QPointF &p2, const QPointF &p3 )
{
    const double d02 = qwtLineLength(p0, p2);
    const double d13 = qwtLineLength(p1, p3);
    const double d12_2 = 0.5 * qwtLineLength(p1, p2);

    const bool b1 = ( d02 / 6.0 ) < d12_2;
    const bool b2 = ( d13 / 6.0 ) < d12_2;

    QPointF off1, off2;

    if( b1 )
    {
        if ( b2 )
        {
            // this is the normal case where both 1/6th 
            // vectors are less than half of d12_2

            const double s1 = ( p0 != p1 ) ? 6 : 3;
            off1 = ( p2 - p0 ) / s1;

            const double s2 = ( p2 != p3 ) ? 6 : 3;
            off2 = ( p1 - p3 ) / s2;
        }
        else
        {
            const double s = d12_2 / d13;

            off1 = ( p2 - p0 ) * s;
            off2 = ( p1 - p3 ) * s;
        }
    }
    else
    {
        if ( b2 )
        {
            // for this case d02/6 is more than half of d12_2, so
            // the d13/6 vector needs to be reduced

            const double s = d12_2 / d02;

            off1 = (p2 - p0) * s;
            off2 = (p1 - p3) * s;
        }
        else
        {
            off1 = (p2 - p0) * ( d12_2 / d02 );
            off2 = (p1 - p3) * ( d12_2 / d13 ); 
        }   
    }

    return QLineF( p1 + off1, p2 + off2 );
}

static inline QPointF qwtBezierPoint( const QLineF &ctrlLine, 
    const QPointF &p1, const QPointF &p2, double t )
{
    const double d1 = 3.0 * t;
    const double d2 = 3.0 * t * t;
    const double d3 = t * t * t;
    const double s  = 1.0 - t;

    const double x = (( s * p1.x() + d1 * ctrlLine.x1() ) * s + d2 * ctrlLine.x2() ) * s + d3 * p2.x();
    const double y = (( s * p1.y() + d1 * ctrlLine.y1() ) * s + d2 * ctrlLine.y2() ) * s + d3 * p2.y();

    return QPointF( x, y );
}

QPolygonF QwtSpline::fitBezier( const QPolygonF& points, int numPoints )
{
    const int size = points.size();
    if ( size <= 2 )
        return points;

    const QPointF *p = points.constData();

    double total_length = 0;
    for( int i = 0; i < size - 1; i++ )
        total_length += qwtLineLength( p[i], p[i+1] );

    const double delta = total_length / numPoints;

    double sum_of_deltas = 0;       // incrementing along the curve
    double sum_of_passed_subcurves = 0;

    QLineF controlLine;

    QPolygonF fittedPoints;
    for ( int i = 0; i < size - 1; i++ )
    {
        if ( i == 0 )
            controlLine = qwtBezierControlLine( p[0], p[0], p[1], p[2]);
        else if ( i == points.size() - 2 )
            controlLine = qwtBezierControlLine( p[size - 3], p[size - 2], p[size - 1], p[size - 1] );
        else
            controlLine = qwtBezierControlLine( p[i-1], p[i], p[i+1], p[i+2]);

        const QPointF &p1 = p[i];
        const QPointF &p2 = p[i + 1];
        const double length = qwtLineLength( p1, p2 );

        for(;;) 
        {
            const double offset = sum_of_deltas - sum_of_passed_subcurves;
            const double t = offset / length;

            // is sampling rate smaller than distance between current points
            if( t < 1.0 )
            {
                fittedPoints += qwtBezierPoint( controlLine, p1, p2, t );

                sum_of_deltas += delta;
                if( sum_of_deltas >= sum_of_passed_subcurves + length )
                {
                    sum_of_passed_subcurves += length;
                    break;
                }
            }
            else
            {
                if( sum_of_deltas >= sum_of_passed_subcurves + length )
                {
                    sum_of_passed_subcurves += length;
                    break; 
                }
            }
        }
    }
    fittedPoints += points.last();

    return fittedPoints;
}

QLineF QwtSpline::bezierControlLine( 
    const QPointF &p0, const QPointF &p1,
    const QPointF &p2, const QPointF &p3 )
{
    return qwtBezierControlLine( p0, p1, p2, p3 );
}

QPointF QwtSpline::bezierPoint( const QLineF &controlLine, 
    const QPointF &p1, const QPointF &p2, double t )
{
    return qwtBezierPoint( controlLine, p1, p2, t );
}

static inline void qwtCubicTo( const QPointF *p, 
    int i1, int i2, int i3, int i4, QPainterPath &path )
{
    const QLineF l = qwtBezierControlLine( p[i1], p[i2], p[i3], p[i4]);
    path.cubicTo( l.p1(), l.p2(), p[i3] );
}

QPainterPath QwtSpline::bezierPath( const QPolygonF &points, bool isClosed )
{
    const int size = points.size();

    QPainterPath path;
    if ( size == 0 )
        return path;

    const QPointF *p = points.constData();

    path.moveTo( p[0] );
    if ( size == 1 )
        return path;

    if ( size == 2 )
    {
        path.lineTo( p[1] );
    }
    else
    {
        if ( isClosed )
        {
            qwtCubicTo( p, size - 1, 0, 1, 2, path );
        }
        else
        {
            qwtCubicTo( p, 0, 0, 1, 2, path );
        }

        for ( int i = 1; i < size - 2; i++ )
            qwtCubicTo( p, i - 1, i, i + 1, i + 2, path );

        if ( isClosed )
        {
            qwtCubicTo( p, size - 3, size - 2, size - 1, 0, path );
            qwtCubicTo( p, size - 2, size - 1, 0, 1, path );
        }
        else
        {
            qwtCubicTo( p, size - 3, size - 2, size - 1, size - 1, path );
        }
    }

    return path;
}

// - natural

static QVector<double> qwtCofficientNatural( const QPolygonF &points )
{
    const int size = points.size();

    QVector<double> aa0( size - 1 );
    QVector<double> bb0( size - 1 );

    double dx1 = points[1].x() - points[0].x();
    double dy1 = ( points[1].y() - points[0].y() ) / dx1;

    for ( int i = 1; i < size - 1; i++ )
    {
        const double dx2 = points[i+1].x() - points[i].x();
        const double dy2 = ( points[i+1].y() - points[i].y() ) / dx2;

        aa0[i] = 2.0 * ( dx1 + dx2 );
        bb0[i] = 6.0 * ( dy1 - dy2 );

        dy1 = dy2;
        dx1 = dx2;
    }

    // L-U Factorization
    QVector<double> cc0( size - 1 );
    for ( int i = 1; i < size - 2; i++ )
    {
        const double dx = points[i+1].x() - points[i].x();

        cc0[i] = dx / aa0[i];
        aa0[i+1] -= dx * cc0[i];
    }

    // forward elimination
    QVector<double> s( size );
    s[1] = bb0[1];
    for ( int i = 2; i < size - 1; i++ )
    {
        s[i] = bb0[i] - cc0[i-1] * s[i-1];
    }

    // backward elimination
    s[size - 2] = - s[size - 2] / aa0[size - 2];
    for ( int i = size - 3; i > 0; i-- )
    {
        const double dx = points[i+1].x() - points[i].x();
        s[i] = - ( s[i] + dx * s[i+1] ) / aa0[i];
    }
    s[size - 1] = s[0] = 0.0;

    return s;
}

QPolygonF QwtSpline::fitNatural( const QPolygonF &points, int numPoints )
{
    const int size = points.size();
    if ( size <= 2 )
        return points;

    const QVector<double> s = qwtCofficientNatural( points );

    const double x1 = points.first().x();
    const double x2 = points.last().x();
    const double delta = ( x2 - x1 ) / ( numPoints - 1 );

    const QPointF *p = points.constData();

    double ai, bi, ci;
    QPointF pi;

    QPolygonF fittedPoints;
    for ( int i = 0, j = 0; i < numPoints; i++ )
    {
        double x = x1 + i * delta;
        if ( x > x2 )
            x = x2;

        if ( i == 0 || x > p[j + 1].x() )
        {
            while ( x > p[j + 1].x() )
                j++;

            const double dx = p[j + 1].x() - p[j].x();
            const double dy = p[j + 1].y() - p[j].y();

            ai = ( s[j+1] - s[j] ) / ( 6.0 * dx );
            bi = 0.5 * s[j];
            ci = dy / dx - ( s[j+1] + 2.0 * s[j] ) * dx / 6.0;
            pi = p[j];
        }

        const double dx = x - pi.x();
        const double y = ( ( ( ai * dx ) + bi ) * dx + ci ) * dx + pi.y();

        fittedPoints += QPointF( x, y );
    }

    return fittedPoints;
}

// - parametric

static QVector<double> qwtCofficientsParametric( const QVector<double> &xValues, const QVector<double> &yValues )
{
    const int size = xValues.size();

    QVector<double> aa0( size - 1 );
    QVector<double> cc0( size - 1 );
    QVector<double> dd0( size - 1 );

    double dx1 = xValues[size - 1] - xValues[size - 2];
    double dy1 = ( yValues[0] - yValues[size - 2] ) / dx1;

    for ( int i = 0; i < size - 1; i++ )
    {
        const double dx2 = xValues[i+1] - xValues[i];
        const double dy2 = ( yValues[i+1] - yValues[i] ) / dx2;

        aa0[i] = 2.0 * ( dx1 + dx2 );
        cc0[i] = dx2;
        dd0[i] = 6.0 * ( dy1 - dy2 );

        dy1 = dy2;
        dx1 = dx2;
    }

    // L-U Factorization
    aa0[0] = qSqrt( aa0[0] );
    cc0[0] = ( xValues[size - 1] - xValues[size - 2] ) / aa0[0];
    double sum0 = 0;

    QVector<double> bb0( size - 1 );
    for ( int i = 0; i < size - 3; i++ )
    {
        const double dx = xValues[i+1] - xValues[i];

        bb0[i] = dx / aa0[i];
        if ( i > 0 )
            cc0[i] = - cc0[i-1] * bb0[i-1] / aa0[i];
        aa0[i+1] = qSqrt( aa0[i+1] - qwtSqr( bb0[i] ) );
        sum0 += qwtSqr( cc0[i] );
    }

    const double dxx = xValues[size - 2] - xValues[size - 3];
    bb0[size - 3] = ( dxx - cc0[size - 4] * bb0[size - 4] ) / aa0[size - 3];
    aa0[size - 2] = qSqrt( aa0[size - 2] - qwtSqr( bb0[size - 3] ) - sum0 );


    QVector<double> s( size );
    s[0] = dd0[0] / aa0[0];

    double sum1 = 0;
    for ( int i = 1; i < size - 2; i++ )
    {
        s[i] = ( dd0[i] - bb0[i-1] * s[i-1] ) / aa0[i];
        sum1 += cc0[i-1] * s[i-1];
    }

    s[size - 2] = ( dd0[size - 2] - bb0[size - 3] * s[size - 3] - sum1 ) / aa0[size - 2];
    s[size - 2] = - s[size - 2] / aa0[size - 2];
    s[size - 3] = -( s[size - 3] + bb0[size - 3] * s[size - 2] ) / aa0[size - 3];
    for ( int i = size - 4; i >= 0; i-- )
        s[i] = - ( s[i] + bb0[i] * s[i+1] + cc0[i] * s[size - 2] ) / aa0[i];

    s[size-1] = s[0];

    return s;
}

QPolygonF QwtSpline::fitParametric( const QPolygonF &points, int numPoints ) 
{
    const int size = points.size();
    if ( size <= 2 )
        return points;

    QVector<double> xValues( size );
    QVector<double> yValuesX( size );
    QVector<double> yValuesY( size );

    const QPointF *p = points.data();

    double param = 0.0;
    for ( int i = 0; i < size; i++ )
    {
        const double x = p[i].x();
        const double y = p[i].y();

        if ( i > 0 )
        {
            const double d1 = x - yValuesX[i-1];
            const double d2 = y - yValuesY[i-1];

            const double delta = qSqrt( d1 * d1 + d2 * d2 );
            param += qMax( delta, 1.0 );
        }
        
        xValues[i] = param;
        yValuesX[i] = x;
        yValuesY[i] = y;
    }

    const QVector<double> sX = qwtCofficientsParametric( xValues, yValuesX );
    const QVector<double> sY = qwtCofficientsParametric( xValues, yValuesY );

    QVector<double> aaX( size );
    QVector<double> bbX( size );
    QVector<double> ccX( size );

    QVector<double> aaY( size );
    QVector<double> bbY( size );
    QVector<double> ccY( size );

    for ( int i = 0; i < size - 1; i++ )
    {
        const double dx = xValues[i+1] - xValues[i];

        aaX[i] = ( sX[i+1] - sX[i] ) / ( 6.0 * dx );
        bbX[i] = 0.5 * sX[i];
        ccX[i] = ( yValuesX[i+1] - yValuesX[i] )
            / dx - ( sX[i+1] + 2.0 * sX[i] ) * dx / 6.0;
    
        aaY[i] = ( sY[i+1] - sY[i] ) / ( 6.0 * dx );
        bbY[i] = 0.5 * sY[i];
        ccY[i] = ( yValuesY[i+1] - yValuesY[i] )
            / dx - ( sY[i+1] + 2.0 * sY[i] ) * dx / 6.0;
    }

    const double x2 = xValues.last();
    const double deltaX = x2 / ( numPoints - 1 );

    double ax, bx, cx, ay, by, cy;

    QPolygonF fittedPoints;
    for ( int i = 0, j = 0; i < numPoints; i++ )
    {
        double x = i * deltaX;
        if ( x > x2 )
            x = x2;

        if ( i == 0 || x > xValues[j + 1] )
        {
            while ( x > xValues[j + 1] )
                j++;

            ax = aaX[j];
            bx = bbX[j];
            cx = ccX[j];

            ay = aaY[j];
            by = bbY[j];
            cy = ccY[j];
        }

        const double dx = x - xValues[j];

        double px = ( ( ( ax * dx ) + bx ) * dx + cx ) * dx + yValuesX[j];
        double py = ( ( ( ay * dx ) + by ) * dx + cy ) * dx + yValuesY[j];

        fittedPoints += QPointF( px, py );
    }

    return fittedPoints;
}
