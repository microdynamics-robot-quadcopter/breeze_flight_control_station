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
 * fcs_instrucment_pfd.cpp
 *
 * Author:
 * Marek M. Cel<marekcel@marekcel.pl>
 * myyerrol<myyerrol@126.com>
 *
 * History:
 * <Authors>     <Date>         <Version>     <Operation>
 * Marek M. Cel  2013.--.--     --            Finish PFD instrument
 * myyerrol      2018.03.xx     1.0           Modify PFD instrument
 *
 * Description:
 * This .cpp file implements the instrument of Primary Flight Display(PFD)
 * according to QFlightInstruments project.
 *****************************************************************************/

#include <fcs_instrucment_pfd.h>

FCSInstrucmentPFD::FCSInstrucmentPFD(QWidget *parent) : QGraphicsView(parent),
    pfd_scene_(0),
    pfd_panel_adi_(0),
    pfd_panel_alt_(0),
    pfd_panel_asi_(0),
    pfd_panel_hsi_(0),
    pfd_panel_vsi_(0),
    pfd_item_back_(0),
    pfd_item_mask_(0),
    pfd_scale_x_(1.0f),
    pfd_scale_y_(1.0f),
    pfd_original_height_(300),
    pfd_original_width_(300),
    pfd_back_z_(0),
    pfd_mask_z_(100)
{
    resetPFD();

    pfd_scene_ = new QGraphicsScene(this);
    setScene(pfd_scene_);

    pfd_scene_->clear();

    pfd_panel_adi_ = new PanelADI(pfd_scene_);
    pfd_panel_alt_ = new PanelALT(pfd_scene_);
    pfd_panel_asi_ = new PanelASI(pfd_scene_);
    pfd_panel_hsi_ = new PanelHSI(pfd_scene_);
    pfd_panel_vsi_ = new PanelVSI(pfd_scene_);

    initPFD();
}

FCSInstrucmentPFD::~FCSInstrucmentPFD()
{
    if (pfd_scene_) {
        pfd_scene_->clear();
        delete pfd_scene_;
        pfd_scene_ = 0;
    }

    resetPFD();

    if (pfd_panel_adi_) {
        delete pfd_panel_adi_;
        pfd_panel_adi_ = 0;
    }
    if (pfd_panel_alt_) {
        delete pfd_panel_alt_;
        pfd_panel_alt_ = 0;
    }
    if (pfd_panel_asi_) {
        delete pfd_panel_asi_;
        pfd_panel_asi_ = 0;
    }
    if (pfd_panel_hsi_) {
        delete pfd_panel_hsi_;
        pfd_panel_hsi_ = 0;
    }
    if (pfd_panel_vsi_) {
        delete pfd_panel_vsi_;
        pfd_panel_vsi_ = 0;
    }
}

void FCSInstrucmentPFD::reinitPFD(void)
{
    if (pfd_scene_) {
        pfd_scene_->clear();
        initPFD();
    }
}

void FCSInstrucmentPFD::updatePFD(void)
{
    updatePFDView();
}

void FCSInstrucmentPFD::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    reinitPFD();
}

void FCSInstrucmentPFD::initPFD(void)
{
    pfd_scale_x_ = (float)width()  / (float)pfd_original_width_;
    pfd_scale_y_ = (float)height() / (float)pfd_original_height_;

    pfd_panel_adi_->initADI(pfd_scale_x_, pfd_scale_y_);
    pfd_panel_alt_->initALT(pfd_scale_x_, pfd_scale_y_);
    pfd_panel_asi_->initASI(pfd_scale_x_, pfd_scale_y_);
    pfd_panel_hsi_->initHSI(pfd_scale_x_, pfd_scale_y_);
    pfd_panel_vsi_->initVSI(pfd_scale_x_, pfd_scale_y_);

    pfd_item_back_ = new QGraphicsSvgItem(
        ":/fcs_instrucment/res/fcs_instrucment_pfd/pfd_back.svg");
    pfd_item_back_->setCacheMode(QGraphicsItem::NoCache);
    pfd_item_back_->setZValue(pfd_back_z_);
    pfd_item_back_->setTransform(
        QTransform::fromScale(pfd_scale_x_, pfd_scale_y_), true);
    pfd_scene_->addItem(pfd_item_back_);

    pfd_item_mask_ = new QGraphicsSvgItem(
        ":/fcs_instrucment/res/fcs_instrucment_pfd/pfd_mask.svg");
    pfd_item_mask_->setCacheMode(QGraphicsItem::NoCache);
    pfd_item_mask_->setZValue(pfd_mask_z_);
    pfd_item_mask_->setTransform(
        QTransform::fromScale(pfd_scale_x_, pfd_scale_y_), true);
    pfd_scene_->addItem(pfd_item_mask_);

    centerOn(width() / 2.0f, height() / 2.0f);

    updatePFDView();
}

void FCSInstrucmentPFD::resetPFD(void)
{
    pfd_item_back_ = 0;
    pfd_item_mask_ = 0;
}

void FCSInstrucmentPFD::updatePFDView(void)
{
    pfd_scale_x_ = (float)width()  / (float)pfd_original_width_;
    pfd_scale_y_ = (float)height() / (float)pfd_original_height_;

    pfd_panel_adi_->updateADI(pfd_scale_x_, pfd_scale_y_);
    pfd_panel_alt_->updateALT(pfd_scale_x_, pfd_scale_y_);
    pfd_panel_asi_->updateASI(pfd_scale_x_, pfd_scale_y_);
    pfd_panel_hsi_->updateHSI(pfd_scale_x_, pfd_scale_y_);
    pfd_panel_vsi_->updateVSI(pfd_scale_x_, pfd_scale_y_);

    pfd_scene_->update();
}

/*****************************************************************************/

