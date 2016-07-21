/***********************************************************************
 *  Software License Agreement (BSD License)
 *
 *  Copyright (c) 2016, Team MicroDynamics
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 *  * Neither the name of the Team MicroDynamics nor the names
 *    of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written
 *    permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 ***********************************************************************

 ***********************************************************************
 *  History:
 *  <Authors>        <Date>        <Operation>
 *  myyerrol         2016.7.17     Create this file
 *
 *  Description:
 *  This .cpp file create and initialize data types.
 **********************************************************************/

#include <communication_data_type.h>

CommunicationDataType::CommunicationDataType(void)
{
    global_coord_speed_target_.axis_x = 0.0;
    global_coord_speed_target_.axis_y = 0.0;
    global_coord_speed_target_.axis_z = 0.0;

    global_coord_speed_actual_.axis_x = 0.0;
    global_coord_speed_actual_.axis_y = 0.0;
    global_coord_speed_actual_.axis_z = 0.0;

    global_coordinate_actual_.axis_x = 0.0;
    global_coordinate_actual_.axis_y = 0.0;
    global_coordinate_actual_.axis_z = 0.0;

    robot_coord_speed_target_.axis_x = 0.0;
    robot_coord_speed_target_.axis_y = 0.0;
    robot_coord_speed_target_.axis_z = 0.0;

    robot_coord_speed_actual_.axis_x = 0.0;
    robot_coord_speed_actual_.axis_y = 0.0;
    robot_coord_speed_actual_.axis_z = 0.0;

    robot_coordinate_actual_.axis_x = 0.0;
    robot_coordinate_actual_.axis_y = 0.0;
    robot_coordinate_actual_.axis_z = 0.0;

    motor_speed_target_.motor_a = 0.0;
    motor_speed_target_.motor_b = 0.0;
    motor_speed_target_.motor_c = 0.0;
    motor_speed_target_.motor_d = 0.0;

    motor_speed_actual_.motor_a = 0.0;
    motor_speed_actual_.motor_b = 0.0;
    motor_speed_actual_.motor_c = 0.0;
    motor_speed_actual_.motor_d = 0.0;

    motor_mileage_actual_.motor_a = 0.0;
    motor_mileage_actual_.motor_b = 0.0;
    motor_mileage_actual_.motor_c = 0.0;
    motor_mileage_actual_.motor_d = 0.0;

    robot_imu_target_.acc.acc_x = 0.0;
    robot_imu_target_.acc.acc_y = 0.0;
    robot_imu_target_.acc.acc_z = 0.0;
    robot_imu_target_.att.att_r = 0.0;
    robot_imu_target_.att.att_p = 0.0;
    robot_imu_target_.att.att_y = 0.0;

    robot_imu_actual_.acc.acc_x = 0.0;
    robot_imu_actual_.acc.acc_y = 0.0;
    robot_imu_actual_.acc.acc_z = 0.0;
    robot_imu_actual_.att.att_r = 0.0;
    robot_imu_actual_.att.att_p = 0.0;
    robot_imu_actual_.att.att_y = 0.0;

    robot_height_target_.alt = 0.0;
    robot_height_target_.hei = 0.0;

    robot_height_actual_.alt = 0.0;
    robot_height_actual_.hei = 0.0;

    motor_thrust_target_.thrust = 0.0;
    motor_thrust_actual_.thrust = 0.0;

    robot_space_pose_target_.coo.axis_x = 0.0;
    robot_space_pose_target_.coo.axis_y = 0.0;
    robot_space_pose_target_.coo.axis_z = 0.0;
    robot_space_pose_target_.att.att_r  = 0.0;
    robot_space_pose_target_.att.att_p  = 0.0;
    robot_space_pose_target_.att.att_y  = 0.0;

    robot_space_pose_actual_.coo.axis_x = 0.0;
    robot_space_pose_actual_.coo.axis_y = 0.0;
    robot_space_pose_actual_.coo.axis_z = 0.0;
    robot_space_pose_actual_.att.att_r  = 0.0;
    robot_space_pose_actual_.att.att_p  = 0.0;
    robot_space_pose_actual_.att.att_y  = 0.0;


    robot_system_info_actual_.battery_capacity = 0.0;
    robot_system_info_actual_.link_quality     = 0.0;
}
