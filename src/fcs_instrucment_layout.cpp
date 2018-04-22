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
 * myyerrol      2018.03.12     1.0.0         Modify instrucment's layout
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
    }
    else {
        ;
    }

    layout_item_ = 0;

    if (layout_rect_last_) {
        delete layout_rect_last_;
    }
    else {
        ;
    }

    layout_rect_last_ = 0;

    if (layout_geometry_) {
        delete layout_geometry_;
    }
    else {
        ;
    }

    layout_geometry_ = 0;
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
        replaceItem(new QWidgetItem(widget));
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

QLayoutItem* FCSInstrucmentLayout::takeAt(int index)
{
    if (index == 0) {
        return take();
    }
    else {
        return 0;
    }
}

Qt::Orientations FCSInstrucmentLayout::expandingDirections() const
{
    return (Qt::Horizontal | Qt::Vertical);
}

void FCSInstrucmentLayout::init(int spacing)
{
    layout_item_ = 0;

    layout_rect_last_ = new QRect(0, 0, 0, 0);
    layout_geometry_  = new QRect(0, 0, 0, 0);

    setSpacing(spacing);
}

void FCSInstrucmentLayout::setRectLast(const QRect &rect)
{
    QRect *temp_rect = layout_rect_last_;

    layout_rect_last_ = new QRect(rect.topLeft(), rect.size());

    delete temp_rect;
}

bool FCSInstrucmentLayout::areRectEqual(const QRect &rect_1,
                                        const QRect &rect_2) const
{
    bool result = false;

    if ((rect_1.x()      == rect_2.x())      &&
        (rect_1.y()      == rect_2.y())      &&
        (rect_1.height() == rect_2.height()) &&
        (rect_1.width()  == rect_2.width())) {
        result = true;
    }
    else {
        ;
    }

     return result;
}

QPoint FCSInstrucmentLayout::calculateCenterPoint(QSize form_size,
                                                  QSize item_size) const
{
    QPoint center_point;

    int temp_width  = form_size.width()  - form_size.width()  / 2.0 -
        item_size.width()  / 2.0;
    int temp_height = form_size.height() - form_size.height() / 2.0 -
        item_size.height() / 2.0;

    if (temp_width > 0.0) {
        center_point.setX(temp_width);
    }
    else {
        ;
    }

    if (temp_height > 0.0) {
        center_point.setY(temp_height);
    }
    else {
        ;
    }

    return center_point;
}

QSize FCSInstrucmentLayout::calculateProperSize(QSize form_size) const
{
    QSize result_size;

    if (form_size.height() < form_size.width()) {
        result_size.setHeight(form_size.height() - margin());
        result_size.setWidth( form_size.height() - margin());
    }
    else {
        result_size.setHeight(form_size.width() - margin());
        result_size.setWidth( form_size.width() - margin());
    }

    return result_size;
}