FCSInstrucmentPFD::PanelADI::PanelADI(QGraphicsScene *scene) :
    adi_scene_(scene),
    adi_item_back_   (0),
    adi_item_ladd_   (0),
    adi_item_roll_   (0),
    adi_item_slip_   (0),
    adi_item_turn_   (0),
    adi_item_path_   (0),
    adi_item_mark_   (0),
    adi_item_bar_h_  (0),
    adi_item_bar_v_  (0),
    adi_item_dot_h_  (0),
    adi_item_dot_v_  (0),
    adi_item_mask_   (0),
    adi_item_scale_h_(0),
    adi_item_scale_v_(0),
    adi_angle_roll_    (0.0f),
    adi_angle_pitch_   (0.0f),
    adi_angle_attack_  (0.0f),
    adi_angle_sideslip_(0.0f),
    adi_slip_skid_     (0.0f),
    adi_turn_rate_     (0.0f),
    adi_bar_h_         (0.0f),
    adi_bar_v_         (0.0f),
    adi_dot_h_         (0.0f),
    adi_dot_v_         (0.0f),
    adi_path_valid_   (true),
    adi_path_visible_ (true),
    adi_bar_h_visible_(true),
    adi_bar_v_visible_(true),
    adi_dot_h_visible_(true),
    adi_dot_v_visible_(true),
    adi_ladd_delta_x_new_     (0.0f),
    adi_ladd_delta_x_old_     (0.0f),
    adi_ladd_back_delta_x_new_(0.0f),
    adi_ladd_back_delta_x_old_(0.0f),
    adi_ladd_back_delta_y_new_(0.0f),
    adi_ladd_back_delta_y_old_(0.0f),
    adi_ladd_delta_y_new_     (0.0f),
    adi_ladd_delta_y_old_     (0.0f),
    adi_slip_delta_x_new_     (0.0f),
    adi_slip_delta_x_old_     (0.0f),
    adi_slip_delta_y_new_     (0.0f),
    adi_slip_delta_y_old_     (0.0f),
    adi_turn_delta_x_new_     (0.0f),
    adi_turn_delta_x_old_     (0.0f),
    adi_path_delta_x_new_     (0.0f),
    adi_path_delta_x_old_     (0.0f),
    adi_path_delta_y_new_     (0.0f),
    adi_path_delta_y_old_     (0.0f),
    adi_mark_delta_x_new_     (0.0f),
    adi_mark_delta_x_old_     (0.0f),
    adi_mark_delta_y_new_     (0.0f),
    adi_mark_delta_y_old_     (0.0f),
    adi_bar_h_delta_x_new_    (0.0f),
    adi_bar_h_delta_x_old_    (0.0f),
    adi_bar_v_delta_y_new_    (0.0f),
    adi_bar_v_delta_y_old_    (0.0f),
    adi_dot_h_delta_x_new_    (0.0f),
    adi_dot_h_delta_x_old_    (0.0f),
    adi_dot_v_delta_y_new_    (0.0f),
    adi_dot_v_delta_y_old_    (0.0f),
    adi_scale_x_(1.0f),
    adi_scale_y_(1.0f),
    adi_original_pix_per_deg_(  3.0f),
    adi_delta_ladd_back_max_ ( 52.5f),
    adi_delta_ladd_back_min_ (-52.5f),
    adi_max_slip_deflection_ ( 20.0f),
    adi_max_turn_deflection_ ( 55.0f),
    adi_max_bars_deflection_ ( 40.0f),
    adi_max_dots_deflection_ ( 50.0f),
    adi_original_adi_ctr_    (150.0f,  125.0f),
    adi_original_back_pos_   ( 45.0f,  -85.0f),
    adi_original_ladd_pos_   ( 110.f, -175.0f),
    adi_original_roll_pos_   ( 45.0f,   20.0f),
    adi_original_slip_pos_   (145.5f,   68.5f),
    adi_original_turn_pos_   (142.5f,  206.0f),
    adi_original_path_pos_   (135.0f,  113.0f),
    adi_original_bar_h_pos_  (149.0f,   85.0f),
    adi_original_bar_v_pos_  (110.0f,  124.0f),
    adi_original_dot_h_pos_  (145.0f,  188.0f),
    adi_original_dot_v_pos_  (213.0f,  120.0f),
    adi_original_scale_h_pos_(  0.0f,    0.0f),
    adi_original_scale_v_pos_(  0.0f,    0.0f),
    adi_back_z_  (10),
    adi_ladd_z_  (20),
    adi_roll_z_  (30),
    adi_slip_z_  (40),
    adi_path_z_  (40),
    adi_bars_z_  (50),
    adi_dots_z_  (50),
    adi_scales_z_(51),
    adi_mask_z_  (60),
    adi_turn_z_  (70)
{
    resetADI();
}

