/******************************************************************************
 * Software License Agreement (GPL V3 License)
 *
 * Copyright (C) 2013 Marek M. Cel
 * Copyright (c) 2018 myyerrol(Team MicroDynamics)
 *
 * This file is part of breeze_flight_control_station.
 *
 * breeze_flight_control_station is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.

 * breeze_flight_control_station is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
 * Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with breeze_flight_control_station.  If not, see
 * <http://www.gnu.org/licenses/>.
 ******************************************************************************

 ******************************************************************************
 * File:
 * fcs_instrucment_adi.h
 *
 * Author:
 * Marek M. Cel<marekcel@marekcel.pl>
 * myyerrol<myyerrol@126.com>
 *
 * History:
 * <Authors>     <Date>         <Version>     <Operation>
 * Marek M. Cel  2013.--.--     --            Finish ADI instrument
 * myyerrol      2018.03.--     1.0.0         Modify ADI instrument
 *
 * Description:
 * This .h file defines some elements for implementing the instrument of
 * Attitude Director Indicator(ADI) according to QFlightInstruments project.
 *****************************************************************************/

#ifndef FCS_INSTRUCMENT_ATTITUDE_H
#define FCS_INSTRUCMENT_ATTITUDE_H

#include <QGraphicsView>
#include <QGraphicsSvgItem>

class FCSInstrucmentADI : public QGraphicsView
{
    Q_OBJECT

public:
    FCSInstrucmentADI(QWidget *parent = 0);
    virtual ~FCSInstrucmentADI();
    void reinitADI(void);
    void updateADI(void);
    void setADIAngleRoll(float angle_roll);
    void setADIAnglePitch(float angle_pitch);
protected:
    void resizeEvent(QResizeEvent *event);
private:
    void initADI(void);
    void resetADI(void);
    void updateADIView(void);
private:
    QGraphicsScene   *adi_scene_;
    QGraphicsSvgItem *adi_item_back_;
    QGraphicsSvgItem *adi_item_face_;
    QGraphicsSvgItem *adi_item_ring_;
    QGraphicsSvgItem *adi_item_case_;
    float adi_angle_roll_;
    float adi_angle_pitch_;
    float adi_face_delta_x_new_;
    float adi_face_delta_x_old_;
    float adi_face_delta_y_new_;
    float adi_face_delta_y_old_;
    float adi_scale_x_;
    float adi_scale_y_;
    const int adi_original_height_;
    const int adi_original_width_;
    const float adi_original_pix_per_deg_;
    QPointF adi_original_adi_ctr_;
    const int adi_back_z_;
    const int adi_face_z_;
    const int adi_ring_z_;
    const int adi_case_z_;
};

#endif // FCS_INSTRUCMENT_ATTITUDE_H
