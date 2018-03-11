/******************************************************************************
 * Software License Agreement (GPL V3 License)
 *
 * Copyright (C) 2014 bushuhui
 * Copyright (c) 2016 myyerrol(Team MicroDynamics)
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
 * fcs_indicator_attitude.h
 *
 * Author:
 * bushuhui<bushuhui@gmail.com>
 * myyerrol<myyerrol@126.com>
 *
 * History:
 * <Authors>     <Date>         <Version>     <Operation>
 * bushuhui      2014.12.03     --           Finish attitude indicator
 * myyerrol      2016.07.12     1.0          Modify attitude indicator
 *
 * Description:
 * This .h file defines some elements for implementing the indicator of
 * attitude according to qFlightInstruments project.
 *****************************************************************************/

#ifndef FLIGHT_ATTITUDE_INDICATOR_H
#define FLIGHT_ATTITUDE_INDICATOR_H

#include <QWidget>

#define VALUE_STEP_ATTITUDE 1

class FlightAttitudeIndicator : public QWidget
{
    Q_OBJECT
public:
    explicit FlightAttitudeIndicator(QWidget *parent = 0);
    ~FlightAttitudeIndicator();
    void setPitchAndRoll(double pitch, double roll);
    void setPitch(double pitch);
    void setRoll(double roll);
    double getPitch(void);
    double getRoll(void);
signals:
    void replotCanvas(void);
protected slots:
    void updateCanvas(void);
protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
    void keyPressEvent(QKeyEvent *event);
private:
    int    widget_size_min_;
    int    widget_size_max_;
    int    widget_size_curr_;
    int    widget_size_offset_;
    double pitch_;
    double roll_;
};

#endif // FLIGHT_ATTITUDE_INDICATOR_H