void FCSInstrucmentPFD::PanelADI::initADI(float scale_x, float scale_y)
{
    adi_scale_x_ = scale_x;
    adi_scale_y_ = scale_y;

    resetADI();

    adi_item_back_ = new QGraphicsSvgItem(
        ":/fcs_instrucment/res/fcs_instrucment_pfd/pfd_adi_back.svg");
    adi_item_back_->setCacheMode(QGraphicsItem::NoCache);
    adi_item_back_->setZValue(adi_back_z_);
    adi_item_back_->setTransform(
        QTransform::fromScale(adi_scale_x_, adi_scale_y_), true);
    adi_item_back_->setTransformOriginPoint(
        adi_original_adi_ctr_ - adi_original_back_pos_);
    adi_item_back_->moveBy(adi_scale_x_ * adi_original_back_pos_.x(),
                           adi_scale_y_ * adi_original_back_pos_.y());
    adi_scene_->addItem(adi_item_back_);

    adi_item_ladd_ = new QGraphicsSvgItem(
        ":/fcs_instrucment/res/fcs_instrucment_pfd/pfd_adi_ladd.svg");
    adi_item_ladd_->setCacheMode(QGraphicsItem::NoCache);
    adi_item_ladd_->setZValue(adi_ladd_z_);
    adi_item_ladd_->setTransform(
        QTransform::fromScale(adi_scale_x_, adi_scale_y_), true);
    adi_item_ladd_->setTransformOriginPoint(
        adi_original_adi_ctr_ - adi_original_ladd_pos_);
    adi_item_ladd_->moveBy(adi_scale_x_ * adi_original_ladd_pos_.x(),
                           adi_scale_y_ * adi_original_ladd_pos_.y());
    adi_scene_->addItem(adi_item_ladd_);

    adi_item_roll_ = new QGraphicsSvgItem(
        ":/fcs_instrucment/res/fcs_instrucment_pfd/pfd_adi_roll.svg");
    adi_item_roll_->setCacheMode(QGraphicsItem::NoCache);
    adi_item_roll_->setZValue(adi_roll_z_);
    adi_item_roll_->setTransform(
        QTransform::fromScale(adi_scale_x_, adi_scale_y_), true);
    adi_item_roll_->setTransformOriginPoint(
        adi_original_adi_ctr_ - adi_original_roll_pos_);
    adi_item_roll_->moveBy(adi_scale_x_ * adi_original_roll_pos_.x(),
                           adi_scale_y_ * adi_original_roll_pos_.y());
    adi_scene_->addItem(adi_item_roll_);

    adi_item_slip_ = new QGraphicsSvgItem(
        ":/fcs_instrucment/res/fcs_instrucment_pfd/pfd_adi_slip.svg");
    adi_item_slip_->setCacheMode(QGraphicsItem::NoCache);
    adi_item_slip_->setZValue(adi_slip_z_);
    adi_item_slip_->setTransform(
        QTransform::fromScale(adi_scale_x_, adi_scale_y_), true);
    adi_item_slip_->setTransformOriginPoint(
        adi_original_adi_ctr_ - adi_original_slip_pos_);
    adi_item_slip_->moveBy(adi_scale_x_ * adi_original_slip_pos_.x(),
                           adi_scale_y_ * adi_original_slip_pos_.y());
    adi_scene_->addItem(adi_item_slip_);

    adi_item_turn_ = new QGraphicsSvgItem(
        ":/fcs_instrucment/res/fcs_instrucment_pfd/pfd_adi_turn.svg");
    adi_item_turn_->setCacheMode(QGraphicsItem::NoCache);
    adi_item_turn_->setZValue(adi_turn_z_);
    adi_item_turn_->setTransform(
        QTransform::fromScale(adi_scale_x_, adi_scale_y_), true);
    adi_item_turn_->moveBy(adi_scale_x_ * adi_original_turn_pos_.x(),
                           adi_scale_y_ * adi_original_turn_pos_.y());
    adi_scene_->addItem(adi_item_turn_);

    adi_item_path_ = new QGraphicsSvgItem(
        ":/fcs_instrucment/res/fcs_instrucment_pfd/pfd_adi_path.svg");
    adi_item_path_->setCacheMode(QGraphicsItem::NoCache);
    adi_item_path_->setZValue(adi_path_z_);
    adi_item_path_->setTransform(
        QTransform::fromScale(adi_scale_x_, adi_scale_y_), true);
    adi_item_path_->moveBy(adi_scale_x_ * adi_original_path_pos_.x(),
                           adi_scale_y_ * adi_original_path_pos_.y());
    adi_scene_->addItem(adi_item_path_);

    adi_item_mark_ = new QGraphicsSvgItem(
        ":/fcs_instrucment/res/fcs_instrucment_pfd/pfd_adi_mark.svg");
    adi_item_mark_->setCacheMode(QGraphicsItem::NoCache);
    adi_item_mark_->setZValue(adi_path_z_);
    adi_item_mark_->setTransform(
        QTransform::fromScale(adi_scale_x_, adi_scale_y_), true);
    adi_item_mark_->moveBy(adi_scale_x_ * adi_original_path_pos_.x(),
                           adi_scale_y_ * adi_original_path_pos_.y());
    adi_scene_->addItem(adi_item_mark_);

    adi_item_bar_h_ = new QGraphicsSvgItem(
        ":/fcs_instrucment/res/fcs_instrucment_pfd/pfd_adi_bar_h.svg");
    adi_item_bar_h_->setCacheMode(QGraphicsItem::NoCache);
    adi_item_bar_h_->setZValue(adi_bars_z_);
    adi_item_bar_h_->setTransform(
        QTransform::fromScale(adi_scale_x_, adi_scale_y_), true);
    adi_item_bar_h_->moveBy(adi_scale_x_ * adi_original_bar_h_pos_.x(),
                            adi_scale_y_ * adi_original_bar_h_pos_.y());
    adi_scene_->addItem(adi_item_bar_h_);

    adi_item_bar_v_ = new QGraphicsSvgItem(
        ":/fcs_instrucment/res/fcs_instrucment_pfd/pfd_adi_bar_v.svg");
    adi_item_bar_v_->setCacheMode(QGraphicsItem::NoCache);
    adi_item_bar_v_->setZValue(adi_bars_z_);
    adi_item_bar_v_->setTransform(
        QTransform::fromScale(adi_scale_x_, adi_scale_y_), true);
    adi_item_bar_v_->moveBy(adi_scale_x_ * adi_original_bar_v_pos_.x(),
                            adi_scale_y_ * adi_original_bar_v_pos_.y());
    adi_scene_->addItem(adi_item_bar_v_);

    adi_item_dot_h_ = new QGraphicsSvgItem(
        ":/fcs_instrucment/res/fcs_instrucment_pfd/pfd_adi_dot_h.svg");
    adi_item_dot_h_->setCacheMode(QGraphicsItem::NoCache);
    adi_item_dot_h_->setZValue(adi_dots_z_);
    adi_item_dot_h_->setTransform(
        QTransform::fromScale(adi_scale_x_, adi_scale_y_), true);
    adi_item_dot_h_->moveBy(adi_scale_x_ * adi_original_dot_h_pos_.x(),
                            adi_scale_y_ * adi_original_dot_h_pos_.y());
    adi_scene_->addItem(adi_item_dot_h_);

    adi_item_dot_v_ = new QGraphicsSvgItem(
        ":/fcs_instrucment/res/fcs_instrucment_pfd/pfd_adi_dot_v.svg");
    adi_item_dot_v_->setCacheMode(QGraphicsItem::NoCache);
    adi_item_dot_v_->setZValue(adi_dots_z_);
    adi_item_dot_v_->setTransform(
        QTransform::fromScale(adi_scale_x_, adi_scale_y_), true);
    adi_item_dot_v_->moveBy(adi_scale_x_ * adi_original_dot_v_pos_.x(),
                            adi_scale_y_ * adi_original_dot_v_pos_.y());
    adi_scene_->addItem(adi_item_dot_v_);

    adi_item_scale_h_ = new QGraphicsSvgItem(
        ":/fcs_instrucment/res/fcs_instrucment_pfd/pfd_adi_scale_h.svg");
    adi_item_scale_h_->setCacheMode(QGraphicsItem::NoCache);
    adi_item_scale_h_->setZValue(adi_scales_z_);
    adi_item_scale_h_->setTransform(
        QTransform::fromScale(adi_scale_x_, adi_scale_y_), true);
    adi_item_scale_h_->moveBy(adi_scale_x_ * adi_original_scale_h_pos_.x(),
                              adi_scale_y_ * adi_original_scale_h_pos_.y());
    adi_scene_->addItem(adi_item_scale_h_);

    adi_item_scale_v_ = new QGraphicsSvgItem(
        ":/fcs_instrucment/res/fcs_instrucment_pfd/pfd_adi_scale_v.svg");
    adi_item_scale_v_->setCacheMode(QGraphicsItem::NoCache);
    adi_item_scale_v_->setZValue(adi_scales_z_);
    adi_item_scale_v_->setTransform(
        QTransform::fromScale(adi_scale_x_, adi_scale_y_), true);
    adi_item_scale_v_->moveBy(adi_scale_x_ * adi_original_scale_v_pos_.x(),
                              adi_scale_y_ * adi_original_scale_v_pos_.y());
    adi_scene_->addItem(adi_item_scale_v_);

    adi_item_mask_ = new QGraphicsSvgItem(
        ":/fcs_instrucment/res/fcs_instrucment_pfd/pfd_adi_mask.svg");
    adi_item_mask_->setCacheMode(QGraphicsItem::NoCache);
    adi_item_mask_->setZValue(adi_mask_z_);
    adi_item_mask_->setTransform(
        QTransform::fromScale(adi_scale_x_, adi_scale_y_), true);
    adi_scene_->addItem(adi_item_mask_);

    updateADI(scale_x, scale_y);
}

