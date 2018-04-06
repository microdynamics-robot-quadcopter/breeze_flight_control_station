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
 *  This .cpp file starts the gui of flight control station.
 **********************************************************************/

#include <QApplication>
#include <QDesktopWidget>
#include <flight_control_station.h>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    FlightControlStation flight_control_station(0/*, "serial:///dev/ttyUSB0",
                                                "/home/ubuntu/Desktop/breeze_flight_control_station/config/config.txt"*/);

    flight_control_station.move(
        (QApplication::desktop()->width()  -
         flight_control_station.width()) / 2,
        (QApplication::desktop()->height() -
         flight_control_station.height()) / 2);

    flight_control_station.show();

    return application.exec();
}
