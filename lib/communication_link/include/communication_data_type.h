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
 *  This .h file defines some data types for communication.
 **********************************************************************/

#ifndef COMMUNICATION_DATA_TYPE_H
#define COMMUNICATION_DATA_TYPE_H

typedef struct DataTypeAcceleration {
    float acc_x;
    float acc_y;
    float acc_z;
} DataTypeAcceleration;

typedef struct DataTypeCoordinate {
    float axis_x;
    float axis_y;
    float axis_z;
} DataTypeCoordinate;

typedef struct DataTypeAttitude {
    float att_r;
    float att_p;
    float att_y;
} DataTypeAttitude;

typedef struct DataTypeSpacePose {
    DataTypeCoordinate coo;
    DataTypeAttitude   att;
} DataTypeSpacePose;

typedef struct DataTypeIMU {
    DataTypeAcceleration acc;
    DataTypeAttitude     att;
} DataTypeIMU;

typedef struct DataTypeMotor {
    float motor_a;
    float motor_b;
    float motor_c;
    float motor_d;
} DataTypeMotor;

typedef struct DataTypeThrust {
    float thrust;
} DataTypeThrust;

typedef struct DataTypeHeight {
    float alt;
    float hei;
} DataTypeHeight;

typedef struct DataTypePID {
    float p;
    float i;
    float d;
} DataTypePID;

typedef struct DataTypeSystemInfo {
    float battery_capacity;
    float link_quality;
} DataTypeSystemInfo;

class CommunicationDataType
{
public:
    CommunicationDataType(void);
public:
    DataTypeCoordinate global_coord_speed_target_;
    DataTypeCoordinate global_coord_speed_actual_;
    DataTypeCoordinate global_coordinate_actual_;
    DataTypeCoordinate robot_coord_speed_target_;
    DataTypeCoordinate robot_coord_speed_actual_;
    DataTypeCoordinate robot_coordinate_actual_;
    DataTypeMotor      motor_speed_target_;
    DataTypeMotor      motor_speed_actual_;
    DataTypeMotor      motor_mileage_actual_;
    DataTypeIMU        robot_imu_target_;
    DataTypeIMU        robot_imu_actual_;
    DataTypeHeight     robot_height_target_;
    DataTypeHeight     robot_height_actual_;
    DataTypeThrust     motor_thrust_target_;
    DataTypeThrust     motor_thrust_actual_;
    DataTypeSpacePose  robot_space_pose_target_;
    DataTypeSpacePose  robot_space_pose_actual_;
    DataTypeSystemInfo robot_system_info_actual_;
};

#endif // COMMUNICATION_DATA_TYPE_H