void FCSInstrucmentPFD::PanelADI::updateADI(float scale_x, float scale_y)
{
    adi_scale_x_ = scale_x;
    adi_scale_y_ = scale_y;

    float delta    = adi_original_pix_per_deg_ * adi_angle_pitch_;
    float roll_rad = M_PI * adi_angle_roll_ / 180.0f;

    float roll_sin = sin(roll_rad);
    float roll_cos = cos(roll_rad);

    updateADILadd(delta, roll_sin, roll_cos);
    updateADILaddBack(delta, roll_sin, roll_cos);
    updateADIAngleRoll();
    updateADiSlipSkip(roll_sin, roll_cos);
    updateADITurnRate();
    updateADIBars();
    updateADIDots();
    updateADIFlightPath();

    adi_ladd_delta_x_old_      = adi_ladd_delta_x_new_;
    adi_ladd_delta_y_old_      = adi_ladd_delta_y_new_;
    adi_ladd_back_delta_x_old_ = adi_ladd_back_delta_x_new_;
    adi_ladd_back_delta_y_old_ = adi_ladd_back_delta_y_new_;
    adi_slip_delta_x_old_      = adi_slip_delta_x_new_;
    adi_slip_delta_y_old_      = adi_slip_delta_y_new_;
    adi_turn_delta_x_old_      = adi_turn_delta_x_new_;
    adi_path_delta_x_old_      = adi_path_delta_x_new_;
    adi_path_delta_y_old_      = adi_path_delta_y_new_;
    adi_mark_delta_x_old_      = adi_mark_delta_x_new_;
    adi_mark_delta_y_old_      = adi_mark_delta_y_new_;
    adi_bar_h_delta_x_old_     = adi_bar_h_delta_x_new_;
    adi_bar_v_delta_y_old_     = adi_bar_v_delta_y_new_;
    adi_dot_h_delta_x_old_     = adi_dot_h_delta_x_new_;
    adi_dot_v_delta_y_old_     = adi_dot_v_delta_y_new_;
}

void FCSInstrucmentPFD::PanelADI::setADIAngleRoll(float angle_roll)
{
    adi_angle_roll_ = angle_roll;

    if (adi_angle_roll_ < -180.0f) {
        adi_angle_roll_ = -180.0f;
    }
    else if (adi_angle_roll_ > 180.0f) {
        adi_angle_roll_ = 180.0f;
    }
    else {
        ;
    }
}

void FCSInstrucmentPFD::PanelADI::setADIAnglePitch(float angle_pitch)
{
    adi_angle_pitch_ = angle_pitch;

    if (adi_angle_pitch_ < -90.0f) {
        adi_angle_pitch_ = -90.0f;
    }
    else if (adi_angle_pitch_ > 90.0f) {
        adi_angle_pitch_ = 90.0f;
    }
    else {
        ;
    }
}

void FCSInstrucmentPFD::PanelADI::setADIFlightPathMarker(float angle_attack,
                                                         float angle_sideslip,
                                                         bool  visible)
{
    adi_angle_attack_   = angle_attack;
    adi_angle_sideslip_ = angle_sideslip;

    adi_path_valid_ = true;

    if (adi_angle_attack_ < -15.0f) {
        adi_angle_attack_ = -15.0f;
        adi_path_valid_ = false;
    }
    else if (adi_angle_attack_ > 15.0f) {
        adi_angle_attack_ = 15.0f;
        adi_path_valid_ = false;
    }
    else {
        ;
    }

    if (adi_angle_sideslip_ < -10.0f) {
        adi_angle_sideslip_ = -10.0f;
        adi_path_valid_ = false;
    }
    else if (adi_angle_sideslip_ > 10.0f) {
        adi_angle_sideslip_ = 10.0f;
        adi_path_valid_ = false;
    }
    else {
        ;
    }

    adi_path_visible_ = visible;
}

void FCSInstrucmentPFD::PanelADI::setADISlipSkid(float slip_skid)
{
    adi_slip_skid_ = slip_skid;

    if (adi_slip_skid_ < -1.0f) {
        adi_slip_skid_ = -1.0f;
    }
    else if (adi_slip_skid_ > 1.0f) {
        adi_slip_skid_ = 1.0f;
    }
    else {
        ;
    }
}

void FCSInstrucmentPFD::PanelADI::setADITurnRate(float turn_rate)
{
    adi_turn_rate_ = turn_rate;

    if (adi_turn_rate_ < -1.0f) {
        adi_turn_rate_ = -1.0f;
    }
    else if (adi_turn_rate_ > 1.0f) {
        adi_turn_rate_ = 1.0f;
    }
    else {
        ;
    }
}

void FCSInstrucmentPFD::PanelADI::setADIDeviateBarPositionH(float bar_h,
                                                            bool  visible)
{
    adi_bar_h_ = bar_h;

    if (adi_bar_h_ < -1.0f) {
        adi_bar_h_ = -1.0f;
    }
    else if (adi_bar_h_> 1.0f) {
        adi_bar_h_ = 1.0f;
    }
    else {
        ;
    }

    adi_bar_h_visible_ = visible;
}

void FCSInstrucmentPFD::PanelADI::setADIDeviateBarPositionV(float bar_v,
                                                            bool  visible)
{
    adi_bar_v_ = bar_v;

    if (adi_bar_v_ < -1.0f) {
        adi_bar_v_ = -1.0f;
    }
    else if (adi_bar_v_> 1.0f) {
        adi_bar_v_ = 1.0f;
    }
    else {
        ;
    }

    adi_bar_v_visible_ = visible;
}

void FCSInstrucmentPFD::PanelADI::setADIDeviateDotPositionH(float dot_h,
                                                            bool  visible)
{
    adi_dot_h_ = dot_h;

    if (adi_dot_h_ < -1.0f) {
        adi_dot_h_ = -1.0f;
    }
    else if (adi_dot_h_> 1.0f) {
        adi_dot_h_ = 1.0f;
    }
    else {
        ;
    }

    adi_dot_h_visible_ = visible;
}

void FCSInstrucmentPFD::PanelADI::setADIDeviateDotPositionV(float dot_v,
                                                            bool  visible)
{
    adi_dot_v_ = dot_v;

    if (adi_dot_v_ < -1.0f) {
        adi_dot_v_ = -1.0f;
    }
    else if (adi_dot_v_> 1.0f) {
        adi_dot_v_ = 1.0f;
    }
    else {
        ;
    }

    adi_dot_v_visible_ = visible;
}

