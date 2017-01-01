#include <qprinter.h>
#include <qprintdialog.h>
#include <qwt_color_map.h>
#include <qwt_plot_spectrogram.h>
#include <qwt_scale_widget.h>
#include <qwt_scale_draw.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_renderer.h>
#include "plot.h"

class MyZoomer: public QwtPlotZoomer
{
public:
    MyZoomer( QWidget *canvas ):
        QwtPlotZoomer( canvas )
    {
        setTrackerMode( AlwaysOn );
    }

    virtual QwtText trackerTextF( const QPointF &pos ) const
    {
        QColor bg( Qt::white );
        bg.setAlpha( 200 );

        QwtText text = QwtPlotZoomer::trackerTextF( pos );
        text.setBackgroundBrush( QBrush( bg ) );
        return text;
    }
};

class SpectrogramData: public QwtRasterData
{
public:
    SpectrogramData()
    {
        // some minor performance improvements wgen the spectrogram item
        // does not need to check for NaN values

        setAttribute( QwtRasterData::WithoutGaps, true );

        setInterval( Qt::XAxis, QwtInterval( -1.5, 1.5 ) );
        setInterval( Qt::YAxis, QwtInterval( -1.5, 1.5 ) );
        setInterval( Qt::ZAxis, QwtInterval( 0.0, 10.0 ) );
    }

    virtual double value( double x, double y ) const
    {
        const double c = 0.842;
        //const double c = 0.33;

        const double v1 = x * x + ( y - c ) * ( y + c );
        const double v2 = x * ( y + c ) + x * ( y + c );

        return 1.0 / ( v1 * v1 + v2 * v2 );
    }
};

class LinearColorMap: public QwtLinearColorMap
{
public:
    LinearColorMap( int formatType ):
        QwtLinearColorMap( Qt::darkCyan, Qt::red )
    {
        setFormat( ( QwtColorMap::Format ) formatType );

        addColorStop( 0.1, Qt::cyan );
        addColorStop( 0.6, Qt::green );
        addColorStop( 0.95, Qt::yellow );
    }
};

class HueColorMap: public QwtHueColorMap
{
public:
    HueColorMap( int formatType ):
        QwtHueColorMap( QwtColorMap::Indexed )
    {
        setFormat( ( QwtColorMap::Format ) formatType );

        //setHueInterval( 240, 60 );
        //setHueInterval( 240, 420 );
        setHueInterval( 0, 359 );
        setSaturation( 150 );
        setValue( 200 );
    }
};

class SaturationColorMap: public QwtSaturationValueColorMap
{
public:
    SaturationColorMap( int formatType )
    {
        setFormat( ( QwtColorMap::Format ) formatType );

        setHue( 220 );
        setSaturationInterval( 0, 255 );
        setValueInterval( 255, 255 );
    }
};

class ValueColorMap: public QwtSaturationValueColorMap
{
public:
    ValueColorMap( int formatType )
    {
        setFormat( ( QwtColorMap::Format ) formatType );

        setHue( 220 );
        setSaturationInterval( 255, 255 );
        setValueInterval( 70, 255 );
    }
};

class SVColorMap: public QwtSaturationValueColorMap
{
public:
    SVColorMap( int formatType )
    {
        setFormat( ( QwtColorMap::Format ) formatType );

        setHue( 220 );
        setSaturationInterval( 100, 255 );
        setValueInterval( 70, 255 );
    }
};

class AlphaColorMap: public QwtAlphaColorMap
{
public:
    AlphaColorMap( int formatType )
    {
        setFormat( ( QwtColorMap::Format ) formatType );

        //setColor( QColor("DarkSalmon") );
        setColor( QColor("SteelBlue") );
    }
};

Plot::Plot( QWidget *parent ):
    QwtPlot( parent ),
    d_formatType( 0 ),
    d_alpha(255)
{
    d_spectrogram = new QwtPlotSpectrogram();
    d_spectrogram->setRenderThreadCount( 0 ); // use system specific thread count
    d_spectrogram->setCachePolicy( QwtPlotRasterItem::PaintCache );

    QList<double> contourLevels;
    for ( double level = 0.5; level < 10.0; level += 1.0 )
        contourLevels += level;
    d_spectrogram->setContourLevels( contourLevels );

    d_spectrogram->setData( new SpectrogramData() );
    d_spectrogram->attach( this );

    const QwtInterval zInterval = d_spectrogram->data()->interval( Qt::ZAxis );

    // A color bar on the right axis
    QwtScaleWidget *rightAxis = axisWidget( QwtAxis::yRight );
    rightAxis->setTitle( "Intensity" );
    rightAxis->setColorBarEnabled( true );

    setAxisScale( QwtAxis::yRight, zInterval.minValue(), zInterval.maxValue() );
    setAxisVisible( QwtAxis::yRight );

    plotLayout()->setAlignCanvasToScales( true );

    setColorMap( Plot::RGBMap );

    // LeftButton for the zooming
    // MidButton for the panning
    // RightButton: zoom out by 1
    // Ctrl+RighButton: zoom out to full size

    QwtPlotZoomer* zoomer = new MyZoomer( canvas() );
    zoomer->setMousePattern( QwtEventPattern::MouseSelect2,
        Qt::RightButton, Qt::ControlModifier );
    zoomer->setMousePattern( QwtEventPattern::MouseSelect3,
        Qt::RightButton );

    QwtPlotPanner *panner = new QwtPlotPanner( canvas() );
    panner->setAxisEnabled( QwtAxis::yRight, false );
    panner->setMouseButton( Qt::MidButton );

    // Avoid jumping when labels with more/less digits
    // appear/disappear when scrolling vertically

    const QFontMetrics fm( axisWidget( QwtAxis::yLeft )->font() );
    QwtScaleDraw *sd = axisScaleDraw( QwtAxis::yLeft );
    sd->setMinimumExtent( fm.width( "100.00" ) );

    const QColor c( Qt::darkBlue );
    zoomer->setRubberBandPen( c );
    zoomer->setTrackerPen( c );
}

