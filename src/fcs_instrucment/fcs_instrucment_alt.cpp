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
 * fcs_instrucment_alt.cpp
 *
 * Author:
 * Marek M. Cel<marekcel@marekcel.pl>
 * myyerrol<myyerrol@126.com>
 *
 * History:
 * <Authors>     <Date>         <Version>     <Operation>
 * Marek M. Cel  2013.--.--     --            Finish ALT instrument
 * myyerrol      2018.03.xx     1.0           Modify ALT instrument
 *
 * Description:
 * This .cpp file implements the instrument of Altimeter(ALT) according to
 * QFlightInstruments project.
 *****************************************************************************/

#include <fcs_instrucment_alt.h>

FCSInstrucmentALT::FCSInstrucmentALT(QWidget *parent) :
    QGraphicsView(parent),
    alt_scene_(0),
    alt_item_face_1_(0),
    alt_item_face_2_(0),
    alt_item_face_3_(0),
    alt_item_hand_1_(0),
    alt_item_hand_2_(0),
    alt_item_case_  (0),
    alt_altitude_( 0.0f),
    alt_pressure_(28.0f),
    alt_scale_x_(1.0f),
    alt_scale_y_(1.0f),
    alt_original_height_(240),
    alt_original_width_ (240),
    alt_original_alt_ctr_(120.0f, 120.0f),
    alt_face_1_z_(-50),
    alt_face_2_z_(-40),
    alt_face_3_z_(-30),
    alt_hand_1_z_(-20),
    alt_hand_2_z_(-10),
    alt_case_z_  ( 10)
{
    resetALT();

    alt_scene_ = new QGraphicsScene(this);

    setScene(alt_scene_);

    alt_scene_->clear();

    initALT();
}

FCSInstrucmentALT::~FCSInstrucmentALT()
{
    if (alt_scene_) {
        alt_scene_->clear();
        delete alt_scene_;
        alt_scene_ = 0;
    }
    else {
        ;
    }

    resetALT();
}

void FCSInstrucmentALT::reinitALT(void)
{
    if (alt_scene_) {
        alt_scene_->clear();
        initALT();
    }
    else {
        ;
    }
}

void FCSInstrucmentALT::updateALT(void)
{
    updateALTView();
}

void FCSInstrucmentALT::setALTAltitude(float altitude)
{
    alt_altitude_ = altitude;
}

void FCSInstrucmentALT::setALTPressure(float pressure)
{
    alt_pressure_ = pressure;

    if (alt_pressure_ < 28.0f) {
        alt_pressure_ = 28.0f;
    }
    else if (alt_pressure_ > 31.5f) {
        alt_pressure_ = 31.5f;
    }
    else {
        ;
    }
}

void FCSInstrucmentALT::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    reinitALT();
}

void FCSInstrucmentALT::initALT(void)
{
    alt_scale_x_ = (float)width()  / (float)alt_original_width_;
    alt_scale_y_ = (float)height() / (float)alt_original_height_;

    resetALT();

    alt_item_face_1_ = new QGraphicsSvgItem(
        ":/fcs_instrucment/res/fcs_instrucment_alt/alt_face_1.svg");
    alt_item_face_1_->setCacheMode(QGraphicsItem::NoCache);
    alt_item_face_1_->setZValue(alt_face_1_z_);
    alt_item_face_1_->setTransform(
        QTransform::fromScale(alt_scale_x_, alt_scale_y_), true);
    alt_item_face_1_->setTransformOriginPoint(alt_original_alt_ctr_);
    alt_scene_->addItem(alt_item_face_1_);

    alt_item_face_2_ = new QGraphicsSvgItem(
        ":/fcs_instrucment/res/fcs_instrucment_alt/alt_face_2.svg");
    alt_item_face_2_->setCacheMode(QGraphicsItem::NoCache);
    alt_item_face_2_->setZValue(alt_face_2_z_);
    alt_item_face_2_->setTransform(
        QTransform::fromScale(alt_scale_x_, alt_scale_y_), true);
    alt_scene_->addItem(alt_item_face_2_);

    alt_item_face_3_ = new QGraphicsSvgItem(
        ":/fcs_instrucment/res/fcs_instrucment_alt/alt_face_3.svg");
    alt_item_face_3_->setCacheMode(QGraphicsItem::NoCache);
    alt_item_face_3_->setZValue(alt_face_3_z_);
    alt_item_face_3_->setTransform(
        QTransform::fromScale(alt_scale_x_, alt_scale_y_), true);
    alt_item_face_3_->setTransformOriginPoint(alt_original_alt_ctr_);
    alt_scene_->addItem(alt_item_face_3_);

    alt_item_hand_1_ = new QGraphicsSvgItem(
        ":/fcs_instrucment/res/fcs_instrucment_alt/alt_hand_1.svg");
    alt_item_hand_1_->setCacheMode(QGraphicsItem::NoCache);
    alt_item_hand_1_->setZValue(alt_hand_1_z_);
    alt_item_hand_1_->setTransform(
        QTransform::fromScale(alt_scale_x_, alt_scale_y_), true);
    alt_item_hand_1_->setTransformOriginPoint(alt_original_alt_ctr_);
    alt_scene_->addItem(alt_item_hand_1_);

    alt_item_hand_2_ = new QGraphicsSvgItem(
        ":/fcs_instrucment/res/fcs_instrucment_alt/alt_hand_2.svg");
    alt_item_hand_2_->setCacheMode(QGraphicsItem::NoCache);
    alt_item_hand_2_->setZValue(alt_hand_2_z_);
    alt_item_hand_2_->setTransform(
        QTransform::fromScale(alt_scale_x_, alt_scale_y_), true);
    alt_item_hand_2_->setTransformOriginPoint(alt_original_alt_ctr_);
    alt_scene_->addItem(alt_item_hand_2_);

    alt_item_case_ = new QGraphicsSvgItem(
        ":/fcs_instrucment/res/fcs_instrucment_alt/alt_case.svg");
    alt_item_case_->setCacheMode(QGraphicsItem::NoCache);
    alt_item_case_->setZValue(alt_case_z_);
    alt_item_case_->setTransform(
        QTransform::fromScale(alt_scale_x_, alt_scale_y_), true);
    alt_scene_->addItem(alt_item_case_);

    centerOn(width() / 2.0f, height() / 2.0f);

    updateALTView();
}

void FCSInstrucmentALT::resetALT(void)
{
    alt_item_face_1_ = 0;
    alt_item_face_2_ = 0;
    alt_item_face_3_ = 0;
    alt_item_hand_1_ = 0;
    alt_item_hand_2_ = 0;
    alt_item_case_   = 0;

    alt_altitude_ =  0.0f;
    alt_pressure_ = 28.0f;
}

void FCSInstrucmentALT::updateALTView(void)
{
    int altitude = ceil(alt_altitude_ + 0.5);

    float angle_hand_1 = alt_altitude_ * 0.036f;
    float angle_hand_2 = (altitude % 1000) * 0.36f;
    float angle_face_1 = (alt_pressure_ - 28.0f) * 100.0f;
    float angle_face_3 = alt_altitude_ * 0.0036f;

    alt_item_hand_1_->setRotation( angle_hand_1);
    alt_item_hand_2_->setRotation( angle_hand_2);
    alt_item_face_1_->setRotation(-angle_face_1);
    alt_item_face_3_->setRotation( angle_face_3);

    alt_scene_->update();
}