void FCSInstrucmentPFD::PanelADI::resetADI(void)
{
    adi_item_back_    = 0;
    adi_item_ladd_    = 0;
    adi_item_roll_    = 0;
    adi_item_slip_    = 0;
    adi_item_turn_    = 0;
    adi_item_path_    = 0;
    adi_item_mark_    = 0;
    adi_item_bar_h_   = 0;
    adi_item_bar_v_   = 0;
    adi_item_dot_h_   = 0;
    adi_item_dot_v_   = 0;
    adi_item_mask_    = 0;
    adi_item_scale_h_ = 0;
    adi_item_scale_v_ = 0;

    adi_angle_roll_     = 0.0f;
    adi_angle_pitch_    = 0.0f;
    adi_angle_attack_   = 0.0f;
    adi_angle_sideslip_ = 0.0f;
    adi_slip_skid_      = 0.0f;
    adi_turn_rate_      = 0.0f;
    adi_bar_h_          = 0.0f;
    adi_bar_v_          = 0.0f;
    adi_dot_h_          = 0.0f;
    adi_dot_v_          = 0.0f;

    adi_path_valid_    = true;
    adi_path_visible_  = true;
    adi_bar_h_visible_ = true;
    adi_bar_v_visible_ = true;
    adi_dot_h_visible_ = true;
    adi_dot_v_visible_ = true;

    adi_ladd_delta_x_new_      = 0.0f;
    adi_ladd_delta_x_old_      = 0.0f;
    adi_ladd_delta_y_new_      = 0.0f;
    adi_ladd_delta_y_old_      = 0.0f;
    adi_ladd_back_delta_x_new_ = 0.0f;
    adi_ladd_back_delta_x_old_ = 0.0f;
    adi_ladd_back_delta_y_new_ = 0.0f;
    adi_ladd_back_delta_y_old_ = 0.0f;
    adi_slip_delta_x_new_      = 0.0f;
    adi_slip_delta_x_old_      = 0.0f;
    adi_slip_delta_y_new_      = 0.0f;
    adi_slip_delta_y_old_      = 0.0f;
    adi_turn_delta_x_new_      = 0.0f;
    adi_turn_delta_x_old_      = 0.0f;
    adi_path_delta_x_new_      = 0.0f;
    adi_path_delta_x_old_      = 0.0f;
    adi_path_delta_y_new_      = 0.0f;
    adi_path_delta_y_old_      = 0.0f;
    adi_mark_delta_x_new_      = 0.0f;
    adi_mark_delta_x_old_      = 0.0f;
    adi_mark_delta_y_new_      = 0.0f;
    adi_mark_delta_y_old_      = 0.0f;
    adi_bar_h_delta_x_new_     = 0.0f;
    adi_bar_h_delta_x_old_     = 0.0f;
    adi_bar_v_delta_y_new_     = 0.0f;
    adi_bar_v_delta_y_old_     = 0.0f;
    adi_dot_h_delta_x_new_     = 0.0f;
    adi_dot_h_delta_x_old_     = 0.0f;
    adi_dot_v_delta_y_new_     = 0.0f;
    adi_dot_v_delta_y_old_     = 0.0f;
}

void FCSInstrucmentPFD::PanelADI::updateADILadd(float delta,
                                                float roll_sin,
                                                float roll_cos)
{
    adi_item_ladd_->setRotation(-adi_angle_roll_);

    adi_ladd_delta_x_new_ = adi_scale_x_ * delta * roll_sin;
    adi_ladd_delta_y_new_ = adi_scale_y_ * delta * roll_cos;

    adi_item_ladd_->moveBy(adi_ladd_delta_x_new_ - adi_ladd_delta_x_old_,
                           adi_ladd_delta_y_new_ - adi_ladd_delta_y_old_);
}

void FCSInstrucmentPFD::PanelADI::updateADILaddBack(float delta,
                                                    float roll_sin,
                                                    float roll_cos)
{
    adi_item_back_->setRotation(-adi_angle_roll_);

    float delta_ladd_back = 0.0f;

    if (delta > adi_delta_ladd_back_max_) {
        delta_ladd_back = adi_delta_ladd_back_max_;
    }
    else if (delta < adi_delta_ladd_back_min_) {
        delta_ladd_back = adi_delta_ladd_back_min_;
    }
    else {
        delta_ladd_back = delta;
    }

    adi_ladd_back_delta_x_new_ = adi_scale_x_ * delta_ladd_back * roll_sin;
    adi_ladd_back_delta_y_new_ = adi_scale_y_ * delta_ladd_back * roll_cos;

    adi_item_back_->moveBy(
        adi_ladd_back_delta_x_new_ - adi_ladd_back_delta_x_old_,
        adi_ladd_back_delta_y_new_ - adi_ladd_back_delta_y_old_);
}

void FCSInstrucmentPFD::PanelADI::updateADIAngleRoll(void)
{
    adi_item_roll_->setRotation(-adi_angle_roll_);
}

void FCSInstrucmentPFD::PanelADI::updateADiSlipSkip(float roll_sin,
                                                    float roll_cos)
{
    adi_item_slip_->setRotation(-adi_angle_roll_);

    float delta_slip = adi_max_slip_deflection_ * adi_slip_skid_;

    adi_slip_delta_x_new_ =  adi_scale_x_ * delta_slip * roll_cos;
    adi_slip_delta_y_new_ = -adi_scale_y_ * delta_slip * roll_sin;

    adi_item_slip_->moveBy(adi_slip_delta_x_new_ - adi_slip_delta_x_old_,
                           adi_slip_delta_y_new_ - adi_slip_delta_y_old_);
}

void FCSInstrucmentPFD::PanelADI::updateADITurnRate(void)
{
    adi_turn_delta_x_new_ = adi_scale_x_ * adi_max_turn_deflection_ *
        adi_turn_rate_;
    adi_item_turn_->moveBy(adi_turn_delta_x_new_ - adi_turn_delta_x_old_, 0.0);
}

void FCSInstrucmentPFD::PanelADI::updateADIFlightPath(void)
{
    if (adi_path_visible_) {
        adi_item_path_->setVisible(true);
        adi_path_delta_x_new_ = adi_scale_x_ * adi_original_pix_per_deg_ *
            adi_angle_sideslip_;
        adi_path_delta_y_new_ = adi_scale_y_ * adi_original_pix_per_deg_ *
            adi_angle_attack_;
        adi_item_path_->moveBy(adi_path_delta_x_new_ - adi_path_delta_x_old_,
                               adi_path_delta_y_new_ - adi_path_delta_y_old_);
        if (!adi_path_valid_) {
            adi_item_mark_->setVisible(true);
            adi_mark_delta_x_new_ = adi_path_delta_x_new_;
            adi_mark_delta_y_new_ = adi_path_delta_y_new_;
            adi_item_mark_->moveBy(
                adi_mark_delta_x_new_ - adi_mark_delta_x_old_,
                adi_mark_delta_y_new_ - adi_mark_delta_y_old_);
        }
        else {
            adi_item_mark_->setVisible(false);
            adi_mark_delta_x_new_ = adi_mark_delta_x_old_;
            adi_mark_delta_y_new_ = adi_mark_delta_y_old_;
        }
    }
    else {
        adi_item_path_->setVisible(false);
        adi_path_delta_x_new_ = adi_path_delta_x_old_;
        adi_path_delta_y_new_ = adi_path_delta_y_old_;

        adi_item_mark_->setVisible(false);
        adi_mark_delta_x_new_ = adi_mark_delta_x_old_;
        adi_mark_delta_y_new_ = adi_mark_delta_y_old_;
    }
}

