#include <QString>
#include <QKeyEvent>
#include <QPen>
#include <QPainter>
#include <QRegion>
#include <QtMath>
#include "flight_attitude_indicator.h"

FlightAttitudeIndicator::FlightAttitudeIndicator(QWidget *parent) :
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

    pitch_ = 0.0;
    roll_  = 0.0;

    connect(this, SIGNAL(replotCanvas(void)), this, SLOT(updateCanvas(void)));
}

FlightAttitudeIndicator::~FlightAttitudeIndicator()
{
}

void FlightAttitudeIndicator::setPitchAndRoll(double pitch, double roll)
{
    pitch_ = pitch;
    roll_  = roll;

    if (pitch_ < -90) {
        pitch_ = -90;
    }
    if (pitch_ > 90) {
        pitch_ = 90;
    }
    if (roll_ < -180) {
        roll_ = -180;
    }
    if (roll_ > 180) {
        roll_ = 180;
    }

    emit replotCanvas();
}

void FlightAttitudeIndicator::setPitch(double pitch)
{
    pitch_  = pitch;

    if (pitch_ < -90) {
        pitch_ = -90;
    }
    if (pitch_ > 90) {
        pitch_ = 90;
    }

    emit replotCanvas();
}

void FlightAttitudeIndicator::setRoll(double roll)
{
    roll_ = roll;

    if (roll_ < -180) {
        roll_ = -180;
    }
    if (roll_ > 180) {
        roll_ = 180;
    }

    emit replotCanvas();
}

double FlightAttitudeIndicator::getPitch(void)
{
    return pitch_;
}

double FlightAttitudeIndicator::getRoll(void)
{
    return roll_;
}

void FlightAttitudeIndicator::updateCanvas(void)
{
    update();
}

void FlightAttitudeIndicator::resizeEvent(QResizeEvent *)
{
    widget_size_curr_ = qMin(width(), height()) - 2 * widget_size_offset_;
}

