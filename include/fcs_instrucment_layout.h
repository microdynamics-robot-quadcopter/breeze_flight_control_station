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
 * fcs_instrucment_layout.h
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
 * This .h file defines some elements for implementing the square layout of
 * instrucments according to QFlightInstruments project.
 *****************************************************************************/

#ifndef FCS_INSTRUCMENT_LAYOUT_H
#define FCS_INSTRUCMENT_LAYOUT_H

#include <QLayout>
#include <QLayoutItem>
#include <QPointer>
#include <QRect>
#include <QWidgetItem>

class FCSInstrucmentLayout : public QLayout
{
    Q_OBJECT

public:
    explicit FCSInstrucmentLayout(QWidget *parent, int spacing = -1);
    explicit FCSInstrucmentLayout(int spacing = -1);
    ~FCSInstrucmentLayout();
    void addItem(QLayoutItem *item);
    void addWidget(QWidget *widget);
    void setGeometry(const QRect &rect);
    int count() const;
    bool hasHeightForWidth() const;
    bool hasItem() const;
    QSize minimumSize() const;
    QSize sizeHint() const;
    QRect geometry();
    QLayoutItem* replaceItem(QLayoutItem *item);
    QLayoutItem* itemAt(int index) const;
    QLayoutItem* take();
    QLayoutItem* takeAt(int index);
    Qt::Orientations expandingDirections() const;
private:
    void init(int spacing);
    void setRectLast(const QRect &rect);
    bool areRectEqual(const QRect &rect_1, const QRect &rect_2) const;
    QPoint calculateCenterPoint(QSize form_size, QSize item_size) const;
    QSize  calculateProperSize(QSize form_size) const;
private:
    QRect       *layout_rect_last_;
    QRect       *layout_geometry_;
    QLayoutItem *layout_item_;
};


#endif // FCS_INSTRUCMENT_LAYOUT_H