void FCSInstrucmentPFD::PanelADI::updateADIBars(void)
{
    if (adi_bar_v_visible_) {
        adi_item_bar_v_->setVisible(true);
        adi_bar_v_delta_y_new_ = adi_scale_y_ * adi_max_bars_deflection_ *
            adi_bar_v_;
        adi_item_bar_v_->moveBy(
            0.0f,
            adi_bar_v_delta_y_old_ - adi_bar_v_delta_y_new_);
    }
    else {
        adi_item_bar_v_->setVisible(false);
        adi_bar_v_delta_y_new_ = adi_bar_v_delta_y_old_;
    }

    if (adi_bar_h_visible_) {
        adi_item_bar_h_->setVisible(true);
        adi_bar_h_delta_x_new_ = adi_scale_x_ * adi_max_bars_deflection_ *
            adi_bar_h_;
        adi_item_bar_h_->moveBy(
            adi_bar_h_delta_x_new_ - adi_bar_h_delta_x_old_,
            0.0f);
    }
    else {
        adi_item_bar_h_->setVisible(false);
        adi_bar_h_delta_x_new_ = adi_bar_h_delta_x_old_;
    }
}

void FCSInstrucmentPFD::PanelADI::updateADIDots(void)
{
    if (adi_dot_h_visible_) {
        adi_item_dot_h_->setVisible(true);
        adi_item_scale_h_->setVisible(true);
        adi_dot_h_delta_x_new_ = adi_scale_x_ * adi_max_dots_deflection_ *
            adi_dot_h_;
        adi_item_dot_h_->moveBy(
            adi_dot_h_delta_x_new_ - adi_dot_h_delta_x_old_,
            0.0f);
    }
    else {
        adi_item_dot_h_->setVisible(false);
        adi_item_scale_h_->setVisible(false);
        adi_dot_h_delta_x_new_ = adi_dot_h_delta_x_old_;
    }

    if (adi_dot_v_visible_) {
        adi_item_dot_v_->setVisible(true);
        adi_item_scale_v_->setVisible(true);
        adi_dot_v_delta_y_new_ = adi_scale_y_ * adi_max_dots_deflection_ *
            adi_dot_v_;
        adi_item_dot_v_->moveBy(
            0.0f,
            adi_dot_v_delta_y_old_ - adi_dot_v_delta_y_new_);
    }
    else {
        adi_item_dot_v_->setVisible(false);
        adi_item_scale_v_->setVisible(false);
        adi_dot_v_delta_y_new_ = adi_dot_v_delta_y_old_;
    }
}

/*****************************************************************************/

FCSInstrucmentPFD::PanelALT::PanelALT(QGraphicsScene *scene) :
    alt_scene_(scene),
    alt_item_back_    (0),
    alt_item_scale1_  (0),
    alt_item_scale2_  (0),
    alt_item_label1_  (0),
    alt_item_label2_  (0),
    alt_item_label3_  (0),
    alt_item_ground_  (0),
    alt_item_frame_   (0),
    alt_item_altitude_(0),
    alt_item_pressure_(0),
    alt_frame_text_color_(255, 255, 255),
    alt_press_text_color_(  0, 255,   0),
    alt_labels_color_    (255, 255, 255),
    alt_altitude_(0.0f),
    alt_pressure_(0.0f),
    alt_pressure_unit_(0),
    alt_scale1_delta_y_new_(0.0f),
    alt_scale1_delta_y_old_(0.0f),
    alt_scale2_delta_y_new_(0.0f),
    alt_scale2_delta_y_old_(0.0f),
    alt_ground_delta_y_new_(0.0f),
    alt_ground_delta_y_old_(0.0f),
    alt_labels_delta_y_new_(0.0f),
    alt_labels_delta_y_old_(0.0f),
    alt_scale_x_(1.0f),
    alt_scale_y_(1.0f),
    alt_original_pix_per_alt_ (0.150f),
    alt_original_scale_height_(300.0f),
    alt_original_labels_x_    (250.0f),
    alt_original_label1_y_    ( 50.0f),
    alt_original_label2_y_    (125.0f),
    alt_original_label3_y_    (200.0f),
    alt_original_back_pos_    (231.0f,   37.5f),
    alt_original_scale1_pos_  (231.0f, -174.5f),
    alt_original_scale2_pos_  (231.0f, -474.5f),
    alt_original_ground_pos_  (231.5f,  124.5f),
    alt_original_frame_pos_   (225.0f,  110.0f),
    alt_original_altitude_ctr_(254.0f,  126.0f),
    alt_original_pressure_ctr_(254.0f,  225.0f),
    alt_back_z_      ( 70),
    alt_scale_z_     ( 77),
    alt_labels_z_    ( 78),
    alt_ground_z_    ( 79),
    alt_frame_z_     (110),
    alt_frame_text_z_(120)
{
    alt_frame_text_font_.setFamily("Courier");
    alt_frame_text_font_.setPointSizeF(10.0f);
    alt_frame_text_font_.setStretch(QFont::Condensed);
    alt_frame_text_font_.setWeight(QFont::Bold);

    alt_labels_font_.setFamily("Courier");
    alt_labels_font_.setPointSizeF(8.0f);
    alt_labels_font_.setStretch(QFont::Condensed);
    alt_labels_font_.setWeight(QFont::Bold);

    resetALT();
}

