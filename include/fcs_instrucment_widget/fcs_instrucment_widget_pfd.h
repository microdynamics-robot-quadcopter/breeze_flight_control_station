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
 * fcs_instrucment_widget_pfd.h
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
 * This .h file defines some elements for implementing the widget of Primary
 * Flight Display(PFD) according to QFlightInstruments project.
 *****************************************************************************/

#ifndef FCS_INSTRUCMENT_WIDGET_PFD_H
#define FCS_INSTRUCMENT_WIDGET_PFD_H

#include <QWidget>
#include <fcs_instrucment_pfd.h>
#include <fcs_instrucment_layout.h>

namespace Ui {
class FCSInstrucmentWidgetPFD;
}

class FCSInstrucmentWidgetPFD : public QWidget
{
    Q_OBJECT

public:
    explicit FCSInstrucmentWidgetPFD(QWidget *parent = 0);
    ~FCSInstrucmentWidgetPFD();
    inline void updatePFD(void)
    {
        widget_pfd_->updatePFD();
    }
    inline void setPFDAngleRoll(float angle_roll)
    {
        widget_pfd_->setPFDAngleRoll(angle_roll);
    }
    inline void setPFDAnglePitch(float angle_pitch)
    {
        widget_pfd_->setPFDAnglePitch(angle_pitch);
    }
    inline void setPFDFlightPathMarker(float angle_attack,
                                       float angle_sideslip)
    {
        widget_pfd_->setPFDFlightPathMarker(angle_attack, angle_sideslip);
    }
    inline void setPFDSlipSkid(float slip_skid)
    {
        widget_pfd_->setPFDSlipSkid(slip_skid);
    }
    inline void setPFDDeviatePositionH(float dev_h)
    {
        widget_pfd_->setPFDDeviateBarPositionH(dev_h);
        widget_pfd_->setPFDDeviateDotPositionH(dev_h);
    }
    inline void setPFDDeviatePositionV(float dev_v)
    {
        widget_pfd_->setPFDDeviateBarPositionV(dev_v);
        widget_pfd_->setPFDDeviateDotPositionV(dev_v);
    }
    inline void setPFDAltitude(float altitude)
    {
        widget_pfd_->setPFDAltitude(altitude);
    }
    inline void setPFDPressure(float pressure)
    {
        widget_pfd_->setPFDPressure(pressure, FCSInstrucmentPFD::IN);
    }
    inline void setPFDAirspeed(float airspeed)
    {
        widget_pfd_->setPFDAirspeed(airspeed);
    }
    inline void setPFDMachNumber(float mach_number)
    {
        widget_pfd_->setPFDMachNumber(mach_number);
    }
    inline void setPFDHeading(float heading)
    {
        widget_pfd_->setPFDHeading(heading);
    }
    inline void setPFDTurnRate(float turn_rate)
    {
        widget_pfd_->setPFDTurnRate(turn_rate);
    }
    inline void setPFDClimbRate(float climb_rate)
    {
        widget_pfd_->setPFDClimbRate(climb_rate);
    }
private:
    void setupWidgetUi(void);
private:
    Ui::FCSInstrucmentWidgetPFD *widget_ui_;
    FCSInstrucmentPFD           *widget_pfd_;
    FCSInstrucmentLayout        *widget_layout_;
};

#endif // FCS_INSTRUCMENT_WIDGET_PFD_H
