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
 * fcs_instrucment_hsi.cpp
 *
 * Author:
 * Marek M. Cel<marekcel@marekcel.pl>
 * myyerrol<myyerrol@126.com>
 *
 * History:
 * <Authors>     <Date>         <Version>     <Operation>
 * Marek M. Cel  2013.--.--     --            Finish HSI instrument
 * myyerrol      2018.03.xx     1.0.0         Modify HSI instrument
 *
 * Description:
 * This .cpp file implements the instrument of Horizontal Situation
 * Indicator(HSI) according to QFlightInstruments project.
 *****************************************************************************/

#include <fcs_instrucment_hsi.h>

FCSInstrucmentHSI::FCSInstrucmentHSI(QWidget *parent) :
    QGraphicsView(parent),
    hsi_scene_(0),
    hsi_item_face_(0),
    hsi_item_case_(0),
    hsi_heading_(0.0f),
    hsi_scale_x_(1.0f),
    hsi_scale_y_(1.0f),
    hsi_original_height_(240),
    hsi_original_width_ (240),
    hsi_original_hsi_ctr_(120.0f, 120.0f),
    hsi_face_z_(-20),
    hsi_case_z_( 10)
{
    resetHSI();

    hsi_scene_ = new QGraphicsScene(this);

    setScene(hsi_scene_);

    hsi_scene_->clear();

    initHSI();
}

FCSInstrucmentHSI::~FCSInstrucmentHSI()
{
    if (hsi_scene_) {
        hsi_scene_->clear();
        delete hsi_scene_;
        hsi_scene_ = 0;
    }
    else {
        ;
    }

    resetHSI();
}

void FCSInstrucmentHSI::reinitHSI(void)
{
    if (hsi_scene_) {
        hsi_scene_->clear();
        initHSI();
    }
    else {
        ;
    }
}

void FCSInstrucmentHSI::updateHSI(void)
{
    updateHSIView();
}

void FCSInstrucmentHSI::setHSIHeading(float heading)
{
    hsi_heading_ = heading;
}

void FCSInstrucmentHSI::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    reinitHSI();
}

void FCSInstrucmentHSI::initHSI(void)
{
    hsi_scale_x_ = (float)width()  / (float)hsi_original_width_;
    hsi_scale_y_ = (float)height() / (float)hsi_original_height_;

    resetHSI();

    hsi_item_face_ = new QGraphicsSvgItem(
        ":/fcs_instrucment/res/fcs_instrucment_hsi/hsi_face.svg");
    hsi_item_face_->setCacheMode(QGraphicsItem::NoCache);
    hsi_item_face_->setZValue(hsi_face_z_);
    hsi_item_face_->setTransform(
        QTransform::fromScale(hsi_scale_x_, hsi_scale_y_), true);
    hsi_item_face_->setTransformOriginPoint(hsi_original_hsi_ctr_);
    hsi_scene_->addItem(hsi_item_face_);

    hsi_item_case_ = new QGraphicsSvgItem(
        ":/fcs_instrucment/res/fcs_instrucment_hsi/hsi_case.svg");
    hsi_item_case_->setCacheMode(QGraphicsItem::NoCache);
    hsi_item_case_->setZValue(hsi_case_z_);
    hsi_item_case_->setTransform(
        QTransform::fromScale(hsi_scale_x_, hsi_scale_y_), true);
    hsi_scene_->addItem(hsi_item_case_);

    centerOn(width() / 2.0f, height() / 2.0f);

    updateHSIView();
}

void FCSInstrucmentHSI::resetHSI(void)
{
    hsi_item_face_ = 0;
    hsi_item_case_ = 0;

    hsi_heading_ = 0.0f;
}

void FCSInstrucmentHSI::updateHSIView(void)
{
    hsi_item_face_->setRotation(-hsi_heading_);
    hsi_scene_->update();
}
