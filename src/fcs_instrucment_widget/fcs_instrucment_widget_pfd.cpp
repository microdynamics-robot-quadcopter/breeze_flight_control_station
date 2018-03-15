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
 * fcs_instrucment_widget_pfd.cpp
 *
 * Author:
 * Marek M. Cel<marekcel@marekcel.pl>
 * myyerrol<myyerrol@126.com>
 *
 * History:
 * <Authors>     <Date>         <Version>     <Operation>
 * Marek M. Cel  2013.--.--     --            Finish PFD widget
 * myyerrol      2018.03.13     1.0           Modify PFD widget
 *
 * Description:
 * This .cpp file implements the widget of Primary Flight Display(PFD)
 * according to QFlightInstruments project.
 *****************************************************************************/

#include <fcs_instrucment_widget_pfd.h>
#include <ui_fcs_instrucment_widget_pfd.h>

FCSInstrucmentWidgetPFD::FCSInstrucmentWidgetPFD(QWidget *parent) :
    QWidget(parent),
    widget_ui_(new Ui::FCSInstrucmentWidgetPFD),
    widget_pfd_(0),
    widget_layout_(0)
{
    widget_ui_->setupUi(this);

    setupWidgetUi();

    widget_pfd_ = widget_ui_->graphics_pfd;
}

FCSInstrucmentWidgetPFD::~FCSInstrucmentWidgetPFD()
{
    if (widget_layout_) {
        delete widget_layout_;
    }
    else {
        ;
    }

    widget_layout_ = 0;

    if (widget_ui_) {
        delete widget_ui_;
    }
    else {
        ;
    }

    widget_ui_ = 0;
}

void FCSInstrucmentWidgetPFD::setupWidgetUi(void)
{
    widget_layout_ = new FCSInstrucmentLayout(this);

    widget_layout_->setContentsMargins(0, 0, 0, 0);
    widget_layout_->addWidget(widget_ui_->frame_pfd);

    setLayout(widget_layout_);
}
