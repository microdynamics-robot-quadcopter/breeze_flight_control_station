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
 * fcs_indicator_altitude.h
 *
 * Author:
 * bushuhui<bushuhui@gmail.com>
 * myyerrol<myyerrol@126.com>
 *
 * History:
 * <Authors>     <Date>         <Version>     <Operation>
 * bushuhui      2014.12.03     --           Finish altitude indicator
 * myyerrol      2016.07.12     1.0.1        Modify altitude indicator
 *
 * Description:
 * This .h file defines some elements for implementing the indicator of
 * altitude according to qFlightInstruments project.
 *****************************************************************************/

#ifndef FLIGHT_ALTITUDE_INDICATOR_H
#define FLIGHT_ALTITUDE_INDICATOR_H

#include <QWidget>

#define VALUE_STEP_ALTITUDE 0.01
#define VALUE_STEP_HEIGHT   0.01

class FlightAltitudeIndicator : public QWidget
{
    Q_OBJECT
public:
    explicit FlightAltitudeIndicator(QWidget *parent = 0);
    ~FlightAltitudeIndicator();
    void setAltitudeAndHeight(double altitude, double height);
    void setAltitude(double altitude);
    void setHeight(double height);
    double getAltitude(void);
    double getHeight(void);
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
    double altitude_;
    double height_;
};

#endif // FLIGHT_ALTITUDE_INDICATOR_H
