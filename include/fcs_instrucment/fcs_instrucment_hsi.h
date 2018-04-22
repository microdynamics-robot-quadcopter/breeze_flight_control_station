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
 * fcs_instrucment_hsi.h
 *
 * Author:
 * Marek M. Cel<marekcel@marekcel.pl>
 * myyerrol<myyerrol@126.com>
 *
 * History:
 * <Authors>     <Date>         <Version>     <Operation>
 * Marek M. Cel  2013.--.--     --            Finish HSI instrument
 * myyerrol      2018.03.xx     1.0.0         Modify HSI instrument
 *
 * Description:
 * This .h file defines some elements for implementing the instrument of
 * Horizontal Situation Indicator(HSI) according to QFlightInstruments project.
 *****************************************************************************/

#ifndef FCS_INSTRUCMENT_COMPASS_H
#define FCS_INSTRUCMENT_COMPASS_H

#include <QGraphicsView>
#include <QGraphicsSvgItem>

class FCSInstrucmentHSI : public QGraphicsView
{
    Q_OBJECT

public:
    FCSInstrucmentHSI(QWidget *parent = 0);
    virtual ~FCSInstrucmentHSI();
    void reinitHSI(void);
    void updateHSI(void);
    void setHSIHeading(float heading);
protected:
    void resizeEvent(QResizeEvent *event);
private:
    void initHSI(void);
    void resetHSI(void);
    void updateHSIView(void);
private:
    QGraphicsScene   *hsi_scene_;
    QGraphicsSvgItem *hsi_item_face_;
    QGraphicsSvgItem *hsi_item_case_;
    float hsi_heading_;
    float hsi_scale_x_;
    float hsi_scale_y_;
    const int hsi_original_height_;
    const int hsi_original_width_;
    QPointF hsi_original_hsi_ctr_;
    const int hsi_face_z_;
    const int hsi_case_z_;
};

#endif // FCS_INSTRUCMENT_COMPASS_H
