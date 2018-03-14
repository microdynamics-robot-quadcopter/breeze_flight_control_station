/******************************************************************************
 * Software License Agreement (GPL V3 License)
 *
 * Copyright (C) 2017 qijiabo
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
 * fcs_custom_tab_widget.cpp
 *
 * Author:
 * qijiabo
 * myyerrol<myyerrol@126.com>
 *
 * History:
 * <Authors>     <Date>         <Version>     <Operation>
 * qijiabo       2017.07.04     --            Finish custom tab widget
 * myyerrol      2018.03.14     1.0           Modify custom tab widget
 *
 * Description:
 * This .cpp file implements the custom tab widget of QTabWidget according to
 * qijiabo's tutorial.
 *****************************************************************************/

#include <fcs_custom_tab_widget.h>
#include <fcs_custom_tab_style.h>

FCSCustomTabWidget::FCSCustomTabWidget(QWidget *parent) :
    QTabWidget(parent)
{
    this->tabBar()->setStyle(new FCSCustomTabStyle);
}

FCSCustomTabWidget::~FCSCustomTabWidget()
{
}
