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
 * fcs_instrucment_adi.cpp
 *
 * Author:
 * Marek M. Cel<marekcel@marekcel.pl>
 * myyerrol<myyerrol@126.com>
 *
 * History:
 * <Authors>     <Date>         <Version>     <Operation>
 * Marek M. Cel  2013.--.--     --            Finish ADI instrument
 * myyerrol      2018.03.xx     1.0.0         Modify ADI instrument
 *
 * Description:
 * This .cpp file implements the instrument of Attitude Director Indicator(ADI)
 * according to QFlightInstruments project.
 *****************************************************************************/

#include <fcs_instrucment_adi.h>

FCSInstrucmentADI::FCSInstrucmentADI(QWidget *parent) :
    QGraphicsView(parent),
    adi_scene_(0),
    adi_item_back_(0),
    adi_item_face_(0),
    adi_item_ring_(0),
    adi_item_case_(0),
    adi_angle_roll_ (0.0f),
    adi_angle_pitch_(0.0f),
    adi_face_delta_x_new_(0.0f),
    adi_face_delta_x_old_(0.0f),
    adi_face_delta_y_new_(0.0f),
    adi_face_delta_y_old_(0.0f),
    adi_scale_x_(1.0f),
    adi_scale_y_(1.0f),
    adi_original_height_(240),
    adi_original_width_ (240),
    adi_original_pix_per_deg_(1.7f),
    adi_original_adi_ctr_(120.0f, 120.0f),
    adi_back_z_(-30),
    adi_face_z_(-20),
    adi_ring_z_(-10),
    adi_case_z_( 10)
{
    resetADI();

    adi_scene_ = new QGraphicsScene(this);

    setScene(adi_scene_);

    adi_scene_->clear();

    initADI();
}

FCSInstrucmentADI::~FCSInstrucmentADI()
{
    if (adi_scene_) {
        adi_scene_->clear();
        delete adi_scene_;
        adi_scene_ = 0;
    }
    else {
        ;
    }

    resetADI();
}

void FCSInstrucmentADI::reinitADI(void)
{
    if (adi_scene_) {
        adi_scene_->clear();
        initADI();
    }
    else {
        ;
    }
}

void FCSInstrucmentADI::updateADI(void)
{
    updateADIView();

    adi_face_delta_x_old_ = adi_face_delta_x_new_;
    adi_face_delta_y_old_ = adi_face_delta_y_new_;
}

void FCSInstrucmentADI::setADIAngleRoll(float angle_roll)
{
    adi_angle_roll_ = angle_roll;

    if (adi_angle_roll_ < -180.0f) {
        adi_angle_roll_ = -180.0f;
    }
    else if (adi_angle_roll_ > 180.0f) {
        adi_angle_roll_ = 180.0f;;
    }
    else {
        ;
    }
}

void FCSInstrucmentADI::setADIAnglePitch(float angle_pitch)
{
    adi_angle_pitch_ = angle_pitch;

    if (adi_angle_pitch_ < -25.0f) {
        adi_angle_pitch_ = -25.0f;
    }
    else if (adi_angle_pitch_ > 25.0f) {
        adi_angle_pitch_ = 25.0f;
    }
    else {
        ;
    }
}

void FCSInstrucmentADI::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    reinitADI();
}

void FCSInstrucmentADI::initADI(void)
{
    adi_scale_x_ = (float)width()  / (float)adi_original_width_;
    adi_scale_y_ = (float)height() / (float)adi_original_height_;

    resetADI();

    adi_item_back_ = new QGraphicsSvgItem(
        ":/fcs_instrucment/res/fcs_instrucment_adi/adi_back.svg");
    adi_item_back_->setCacheMode(QGraphicsItem::NoCache);
    adi_item_back_->setZValue(adi_back_z_);
    adi_item_back_->setTransform(
        QTransform::fromScale(adi_scale_x_, adi_scale_y_), true);
    adi_item_back_->setTransformOriginPoint(adi_original_adi_ctr_);
    adi_scene_->addItem(adi_item_back_);

    adi_item_face_ = new QGraphicsSvgItem(
        ":/fcs_instrucment/res/fcs_instrucment_adi/adi_face.svg");
    adi_item_face_->setCacheMode(QGraphicsItem::NoCache);
    adi_item_face_->setZValue(adi_face_z_);
    adi_item_face_->setTransform(
        QTransform::fromScale(adi_scale_x_, adi_scale_y_), true);
    adi_item_face_->setTransformOriginPoint(adi_original_adi_ctr_);
    adi_scene_->addItem(adi_item_face_);

    adi_item_ring_ = new QGraphicsSvgItem(
        ":/fcs_instrucment/res/fcs_instrucment_adi/adi_ring.svg");
    adi_item_ring_->setCacheMode(QGraphicsItem::NoCache);
    adi_item_ring_->setZValue(adi_ring_z_);
    adi_item_ring_->setTransform(
        QTransform::fromScale(adi_scale_x_, adi_scale_y_), true);
    adi_item_ring_->setTransformOriginPoint(adi_original_adi_ctr_);
    adi_scene_->addItem(adi_item_ring_);

    adi_item_case_ = new QGraphicsSvgItem(
        ":/fcs_instrucment/res/fcs_instrucment_adi/adi_case.svg");
    adi_item_case_->setCacheMode(QGraphicsItem::NoCache);
    adi_item_case_->setZValue(adi_case_z_);
    adi_item_case_->setTransform(
        QTransform::fromScale(adi_scale_x_, adi_scale_y_), true);
    adi_scene_->addItem(adi_item_case_);

    centerOn(width() / 2.0f, height() / 2.0f);

    updateADIView();
}

void FCSInstrucmentADI::resetADI(void)
{
    adi_item_back_ = 0;
    adi_item_face_ = 0;
    adi_item_ring_ = 0;
    adi_item_case_ = 0;

    adi_angle_roll_  = 0.0f;
    adi_angle_pitch_ = 0.0f;

    adi_face_delta_x_new_ = 0.0f;
    adi_face_delta_x_old_ = 0.0f;
    adi_face_delta_y_new_ = 0.0f;
    adi_face_delta_y_old_ = 0.0f;
}

void FCSInstrucmentADI::updateADIView(void)
{
    adi_scale_x_ = (float)width()  / (float)adi_original_width_;
    adi_scale_y_ = (float)height() / (float)adi_original_height_;

    adi_item_back_->setRotation(-adi_angle_roll_);
    adi_item_face_->setRotation(-adi_angle_roll_);
    adi_item_ring_->setRotation(-adi_angle_roll_);

    float roll_rad = M_PI * adi_angle_roll_ / 180.0f;

    float delta = adi_original_pix_per_deg_ * adi_angle_pitch_;

    adi_face_delta_x_new_ = adi_scale_x_ * delta * sin(roll_rad);
    adi_face_delta_y_new_ = adi_scale_y_ * delta * cos(roll_rad);

    adi_item_face_->moveBy(adi_face_delta_x_new_ - adi_face_delta_x_old_,
                           adi_face_delta_y_new_ - adi_face_delta_y_old_);

    adi_scene_->update();
}
