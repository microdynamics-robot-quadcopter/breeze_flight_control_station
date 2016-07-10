#include <QString>
#include <QKeyEvent>
#include <QPen>
#include <QPainter>
#include <QRegion>
#include <QtMath>
#include <QDebug>
#include "flight_altitude_indicator.h"

FlightAltitudeIndicator::FlightAltitudeIndicator(QWidget *parent) :
    QWidget(parent)
{
    widget_size_min_    = 200;
    widget_size_max_    = 600;
    widget_size_offset_ = 2;
    widget_size_curr_   = widget_size_min_ - 2 * widget_size_offset_;

    setMinimumSize(widget_size_min_, widget_size_min_);
    setMaximumSize(widget_size_max_, widget_size_max_);
    resize(widget_size_min_, widget_size_min_);

    setFocusPolicy(Qt::NoFocus);

    altitude_ = 0.0;
    height_   = 0.0;

    connect(this, SIGNAL(replotCanvas(void)), this, SLOT(updateCanvas(void)));
}

FlightAltitudeIndicator::~FlightAltitudeIndicator()
{
}

void FlightAltitudeIndicator::setAltitudeAndHeight(double altitude,
                                                   double height)
{
    altitude_ = altitude;
    height_   = height;
    emit replotCanvas();
}

void FlightAltitudeIndicator::setAltitude(double altitude)
{
    altitude_ = altitude;
    emit replotCanvas();
}

void FlightAltitudeIndicator::setHeight(double height)
{
    height_ = height;
    emit replotCanvas();
}

double FlightAltitudeIndicator::getAltitude(void)
{
    return altitude_;
}

double FlightAltitudeIndicator::getHeight(void)
{
    return height_;
}

void FlightAltitudeIndicator::updateCanvas(void)
{
    update();
}

void FlightAltitudeIndicator::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen_black(Qt::black);
    QBrush brush_sky(QColor(48, 172, 220));

    pen_black.setWidth(2);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);

    // Draw the background's color.
    do {
        painter.setPen(pen_black);
        painter.setBrush(brush_sky);
        painter.drawEllipse(-widget_size_curr_ / 2,
                            -widget_size_curr_ / 2,
                             widget_size_curr_,
                             widget_size_curr_);
    } while (false);
}

void FlightAltitudeIndicator::resizeEvent(QResizeEvent *)
{
    widget_size_curr_ = qMin(width(), height()) - 2 * widget_size_offset_;
}

void FlightAltitudeIndicator::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_U: {
            altitude_ += VALUE_CHANGING_STEP;
            break;
        }
        case Qt::Key_I: {
            altitude_ -= VALUE_CHANGING_STEP;
            break;
        }
        case Qt::Key_J: {
            height_ += VALUE_CHANGING_STEP;
            break;
        }
        case Qt::Key_K: {
            height_ -= VALUE_CHANGING_STEP;
            break;
        }
        default: {
            QWidget::keyPressEvent(event);
            break;
        }
    }

    update();
}
