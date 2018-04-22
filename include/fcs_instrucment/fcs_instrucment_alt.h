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
 * fcs_instrucment_alt.h
 *
 * Author:
 * Marek M. Cel<marekcel@marekcel.pl>
 * myyerrol<myyerrol@126.com>
 *
 * History:
 * <Authors>     <Date>         <Version>     <Operation>
 * Marek M. Cel  2013.--.--     --            Finish ALT instrument
 * myyerrol      2018.03.xx     1.0.0         Modify ALT instrument
 *
 * Description:
 * This .h file defines some elements for implementing the instrument of
 * Altimeter(ALT) according to QFlightInstruments project.
 *****************************************************************************/

#ifndef FCS_INSTRUCMENT_ALTITUDE_H
#define FCS_INSTRUCMENT_ALTITUDE_H

#include <QGraphicsView>
#include <QGraphicsSvgItem>

class FCSInstrucmentALT : public QGraphicsView
{
    Q_OBJECT

public:
    FCSInstrucmentALT(QWidget *parent = 0);
    virtual ~FCSInstrucmentALT();
    void reinitALT(void);
    void updateALT(void);
    void setALTAltitude(float altitude);
    void setALTPressure(float pressure);
protected:
    void resizeEvent(QResizeEvent *event);
private:
    void initALT(void);
    void resetALT(void);
    void updateALTView(void);
private:
    QGraphicsScene   *alt_scene_;
    QGraphicsSvgItem *alt_item_face_1_;
    QGraphicsSvgItem *alt_item_face_2_;
    QGraphicsSvgItem *alt_item_face_3_;
    QGraphicsSvgItem *alt_item_hand_1_;
    QGraphicsSvgItem *alt_item_hand_2_;
    QGraphicsSvgItem *alt_item_case_;
    float alt_altitude_;
    float alt_pressure_;
    float alt_scale_x_;
    float alt_scale_y_;
    const int alt_original_height_;
    const int alt_original_width_;
    QPointF alt_original_alt_ctr_;
    const int alt_face_1_z_;
    const int alt_face_2_z_;
    const int alt_face_3_z_;
    const int alt_hand_1_z_;
    const int alt_hand_2_z_;
    const int alt_case_z_;
};

#endif // FCS_INSTRUCMENT_ALTITUDE_H