void Plot::showContour( bool on )
{
    d_spectrogram->setDisplayMode( QwtPlotSpectrogram::ContourMode, on );
    replot();
}

void Plot::showSpectrogram( bool on )
{
    d_spectrogram->setDisplayMode( QwtPlotSpectrogram::ImageMode, on );
    d_spectrogram->setDefaultContourPen( 
        on ? QPen( Qt::black, 0 ) : QPen( Qt::NoPen ) );

    replot();
}

void Plot::setColorTableSize( int type )
{
    int numColors = 0;
    switch( type )
    {
        case 1:
            numColors = 256;
            break;
        case 2:
            numColors = 1024;
            break;
        case 3:
            numColors = 16384;
            break;
    }

    d_spectrogram->setMaxRGBTableSize( numColors );
    replot();
}

void Plot::setColorFormat( int format )
{
    d_formatType = format;
    setColorMap( d_mapType );
}

void Plot::setColorMap( int type )
{
    QwtScaleWidget *axis = axisWidget( QwtAxis::yRight );
    const QwtInterval zInterval = d_spectrogram->data()->interval( Qt::ZAxis );

    d_mapType = type;

    int alpha = d_alpha;
    switch( type )
    {
        case Plot::HueMap:
        {
            d_spectrogram->setColorMap( new HueColorMap( d_formatType ) );
            axis->setColorMap( zInterval, new HueColorMap( d_formatType ) );
            break;
        }
        case Plot::SaturationMap:
        {
            d_spectrogram->setColorMap( new SaturationColorMap( d_formatType ) );
            axis->setColorMap( zInterval, new SaturationColorMap( d_formatType ) );
            break;
        }
        case Plot::ValueMap:
        {
            d_spectrogram->setColorMap( new ValueColorMap( d_formatType ) );
            axis->setColorMap( zInterval, new ValueColorMap( d_formatType ) );
            break;
        }
        case Plot::SVMap:
        {
            d_spectrogram->setColorMap( new SVColorMap( d_formatType ) );
            axis->setColorMap( zInterval, new SVColorMap( d_formatType ) );
            break;
        }
        case Plot::AlphaMap:
        {
            alpha = 255;
            d_spectrogram->setColorMap( new AlphaColorMap( d_formatType ) );
            axis->setColorMap( zInterval, new AlphaColorMap( d_formatType ) );
            break;
        }
        case Plot::RGBMap:
        default:
        {
            d_spectrogram->setColorMap( new LinearColorMap( d_formatType ) );
            axis->setColorMap( zInterval, new LinearColorMap( d_formatType ) );
        }
    }
    d_spectrogram->setAlpha( alpha );

    replot();
}

void Plot::setAlpha( int alpha )
{
    // setting an alpha value doesn't make sense in combination
    // with a color map interpolating the alpha value

    d_alpha = alpha;
    if ( d_mapType != Plot::AlphaMap )
    {
        d_spectrogram->setAlpha( alpha );
        replot();
    }
}

#ifndef QT_NO_PRINTER

void Plot::printPlot()
{
    QPrinter printer( QPrinter::HighResolution );
    printer.setOrientation( QPrinter::Landscape );
    printer.setOutputFileName( "spectrogram.pdf" );

    QPrintDialog dialog( &printer );
    if ( dialog.exec() )
    {
        QwtPlotRenderer renderer;

        if ( printer.colorMode() == QPrinter::GrayScale )
        {
            renderer.setDiscardFlag( QwtPlotRenderer::DiscardBackground );
            renderer.setDiscardFlag( QwtPlotRenderer::DiscardCanvasBackground );
            renderer.setDiscardFlag( QwtPlotRenderer::DiscardCanvasFrame );
            renderer.setLayoutFlag( QwtPlotRenderer::FrameWithScales );
        }

        renderer.renderTo( this, printer );
    }
}

#endif
