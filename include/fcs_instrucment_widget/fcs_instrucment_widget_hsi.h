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
 * fcs_instrucment_widget_hsi.h
 *
 * Author:
 * Marek M. Cel<marekcel@marekcel.pl>
 * myyerrol<myyerrol@126.com>
 *
 * History:
 * <Authors>     <Date>         <Version>     <Operation>
 * Marek M. Cel  2013.--.--     --            Finish HSI widget
 * myyerrol      2018.03.14     1.0           Modify HSI widget
 *
 * Description:
 * This .h file defines some elements for implementing the widget of Horizontal
 * Situation Indicator(HSI) according to QFlightInstruments project.
 *****************************************************************************/

#ifndef FCS_INSTRUCMENT_WIDGET_HSI_H
#define FCS_INSTRUCMENT_WIDGET_HSI_H

#include <QWidget>
#include <fcs_instrucment_hsi.h>
#include <fcs_instrucment_layout.h>

namespace Ui {
class FCSInstrucmentWidgetHSI;
}

class FCSInstrucmentWidgetHSI : public QWidget
{
    Q_OBJECT

public:
    explicit FCSInstrucmentWidgetHSI(QWidget *parent = 0);
    ~FCSInstrucmentWidgetHSI();
    inline void updateHSI(void)
    {
        widget_hsi_->updateHSI();
    }
    inline void setHSIHeading(float heading)
    {
        widget_hsi_->setHSIHeading(heading);
    }
private:
    void setupWidgetUi(void);
private:
    Ui::FCSInstrucmentWidgetHSI *widget_ui_;
    FCSInstrucmentHSI           *widget_hsi_;
    FCSInstrucmentLayout        *widget_layout_;
};

#endif // FCS_INSTRUCMENT_WIDGET_HSI_H
