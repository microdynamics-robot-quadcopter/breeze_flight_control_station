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
 *  This .h file defines some elements for implementing the gui of
 *  flight control station.
 **********************************************************************/

#ifndef FLIGHT_CONTROL_STATION_H
#define FLIGHT_CONTROL_STATION_H

#include <QTimer>
#include <QMessageBox>
#include <QMainWindow>
#include <communication_serial_interface.h>
#include "flight_attitude_indicator.h"
#include "flight_altitude_indicator.h"
#include "flight_compass_indicator.h"

#define KEYBOARD_CONTROL 0

using namespace communication_serial;

namespace Ui {
class FlightControlStation;
}

class FlightControlStation : public QMainWindow
{
    Q_OBJECT
public:
    explicit FlightControlStation(QWidget *parent = 0,
                                  std::string serial_url = "",
                                  std::string config_addr = "");
    ~FlightControlStation();
protected slots:
    void openAboutWidget(void);
    void updateTimerOperation(void);
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
    int                          count_;
    float                        acc_x_actual_, acc_y_actual_, acc_z_actual_;
    float                        att_r_actual_, att_p_actual_, att_y_actual_;
    float                        acc_x_target_, acc_y_target_, acc_z_target_;
    float                        att_r_target_, att_p_target_, att_y_target_;
    float                        motor_thrust_acutal_;
    float                        motor_thrust_target_;
    float                        robot_alt_actual_;
    float                        robot_alt_target_;
    float                        robot_hei_actual_;
    float                        robot_hei_target_;
    float                        battery_capacity_;
    std::vector<float>           motor_speed_actual_;
    std::vector<float>           motor_speed_target_;
    std::vector<float>           motor_mileage_actual_;
    std::vector<float>           motor_mileage_target_;
    QMessageBox                  *about_widget_;
    QTimer                       *timer_;
    FlightAttitudeIndicator      *flight_attitude_indicator_;
    FlightAltitudeIndicator      *flight_altitude_indicator_;
    FlightCompassIndicator       *flight_compass_indicator_;
    Ui::FlightControlStation     *ui;
    CommunicationSerialInterface serial_interface_;
};

#endif // FLIGHT_CONTROL_STATION_H