void FlightAttitudeIndicator::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QBrush   background_sky(QColor(48, 172, 220));
    QBrush   background_ground(QColor(247, 168, 21));
    QPen     pen_white(Qt::white);
    QPen     pen_black(Qt::black);
    QPen     pen_pitch(Qt::white);
    QPen     pen_pitch_zero(Qt::green);

    pen_white.setWidth(2);
    pen_black.setWidth(2);
    pen_pitch_zero.setWidth(3);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.rotate(roll_);

    double pitch_temp_ = -pitch_;

    // Draw the background.
    do {
        int y_min, y_max;

        y_min = widget_size_curr_ / 2 * -40.0 / 45.0;
        y_max = widget_size_curr_ / 2 *  40.0 / 45.0;

        int y = widget_size_curr_ / 2 * pitch_temp_ / 45.0;

        if (y < y_min) {
            y = y_min;
        }
        if (y > y_max) {
            y = y_max;
        }

        int    x = qSqrt(widget_size_curr_ * widget_size_curr_ / 4 - y * y);
        double theta = qAtan((double)(y) / x);
        theta = theta * 180 / M_PI;

        painter.setPen(pen_black);
        painter.setBrush(background_sky);
        painter.drawChord(-widget_size_curr_ / 2,
                          -widget_size_curr_ / 2,
                           widget_size_curr_,
                           widget_size_curr_,
                           theta * 16,
                           (180 - 2 * theta) * 16);

        painter.setBrush(background_ground);
        painter.drawChord(-widget_size_curr_ / 2,
                          -widget_size_curr_ / 2,
                           widget_size_curr_,
                           widget_size_curr_,
                           theta * 16,
                           -(180 + 2 * theta) * 16);
    } while(false);

    QRegion mask_region(-widget_size_curr_ / 2,
                        -widget_size_curr_ / 2,
                         widget_size_curr_,
                         widget_size_curr_,
                         QRegion::Ellipse);
    painter.setClipRegion(mask_region);

    // Draw the pitch's lines and marker.
    do {
        int     x_a, y_a, x_b, y_b;
        int     text_width;
        int     line_short;
        int     line_long = widget_size_curr_ / 8;
        int     font_size = 8;
        double  pitch;
        double  chord_length;
        QString string;

        pen_pitch.setWidth(2);
        painter.setFont(QFont("", font_size));

        // Draw the pitch's lines.
        for (int i = -9; i <= 9; i++) {
            pitch = i * 10;
            string = QString("%1").arg(-pitch);

            if (i % 3 == 0) {
                line_short = line_long;
            }
            else {
                line_short = line_long / 2;
            }
            if (i == 0) {
                painter.setPen(pen_pitch_zero);
                line_short = line_short * 1.8;
            }
            else {
                painter.setPen(pen_pitch);
            }

            y_a = widget_size_curr_ / 2 * pitch       / 45.0 -
                  widget_size_curr_ / 2 * pitch_temp_ / 45.0;
            x_a = line_short;
            chord_length = qSqrt(x_a * x_a + y_a * y_a);

            if (chord_length > widget_size_curr_ / 2) {
                continue;
            }

            painter.drawLine(QPointF(-line_short, 1.0 * y_a),
                             QPointF(+line_short, 1.0 * y_a));
            text_width = 100;

            if (i % 3 == 0 && i != 0) {
                painter.setPen(QPen(Qt::white));
                x_b = -x_a - 2 - text_width;
                y_b = y_a - font_size / 2 - 1;
                painter.drawText(QRectF(x_b, y_b, text_width, font_size + 2),
                                 Qt::AlignRight | Qt::AlignVCenter, string);
            }
        }

        // Draw the marker.
        int    marker_size = widget_size_curr_ / 20;
        double fx_a, fx_b, fx_c, fy_a, fy_b, fy_c;

        painter.setBrush(QBrush(Qt::red));
        painter.setPen(Qt::NoPen);

        fx_a = marker_size;
        fy_a = 0;
        fx_b = fx_a + marker_size;
        fy_b = -marker_size / 2;
        fx_c = fx_a + marker_size;
        fy_c = marker_size / 2;

        QPointF points_a[3] = {
            QPointF(fx_a, fy_a),
            QPointF(fx_b, fy_b),
            QPointF(fx_c, fy_c)
        };

        painter.drawPolygon(points_a, 3);

        QPointF points_b[3] = {
            QPointF(-fx_a, fy_a),
            QPointF(-fx_b, fy_b),
            QPointF(-fx_c, fy_c)
        };

        painter.drawPolygon(points_b, 3);
    } while (false);

    // Draw the roll's degree lines.
    do {
        int     roll_line_number = 36;
        int     roll_line_length = widget_size_curr_ / 25;
        int     font_size        = 8;
        double  unit_angular     = 360.0 / roll_line_number;
        double  fx_a, fx_b, fy_a, fy_b;
        QString string;

        pen_black.setWidth(1);
        painter.setPen(pen_black);
        painter.setFont(QFont("", font_size));

        for (int i = 0; i < roll_line_number; i++) {
            if (i < roll_line_number / 2) {
                string = QString("%1").arg(-i * unit_angular);
            }
            else {
                string = QString("%1").arg(360 - i * unit_angular);
            }

            fx_a = 0;
            fy_a = -widget_size_curr_ / 2 + widget_size_offset_;
            fx_b = 0;

            if (i % 3 == 0) {
                fy_b = fy_a + roll_line_length;
                painter.drawLine(QPointF(fx_a, fy_a), QPointF(fx_b, fy_b));
                fy_b = fy_a + roll_line_length + 2;
                painter.drawText(QRectF(-50, fy_b, 100, font_size + 2),
                                 Qt::AlignCenter, string);
            }
            else {
                fy_b = fy_a + roll_line_length / 2;
                painter.drawLine(QPointF(fx_a, fy_a), QPointF(fx_b, fy_b));
            }

            painter.rotate(unit_angular);
        }
    } while (false);

    // Draw the roll's marker.
    do {
        int    roll_marker_size = widget_size_curr_ / 25;
        double fx_a, fx_b, fx_c, fy_a, fy_b, fy_c;

        painter.rotate(-roll_);
        painter.setBrush(QBrush(Qt::black));

        fx_a = 0;
        fy_a = -widget_size_curr_ / 2 + widget_size_offset_;
        fx_b = fx_a - roll_marker_size / 2;
        fy_b = fy_a + roll_marker_size;
        fx_c = fx_a + roll_marker_size / 2;
        fy_c = fy_a + roll_marker_size;

        QPointF points[3] = {
            QPointF(fx_a, fy_a),
            QPointF(fx_b, fy_b),
            QPointF(fx_c, fy_c)
        };

        painter.drawPolygon(points, 3);
    } while (false);
}

void FlightAttitudeIndicator::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Up: {
            if (pitch_ < 90) {
                pitch_ += VALUE_CHANGING_STEP;
            }
            break;
        }
        case Qt::Key_Down: {
            if (pitch_ > -90) {
                pitch_ -= VALUE_CHANGING_STEP;
            }
            break;
        }
        case Qt::Key_Left: {
            roll_ -= VALUE_CHANGING_STEP;
            break;
        }
        case Qt::Key_Right: {
            roll_ += VALUE_CHANGING_STEP;
            break;
        }
        default: {
            QWidget::keyPressEvent(event);
            break;
        }
    }

    update();
}
