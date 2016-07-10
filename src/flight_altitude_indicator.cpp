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

    // Draw the background's numbers and lines.
    do {
        int     yaw_line_number = 36;
        int     yaw_line_length = widget_size_curr_ / 25;
        int     font_size       = 10;
        double  unit_angular    = 360.0 / yaw_line_number;
        double  fx_a, fx_b, fy_a, fy_b;
        QString string;

        pen_black.setWidth(2);
        painter.setPen(pen_black);
        painter.setFont(QFont("", font_size));

        for (int i = 0; i < yaw_line_number; i++) {
            string = QString("%1").arg(i);

            fx_a = 0.0;
            fy_a = -widget_size_curr_ / 2 + widget_size_offset_;
            fx_b = 0.0;

            if (i % 3 == 0) {
                fy_b = fy_a + yaw_line_length;
                painter.drawLine(QPointF(fx_a, fy_a), QPointF(fx_b, fy_b));
                fy_b = fy_a + yaw_line_length + 4;
                painter.drawText(QRectF(-50, fy_b, 100, font_size + 2),
                                 Qt::AlignCenter, string);
            }
            else {
                fy_b = fy_a + yaw_line_length / 2;
                painter.drawLine(QPointF(fx_a, fy_a), QPointF(fx_b, fy_b));
            }

            painter.rotate(-unit_angular);
        }
    } while (false);

    // Draw the arrow.
    do {
        int    arrow_size = widget_size_curr_ / 12;
        double fx_a, fx_b, fx_c, fy_a, fy_b, fy_c;

        painter.rotate(-100 * altitude_);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QBrush(QColor(Qt::red)));

        fx_a = 0;
        fy_a = -widget_size_curr_ / 2.5 + widget_size_offset_;
        fx_b = fx_a - arrow_size / 2;
        fy_b = fy_a + arrow_size;
        fx_c = fx_a + arrow_size / 2;
        fy_c = fy_a + arrow_size;

        QPointF points[3] = {
            QPointF(fx_a, fy_a),
            QPointF(fx_b, fy_b),
            QPointF(fx_c, fy_c)
        };

        painter.drawPolygon(points, 3);
        painter.rotate(100 * altitude_);
    } while (false);

    // Draw the text.
    do {
        int    font_size = 15;
        double fx_a, fy_a;

        fx_a = -50;
        fy_a = -widget_size_curr_ / 3.5 + widget_size_offset_;

        painter.setPen(pen_black);
        painter.setBrush(Qt::NoBrush);
        painter.setFont(QFont("", font_size));
        painter.drawText(QRectF(fx_a, fy_a, 100, font_size + 5),
                         Qt::AlignCenter, "x 0.1m");
    } while (false);

    // Draw the altitude and height.
    do {
        int     font_size = 15;
        int     fx, fy, width, height;
        QString string;

        width  = 120;
        height = (font_size + 10) * 2;
        fx     = - width  / 2;
        fy     = - height / 2;

        pen_black.setWidth(2);
        painter.setPen(pen_black);
        painter.setBrush(QBrush(Qt::white));
        painter.setFont(QFont("", font_size));
        painter.drawRect(fx, fy, width, height);

        string = QString("%1").arg(altitude_);
        string = "ALT: " + string + "m";
        painter.drawText(QRectF(fx, fy + 2, width, height / 2),
                         Qt::AlignCenter, string);

        string = QString("%1").arg(height_);
        string = "HEI: " + string + "m";
        painter.drawText(QRectF(fx, fy + height / 2, width, height / 2),
                         Qt::AlignCenter, string);
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
