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
 * fcs_indicator_compass.h
 *
 * Author:
 * bushuhui<bushuhui@gmail.com>
 * myyerrol<myyerrol@126.com>
 *
 * History:
 * <Authors>     <Date>         <Version>     <Operation>
 * bushuhui      2014.12.03     --           Finish compass indicator
 * myyerrol      2016.07.12     1.0          Modify compass indicator
 *
 * Description:
 * This .h file defines some elements for implementing the indicator of
 * compass according to qFlightInstruments project.
 *****************************************************************************/

#ifndef FLIGHT_COMPASS_INDICATOR_H
#define FLIGHT_COMPASS_INDICATOR_H

#include <QWidget>

#define VALUE_STEP_COMPASS 1

class FlightCompassIndicator : public QWidget
{
    Q_OBJECT
public:
    explicit FlightCompassIndicator(QWidget *parent = 0);
    ~FlightCompassIndicator();
    void setYaw(double yaw);
    double getYaw(void);
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
    double yaw_;
};

#endif // FLIGHT_COMPASS_INDICATOR_H
