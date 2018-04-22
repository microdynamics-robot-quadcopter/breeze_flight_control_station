/******************************************************************************
 * Software License Agreement (GPL V3 License)
 *
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
 * flight_control_station.cpp
 *
 * Author:
 * myyerrol<myyerrol@126.com>
 *
 * History:
 * <Authors>     <Date>         <Version>     <Operation>
 * myyerrol      2016.07.12     -             Finish basic gui
 * myyerrol      2018.04.21     1.0.0         Modify basic gui
 *
 * Description:
 * This .cpp file starts the gui of flight control station.
 *****************************************************************************/

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