void FCSInstrucmentPFD::PanelALT::initALT(float scale_x, float scale_y)
{
    alt_scale_x_ = scale_x;
    alt_scale_y_ = scale_y;

    resetALT();

    alt_item_back_ = new QGraphicsSvgItem(
        ":/fcs_instrucment/res/fcs_instrucment_pfd/pfd_alt_back.svg");
    alt_item_back_->setCacheMode(QGraphicsItem::NoCache);
    alt_item_back_->setZValue(alt_back_z_);
    alt_item_back_->setTransform(
        QTransform::fromScale(alt_scale_x_, alt_scale_y_),
        true);
    alt_item_back_->moveBy(alt_scale_x_ * alt_original_back_pos_.x(),
                           alt_scale_y_ * alt_original_back_pos_.y());
    alt_scene_->addItem(alt_item_back_);

    alt_item_scale1_ = new QGraphicsSvgItem(
        ":/fcs_instrucment/res/fcs_instrucment_pfd/pfd_alt_scale.svg");
    alt_item_scale1_->setCacheMode(QGraphicsItem::NoCache);
    alt_item_scale1_->setZValue(alt_scale_z_);
    alt_item_scale1_->setTransform(
        QTransform::fromScale(alt_scale_x_, alt_scale_y_),
        true);
    alt_item_scale1_->moveBy(alt_scale_x_ * alt_original_scale1_pos_.x(),
                             alt_scale_y_ * alt_original_scale1_pos_.y());
    alt_scene_->addItem(alt_item_scale1_);

    alt_item_scale2_ = new QGraphicsSvgItem(
        ":/fcs_instrucment/res/fcs_instrucment_pfd/pfd_alt_scale.svg");
    alt_item_scale2_->setCacheMode(QGraphicsItem::NoCache);
    alt_item_scale2_->setZValue(alt_scale_z_);
    alt_item_scale2_->setTransform(
        QTransform::fromScale(alt_scale_x_, alt_scale_y_),
        true);
    alt_item_scale2_->moveBy(alt_scale_x_ * alt_original_scale2_pos_.x(),
                             alt_scale_y_ * alt_original_scale2_pos_.y());
    alt_scene_->addItem(alt_item_scale2_);

    alt_item_label1_ = new QGraphicsTextItem(QString( "99999" ));
    alt_item_label1_->setCacheMode(QGraphicsItem::NoCache);
    alt_item_label1_->setZValue(alt_labels_z_);
    alt_item_label1_->setDefaultTextColor(alt_labels_color_);
    alt_item_label1_->setFont(alt_labels_font_);
    alt_item_label1_->setTransform(
        QTransform::fromScale(alt_scale_x_, alt_scale_y_),
        true);
    alt_item_label1_->moveBy(
        alt_scale_x_ * (alt_original_labels_x_ -
                        alt_item_label1_->boundingRect().width()  / 2.0f),
        alt_scale_y_ * (alt_original_label1_y_ -
                        alt_item_label1_->boundingRect().height() / 2.0f));
    alt_scene_->addItem(alt_item_label1_);

    alt_item_label2_ = new QGraphicsTextItem(QString( "99999" ));
    alt_item_label2_->setCacheMode(QGraphicsItem::NoCache);
    alt_item_label2_->setZValue(alt_labels_z_);
    alt_item_label2_->setDefaultTextColor(alt_labels_color_);
    alt_item_label2_->setFont(alt_labels_font_);
    alt_item_label2_->setTransform(
        QTransform::fromScale(alt_scale_x_, alt_scale_y_),
        true);
    alt_item_label2_->moveBy(
        alt_scale_x_ * (alt_original_labels_x_ -
                        alt_item_label2_->boundingRect().width()  / 2.0f),
        alt_scale_y_ * (alt_original_label2_y_ -
                        alt_item_label2_->boundingRect().height() / 2.0f));
    alt_scene_->addItem(alt_item_label2_);

    alt_item_label3_ = new QGraphicsTextItem(QString( "99999" ));
    alt_item_label3_->setCacheMode(QGraphicsItem::NoCache);
    alt_item_label3_->setZValue(alt_labels_z_);
    alt_item_label3_->setDefaultTextColor(alt_labels_color_);
    alt_item_label3_->setFont(alt_labels_font_);
    alt_item_label3_->setTransform(
        QTransform::fromScale(alt_scale_x_, alt_scale_y_),
        true);
    alt_item_label3_->moveBy(
        alt_scale_x_ * (alt_original_labels_x_ -
                        alt_item_label3_->boundingRect().width()  / 2.0f),
        alt_scale_y_ * (alt_original_label3_y_ -
                        alt_item_label3_->boundingRect().height() / 2.0f));
    alt_scene_->addItem(alt_item_label3_);

    alt_item_ground_ = new QGraphicsSvgItem(
        ":/fcs_instrucment/res/fcs_instrucment_pfd/pfd_alt_ground.svg");
    alt_item_ground_->setCacheMode(QGraphicsItem::NoCache);
    alt_item_ground_->setZValue(alt_ground_z_);
    alt_item_ground_->setTransform(
        QTransform::fromScale(alt_scale_x_, alt_scale_y_),
        true);
    alt_item_ground_->moveBy(alt_scale_x_ * alt_original_ground_pos_.x(),
                             alt_scale_y_ * alt_original_ground_pos_.y());
    alt_scene_->addItem(alt_item_ground_);

    alt_item_frame_ = new QGraphicsSvgItem(
        ":/fcs_instrucment/res/fcs_instrucment_pfd/pfd_alt_frame.svg");
    alt_item_frame_->setCacheMode(QGraphicsItem::NoCache);
    alt_item_frame_->setZValue(alt_frame_z_);
    alt_item_frame_->setTransform(
        QTransform::fromScale(alt_scale_x_, alt_scale_y_),
        true);
    alt_item_frame_->moveBy(alt_scale_x_ * alt_original_frame_pos_.x(),
                            alt_scale_y_ * alt_original_frame_pos_.y());
    alt_scene_->addItem(alt_item_frame_);

    alt_item_altitude_ = new QGraphicsTextItem(QString("0"));
    alt_item_altitude_->setCacheMode(QGraphicsItem::NoCache);
    alt_item_altitude_->setZValue(alt_frame_text_z_);
    alt_item_altitude_->setDefaultTextColor(alt_frame_text_color_);
    alt_item_altitude_->setFont(alt_frame_text_font_);
    alt_item_altitude_->setTransform(
        QTransform::fromScale(alt_scale_x_, alt_scale_y_),
        true);
    alt_item_altitude_->moveBy(
        alt_scale_x_ * (alt_original_altitude_ctr_.x() -
                        alt_item_altitude_->boundingRect().width()  / 2.0f),
        alt_scale_y_ * (alt_original_altitude_ctr_.y() -
                        alt_item_altitude_->boundingRect().height() / 2.0f));
    alt_scene_->addItem(alt_item_altitude_);

    alt_item_pressure_ = new QGraphicsTextItem(QString("STD"));
    alt_item_pressure_->setCacheMode(QGraphicsItem::NoCache);
    alt_item_pressure_->setZValue(alt_frame_text_z_);
    alt_item_pressure_->setDefaultTextColor(alt_press_text_color_);
    alt_item_pressure_->setFont(alt_frame_text_font_);
    alt_item_pressure_->setTransform(
        QTransform::fromScale(alt_scale_x_, alt_scale_y_),
        true);
    alt_item_pressure_->moveBy(
        alt_scale_x_ * (alt_original_pressure_ctr_.x() -
                        alt_item_pressure_->boundingRect().width()  / 2.0f),
        alt_scale_y_ * (alt_original_pressure_ctr_.y() -
                        alt_item_pressure_->boundingRect().height() / 2.0f));
    alt_scene_->addItem(alt_item_pressure_);

    updateALT(scale_x, scale_y);
}

void FCSInstrucmentPFD::PanelALT::updateALT(float scale_x, float scale_y)
{
    alt_scale_x_ = scale_x;
    alt_scale_y_ = scale_y;

    updateALTAltitude();
    updateALTPressure();

    alt_scale1_delta_y_old_ = alt_scale1_delta_y_new_;
    alt_scale2_delta_y_old_ = alt_scale2_delta_y_new_;
    alt_ground_delta_y_old_ = alt_ground_delta_y_new_;
    alt_labels_delta_y_old_ = alt_labels_delta_y_new_;
}

