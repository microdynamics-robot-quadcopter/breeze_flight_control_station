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
 * flight_control_station.h
 *
 * Author:
 * myyerrol<myyerrol@126.com>
 *
 * History:
 * <Authors>     <Date>         <Version>     <Operation>
 * myyerrol      2016.07.12     -             Finish basic gui
 * myyerrol      2018.04.21     1.0           Modify basic gui
 *
 * Description:
 * This .h file defines some elements for implementing the gui of
 * flight control station.
 *****************************************************************************/

#ifndef FLIGHT_CONTROL_STATION_H
#define FLIGHT_CONTROL_STATION_H

#include <QCamera>
#include <QCameraInfo>
#include <QCameraViewfinder>
#include <QMainWindow>
#include <QMessageBox>
#include <QSerialPortInfo>
#include <QTimer>

//#include <communication_serial_interface.h>
//#include "fcs_indicator_attitude.h"
//#include "fcs_indicator_altitude.h"
//#include "fcs_indicator_compass.h"

#define KEYBOARD_CONTROL 0

//using namespace communication_serial;

namespace Ui {
class FlightControlStation;
}

class FlightControlStation : public QMainWindow
{
    Q_OBJECT

public:
    explicit FlightControlStation(QWidget *parent = 0/*,
                                  std::string serial_url = "",
                                  std::string config_addr = ""*/);
    ~FlightControlStation();
protected slots:
    void openAboutWidget(void);
    void openCameraViewFinder(void);
//    void updateTimerOperation(void);
    void closeCameraViewFinder(void);
protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);
private:
    void updateBufferRead(void);
    void updateBufferWrite(void);
    void updateUIFromRead(void);
    void updateUIFromWrite(void);
private:
    int                           count_;
    float                         acc_x_actual_, acc_y_actual_, acc_z_actual_;
    float                         att_r_actual_, att_p_actual_, att_y_actual_;
    float                         acc_x_target_, acc_y_target_, acc_z_target_;
    float                         att_r_target_, att_p_target_, att_y_target_;
    float                         motor_thrust_acutal_;
    float                         motor_thrust_target_;
    float                         robot_alt_actual_;
    float                         robot_alt_target_;
    float                         robot_hei_actual_;
    float                         robot_hei_target_;
    float                         battery_capacity_;
    std::vector<float>            motor_speed_actual_;
    std::vector<float>            motor_speed_target_;
    std::vector<float>            motor_mileage_actual_;
    std::vector<float>            motor_mileage_target_;
    QMessageBox                  *about_widget_;
    QTimer                       *timer_;
    QString                       serial_name_;
    QList<QSerialPortInfo>        serial_ports_info_;
    QCamera                      *camera_;
    QList<QCameraInfo>            cameras_info_;
    QCameraViewfinder            *camera_view_finder_;
//    FlightAttitudeIndicator      *flight_attitude_indicator_;
//    FlightAltitudeIndicator      *flight_altitude_indicator_;
//    FlightCompassIndicator       *flight_compass_indicator_;
    Ui::FlightControlStation     *ui;
//    CommunicationSerialInterface serial_interface_;
};

#endif // FLIGHT_CONTROL_STATION_H
