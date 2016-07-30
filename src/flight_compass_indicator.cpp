/***********************************************************************
 *  Software License Agreement (BSD License)
 *
 *  Copyright (c) 2016, Team MicroDynamics
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *  * Neither the name of the Team MicroDynamics nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 ***********************************************************************

 ***********************************************************************
 *  History:
 *  <Authors>        <Date>        <Operation>
 *  myyerrol         2016.7.12     Finish the basic gui
 *
 *  Description:
 *  This .cpp file implements the gui of flight compass indicator.
 **********************************************************************/

#include <QString>
#include <QKeyEvent>
#include <QPen>
#include <QPainter>
#include <QRegion>
#include <QtMath>
#include <QDebug>
#include <flight_compass_indicator.h>

FlightCompassIndicator::FlightCompassIndicator(QWidget *parent) :
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

    yaw_ = 0.0;

    connect(this, SIGNAL(replotCanvas(void)), this, SLOT(updateCanvas(void)));
}

FlightCompassIndicator::~FlightCompassIndicator()
{
}

void FlightCompassIndicator::setYaw(double yaw)
{
    yaw_ = yaw;

    if (yaw_ < 0) {
        yaw_ = 360 + yaw_;
    }
    if (yaw_ > 360) {
        yaw_ = yaw_ - 360;
    }

    emit replotCanvas();
}

double FlightCompassIndicator::getYaw()
{
    return yaw_;
}

void FlightCompassIndicator::updateCanvas(void)
{
    update();
}

void FlightCompassIndicator::paintEvent(QPaintEvent *)
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
        painter.rotate(-yaw_);

        for (int i = 0; i < yaw_line_number; i++) {
            if (i == 0) {
                string = "N";
                painter.setFont(QFont("Monospace", font_size * 1.2));
            }
            else if (i == 9) {
                string = "W";
                painter.setFont(QFont("Monospace", font_size * 1.2));
            }
            else if (i == 18) {
                string = "S";
                painter.setFont(QFont("Monospace", font_size * 1.2));
            }
            else if (i == 27) {
                string = "E";
                painter.setFont(QFont("Monospace", font_size * 1.2));
            }
            else {
                string = QString("%1").arg(i * unit_angular);
                painter.setFont(QFont("", font_size));
            }

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

        painter.rotate(yaw_);
    } while (false);

    // Draw the quadrotor.
    do {
        double quadrotor_body_size    = widget_size_curr_ / 10;
        double quadrotor_motor_radius = quadrotor_body_size;
        double quadrotor_motor_point  = quadrotor_body_size * 1.5;
        QPen   pen_orange(QColor(255, 140, 0));
        QPoint point_a(-quadrotor_motor_point, -quadrotor_motor_point);
        QPoint point_b(-quadrotor_motor_point, +quadrotor_motor_point);
        QPoint point_c(+quadrotor_motor_point, -quadrotor_motor_point);
        QPoint point_d(+quadrotor_motor_point, +quadrotor_motor_point);
        QPoint point_rect_a(-quadrotor_body_size / 2,
                            -quadrotor_body_size / 2);
        QPoint point_rect_b(-quadrotor_body_size / 2,
                            +quadrotor_body_size / 2);
        QPoint point_rect_c(+quadrotor_body_size / 2,
                            -quadrotor_body_size / 2);
        QPoint point_rect_d(+quadrotor_body_size / 2,
                            +quadrotor_body_size / 2);

        pen_orange.setWidth(5);
        painter.setPen(pen_orange);
        painter.setBrush(Qt::NoBrush);
        painter.drawPoint(point_a);
        painter.drawPoint(point_b);
        painter.drawPoint(point_c);
        painter.drawPoint(point_d);

        pen_orange.setWidth(3);
        painter.setPen(pen_orange);
        painter.drawRect(-quadrotor_body_size / 2,
                         -quadrotor_body_size / 2,
                          quadrotor_body_size,
                          quadrotor_body_size);
        painter.drawLine(point_a, point_rect_a);
        painter.drawLine(point_b, point_rect_b);
        painter.drawLine(point_c, point_rect_c);
        painter.drawLine(point_d, point_rect_d);
        painter.drawEllipse(QRect(-quadrotor_motor_point -
                                   quadrotor_motor_radius,
                                  -quadrotor_motor_point -
                                   quadrotor_motor_radius,
                                   quadrotor_motor_radius * 2,
                                   quadrotor_motor_radius * 2));
        painter.drawEllipse(QRect(-quadrotor_motor_point -
                                   quadrotor_motor_radius,
                                  +quadrotor_motor_point -
                                   quadrotor_motor_radius,
                                   quadrotor_motor_radius * 2,
                                   quadrotor_motor_radius * 2));
        painter.drawEllipse(QRect(+quadrotor_motor_point -
                                   quadrotor_motor_radius,
                                  -quadrotor_motor_point -
                                   quadrotor_motor_radius,
                                   quadrotor_motor_radius * 2,
                                   quadrotor_motor_radius * 2));
        painter.drawEllipse(QRect(+quadrotor_motor_point -
                                   quadrotor_motor_radius,
                                  +quadrotor_motor_point -
                                   quadrotor_motor_radius,
                                   quadrotor_motor_radius * 2,
                                   quadrotor_motor_radius * 2));
    } while (false);

    // Draw the arrow.
    do {
        int    arrow_size = widget_size_curr_ / 12;
        double fx_a, fx_b, fx_c, fy_a, fy_b, fy_c;

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
    } while (false);
}

void FlightCompassIndicator::resizeEvent(QResizeEvent *)
{
    widget_size_curr_ = qMin(width(), height()) - 2 * widget_size_offset_;
}

void FlightCompassIndicator::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Q: {
            yaw_ -= VALUE_STEP_COMPASS;
            break;
        }
        case Qt::Key_E: {
            yaw_ += VALUE_STEP_COMPASS;
            break;
        }
        default: {
            QWidget::keyPressEvent(event);
            break;
        }
    }

    update();
}
