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
 * fcs_instrucment_layout.cpp
 *
 * Author:
 * Marek M. Cel<marekcel@marekcel.pl>
 * myyerrol<myyerrol@126.com>
 *
 * History:
 * <Authors>     <Date>         <Version>     <Operation>
 * Marek M. Cel  2013.--.--     --            Finish instrucment's layout
 * myyerrol      2018.03.12     1.0           Modify instrucment's layout
 *
 * Description:
 * This .cpp file implements the square layout of instrucments according to
 * QFlightInstruments project.
 *****************************************************************************/

#include <fcs_instrucment_layout.h>

FCSInstrucmentLayout::FCSInstrucmentLayout(QWidget *parent, int spacing) :
    QLayout(parent)
{
    init(spacing);
}

FCSInstrucmentLayout::FCSInstrucmentLayout(int spacing) :
    QLayout(0)
{
    init(spacing);
}

FCSInstrucmentLayout::~FCSInstrucmentLayout()
{
    if (layout_item_) {
        delete layout_item_;
        layout_item_ = 0;
    }
    else {
        ;
    }

    if (layout_rect_last_) {
        delete layout_rect_last_;
        layout_rect_last_ = 0;
    }
    else {
        ;
    }

    if (layout_geometry_) {
        delete layout_geometry_;
        layout_geometry_ = 0;
    }
    else {
        ;
    }
}

void FCSInstrucmentLayout::addItem(QLayoutItem *item)
{
    if (!hasItem()) {
        replaceItem(item);
    }
    else {
        ;
    }
}

void FCSInstrucmentLayout::addWidget(QWidget *widget)
{
    if (!hasItem()) {
        replaceItem(new QWidget(widget));
    }
    else {
        ;
    }
}

void FCSInstrucmentLayout::setGeometry(const QRect &rect)
{
    if (!hasItem() || areRectEqual(*layout_rect_last_, rect)) {
        return;
    }
    else {
        ;
    }

    setRectLast(rect);

    QSize  proper_size  = calculateProperSize(rect.size());
    QPoint center_point = calculateCenterPoint(rect.size(), proper_size);

    layout_item_->setGeometry(QRect(center_point, proper_size));

    QRect *temp_rect = layout_geometry_;

    layout_geometry_ = new QRect(center_point, proper_size);

    delete temp_rect;

    QLayout::setGeometry(*layout_geometry_);
}

int FCSInstrucmentLayout::count() const
{
    if (hasItem()) {
        return 1;
    }
    else {
        return 0;
    }
}

bool FCSInstrucmentLayout::hasHeightForWidth() const
{
    return false;
}

bool FCSInstrucmentLayout::hasItem() const
{
    return (layout_item_ != 0);
}

QSize FCSInstrucmentLayout::minimumSize() const
{
    return layout_item_->minimumSize();
}

QSize FCSInstrucmentLayout::sizeHint() const
{
    return layout_item_->minimumSize();
}

QRect FCSInstrucmentLayout::geometry()
{
    return (QRect)(*layout_geometry_);
}

QLayoutItem* FCSInstrucmentLayout::replaceItem(QLayoutItem *item)
{
    QLayoutItem *temp_item = 0;

    if (hasItem()) {
        temp_item = layout_item_;
    }
    else {
        ;
    }

    layout_item_ = item;

    setGeometry(*layout_geometry_);

    return temp_item;
}

QLayoutItem* FCSInstrucmentLayout::itemAt(int index) const
{
    if (index == 0) {
        if (hasItem()) {
            return layout_item_;
        }
        else {
            ;
        }
    }
    else {
        ;
    }

    return 0;
}

QLayoutItem* FCSInstrucmentLayout::take()
{
    QLayoutItem *temp_item = 0;

    if (hasItem()) {
        temp_item = layout_item_;
        layout_item_ = 0;
    }
    else {
        ;
    }

    return temp_item;
}