void FCSInstrucmentPFD::PanelALT::setALTAltitude(float altitude)
{
    alt_altitude_ = altitude;

    if (alt_altitude_ < 0.0f) {
        alt_altitude_ = 0.0f;
    }
    else if (alt_altitude_ > 99999.0f) {
        alt_altitude_ = 99999.0f;
    }
    else {
        ;
    }
}

void FCSInstrucmentPFD::PanelALT::setALTPressure(float pressure,
                                                 int   pressure_unit)
{
    alt_pressure_ = pressure;

    if (alt_pressure_ < 0.0f) {
        alt_pressure_ = 0.0f;
    }
    else if (alt_pressure_ > 2000.0f) {
        alt_pressure_ = 2000.0f;
    }
    else {
        ;
    }

    alt_pressure_unit_ = 0;

    if (pressure_unit == 1) {
        alt_pressure_unit_ = 1;
    }
    else if (pressure_unit == 2) {
        alt_pressure_unit_ = 2;
    }
    else {
        ;
    }
}

void FCSInstrucmentPFD::PanelALT::resetALT(void)
{
    alt_item_back_     = 0;
    alt_item_scale1_   = 0;
    alt_item_scale2_   = 0;
    alt_item_label1_   = 0;
    alt_item_label2_   = 0;
    alt_item_label3_   = 0;
    alt_item_ground_   = 0;
    alt_item_frame_    = 0;
    alt_item_altitude_ = 0;
    alt_item_pressure_ = 0;

    alt_altitude_ = 0.0f;
    alt_pressure_ = 0.0f;

    alt_pressure_unit_ = 0;

    alt_scale1_delta_y_new_ = 0.0f;
    alt_scale1_delta_y_old_ = 0.0f;
    alt_scale2_delta_y_new_ = 0.0f;
    alt_scale2_delta_y_old_ = 0.0f;
    alt_ground_delta_y_new_ = 0.0f;
    alt_ground_delta_y_old_ = 0.0f;
    alt_labels_delta_y_new_ = 0.0f;
    alt_labels_delta_y_old_ = 0.0f;
}

void FCSInstrucmentPFD::PanelALT::updateALTAltitude(void)
{
    alt_item_altitude_->setPlainText(
        QString("%1").arg(alt_altitude_, 5, 'f', 0, QChar('.')));

    updateALTScale();
    updateALTScaleLabels();
}

void FCSInstrucmentPFD::PanelALT::updateALTPressure(void)
{
    if (alt_pressure_unit_ == 0) {
        alt_item_pressure_->setPlainText(QString("STD"));
    }
    else if (alt_pressure_unit_ == 1) {
        alt_item_pressure_->setPlainText(
            QString::number(alt_pressure_, 'f', 0) + QString(" MB"));
    }
    else if (alt_pressure_unit_ == 2) {
        alt_item_pressure_->setPlainText(
            QString::number(alt_pressure_, 'f', 2) + QString(" IN"));
    }
    else {
        ;
    }
}

void FCSInstrucmentPFD::PanelALT::updateALTScale(void)
{
    alt_scale1_delta_y_new_ = alt_scale_y_ * alt_original_pix_per_alt_ *
        alt_altitude_;
    alt_scale2_delta_y_new_ = alt_scale1_delta_y_new_;
    alt_ground_delta_y_new_ = alt_scale1_delta_y_new_;

    float scale_single_height = alt_scale_y_ * alt_original_scale_height_;
    float scale_double_height = scale_single_height * 2.0f;

    while (alt_scale1_delta_y_new_ >
            scale_single_height + alt_scale_y_ * 74.5f) {
        alt_scale1_delta_y_new_ = alt_scale1_delta_y_new_ -
            scale_double_height;
    }

    while (alt_scale2_delta_y_new_ >
            scale_double_height + alt_scale_y_ * 74.5f) {
        alt_scale2_delta_y_new_ = alt_scale2_delta_y_new_ -
            scale_double_height;
    }

    if (alt_ground_delta_y_new_ > alt_scale_y_ * 100.0f) {
        alt_ground_delta_y_new_ = alt_scale_y_ * 100.0f;
    }
    else {
        ;
    }

    alt_item_scale1_->moveBy(
        0.0f,
        alt_scale1_delta_y_new_ - alt_scale1_delta_y_old_);
    alt_item_scale2_->moveBy(
        0.0f,
        alt_scale2_delta_y_new_ - alt_scale2_delta_y_old_);
    alt_item_ground_->moveBy(
        0.0f,
        alt_ground_delta_y_new_ - alt_ground_delta_y_old_);
}

void FCSInstrucmentPFD::PanelALT::updateALTScaleLabels(void)
{
    int tmp = floor(alt_altitude_ + 0.5f);
    int alt = tmp - (tmp % 500);

    float alt1 = (float)alt + 500.0f;
    float alt2 = (float)alt;
    float alt3 = (float)alt - 500.0f;

    alt_labels_delta_y_new_ = alt_scale_y_ * alt_original_pix_per_alt_ *
        alt_altitude_;

    while (alt_labels_delta_y_new_ > alt_scale_y_ * 37.5f) {
        alt_labels_delta_y_new_ = alt_labels_delta_y_new_ - alt_scale_y_ *
            75.0f;
    }

    if (alt_labels_delta_y_new_ < 0.0f && alt_altitude_ > alt2) {
        alt1 += 500.0f;
        alt2 += 500.0f;
        alt3 += 500.0f;
    }
    else {
        ;
    }

    alt_item_label1_->moveBy(
        0.0f,
        alt_labels_delta_y_new_ - alt_labels_delta_y_old_);
    alt_item_label2_->moveBy(
        0.0f,
        alt_labels_delta_y_new_ - alt_labels_delta_y_old_);
    alt_item_label3_->moveBy(
        0.0f,
        alt_labels_delta_y_new_ - alt_labels_delta_y_old_);

    if (alt1 > 0.0f && alt1 <= 100000.0f) {
        alt_item_label1_->setVisible(true);
        alt_item_label1_->setPlainText(
            QString("%1").arg(alt1, 5, 'f', 0, QChar(' ')));
    }
    else {
        alt_item_label1_->setVisible(false);
    }

    if (alt2 > 0.0f && alt2 <= 100000.0f) {
        alt_item_label2_->setVisible(true);
        alt_item_label2_->setPlainText(
            QString("%1").arg(alt2, 5, 'f', 0, QChar(' ')));
    }
    else {
        alt_item_label2_->setVisible(false);
    }

    if (alt3 > 0.0f && alt3 <= 100000.0f) {
        alt_item_label3_->setVisible(true);
        alt_item_label3_->setPlainText(
            QString("%1").arg(alt3, 5, 'f', 0, QChar(' ')));
    }
    else {
        alt_item_label3_->setVisible(false);
    }
}

/*****************************************************************************/

