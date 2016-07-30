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
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *  * Neither the name of the Team MicroDynamics nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
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
 *  This .cpp file implement the communication link.
 **********************************************************************/

#include <stdio.h>
#include <string.h>
#include <communication_link.h>

CommunicationLink::CommunicationLink(unsigned char owner_id,
                                     unsigned char other_id,
                                     CommunicationDataType *data_type)
{
    link_mode_   = MODE_MASTER;
    port_num_    = 1;
    owner_id_    = owner_id;
    other_id_    = other_id;
    link_ack_en_ = FALSE;
    data_type_   = data_type;

    if (link_mode_ == MODE_SLAVE) {
        link_ack_en_ = TRUE;
    }

    shake_hands_state_        = FALSE;
    receive_state_            = WAITING_FF_A;
    command_state_            = SHAKE_HANDS;
    recv_message_.sender_id   = 0;
    recv_message_.receiver_id = 0;
    recv_message_.length      = 0;
    send_message_.sender_id   = 0;
    send_message_.receiver_id = 0;
    send_message_.length      = 0;
    recv_package_count_       = 0;
    package_update_freq_      = 0;
    send_package_count_       = 0;
    send_buffer_[0]           = 0;
    send_buffer_length_       = 0;
}

void CommunicationLink::setOwnerID(unsigned char owner_id)
{
    owner_id_ = owner_id;
}

void CommunicationLink::setOtherID(unsigned char other_id)
{
    other_id_ = other_id;
}

void CommunicationLink::setPortNum(unsigned char port_num)
{
    port_num_ = port_num;
}

void CommunicationLink::enableAck(void)
{
    if (!link_ack_en_) {
        link_ack_en_ = TRUE;
    }
}

void CommunicationLink::disableAck(void)
{
    link_ack_en_ = FALSE;
}

unsigned char CommunicationLink::sendCommandFromMaster(
    CommunicationCommandState command_state)
{
    unsigned char  analysis_state = TRUE;
    unsigned char *single_command;

    if (link_mode_ != MODE_MASTER) {
        return FALSE;
    }

    switch (command_state) {
        case READ_GLOBAL_COORDINATE: {
            READ_COMMAND_STATE;
        }
        case READ_GLOBAL_COORD_SPEED: {
            READ_COMMAND_STATE;
        }
        case READ_ROBOT_COORDINATE: {
            READ_COMMAND_STATE;
        }
        case READ_ROBOT_COORD_SPEED: {
            READ_COMMAND_STATE;
        }
        case READ_ROBOT_IMU: {
            READ_COMMAND_STATE;
        }
        case READ_MOTOR_SPEED: {
            READ_COMMAND_STATE;
        }
        case READ_MOTOR_MILEAGE: {
            READ_COMMAND_STATE;
        }
        case READ_ROBOT_HEIGHT: {
            READ_COMMAND_STATE;
        }
        case READ_MOTOR_THRUST: {
            READ_COMMAND_STATE;
        }
        case READ_ROBOT_SPACE_POSE: {
            READ_COMMAND_STATE;
        }
        case READ_ROBOT_SYSTEM_INFO: {
            READ_COMMAND_STATE;
        }
        case SHAKE_HANDS: {
            shake_hands_state_ = TRUE;
            WRITE_COMMAND_STATE(data_type_->global_coordinate_actual_);
        }
        case WRITE_GLOBAL_COORD_SPEED: {
            WRITE_COMMAND_STATE(data_type_->global_coord_speed_target_);
        }
        case WRITE_ROBOT_COORD_SPEED: {
            WRITE_COMMAND_STATE(data_type_->robot_coord_speed_target_);
        }
        case WRITE_MOTOR_SPEED: {
            WRITE_COMMAND_STATE(data_type_->motor_speed_target_);
        }
        case WRITE_ROBOT_IMU: {
            WRITE_COMMAND_STATE(data_type_->robot_imu_target_);
        }
        case WRITE_ROBOT_HEIGHT: {
            WRITE_COMMAND_STATE(data_type_->robot_height_target_);
        }
        case WRITE_MOTOR_THRUST: {
            WRITE_COMMAND_STATE(data_type_->motor_thrust_target_);
        }
        case WRITE_ROBOT_SPACE_POSE: {
            WRITE_COMMAND_STATE(data_type_->robot_space_pose_target_);
        }
        default: {
            analysis_state = FALSE;
            break;
        }

        return analysis_state;
    }
}

unsigned char CommunicationLink::analyseReceiveByte(unsigned char recv_byte)
{
    unsigned char recv_package_flag = FALSE;
    unsigned char recv_message_flag = FALSE;

    recv_message_flag = analyseReceiveStates(recv_byte);

    if (recv_message_flag) {
        recv_message_flag = TRUE;
        recv_package_flag = analyseReceivePackage();
        if (recv_package_flag) {
            recv_package_count_++;
        }
        return recv_package_flag;
    }

    return FALSE;
}

unsigned char CommunicationLink::getReceiveState(
    CommunicationCommandState command_state)
{
    return recv_package_state_[command_state];
}

unsigned char *CommunicationLink::getSerializeData(void)
{
    return send_buffer_;
}

unsigned short CommunicationLink::getSerializedLength(void)
{
    return send_buffer_length_;
}

void CommunicationLink::sendData(CommunicationCommandState command_state,
                                 unsigned char *data_type,
                                 unsigned short data_type_length)
{
    send_message_.sender_id   = owner_id_;
    send_message_.receiver_id = other_id_;
    send_message_.length      = data_type_length + 1;
    send_message_.data[0]     = (unsigned char)command_state;

    // Fill specific data to send write command.
    if (data_type_length > 0) {
        memcpy(&send_message_.data[1], data_type, data_type_length);
    }
    // Fill empty data to send read command.
    else if (data_type_length == 0) {
    }

    sendMessage();
}

void CommunicationLink::sendMessage(void)
{
    unsigned short i;
    unsigned short checksum = 0;

    send_buffer_[0] = 0xff;
    checksum += 0xff;

    send_buffer_[1] = 0xff;
    checksum += 0xff;

    send_buffer_[2] = send_message_.sender_id;
    checksum += send_buffer_[2];

    send_buffer_[3] = send_message_.receiver_id;
    checksum += send_buffer_[3];

    send_buffer_[4] = (unsigned char)(send_message_.length >> 8);
    checksum += send_buffer_[4];

    send_buffer_[5] = (unsigned char)(send_message_.length);
    checksum += send_buffer_[5];

    for (i = 0; i < send_message_.length; i++) {
        send_buffer_[6 + i] = send_message_.data[i];
        checksum += send_buffer_[6 + i];
    }

    checksum = checksum % 255;
    send_buffer_[6 + i] = checksum;
    send_buffer_length_ = 7 + i;
    send_package_count_++;
}

unsigned char CommunicationLink::analyseReceiveStates(unsigned char recv_data)
{
    switch (receive_state_) {
        case WAITING_FF_A: {
            if (recv_data == 0xff) {
                receive_state_       = WAITING_FF_B;
                recv_checksum_       = 0;
                recv_message_length_ = 0;
                recv_byte_count_     = 0;
                recv_checksum_      += recv_data;
            }
            break;
        }
        case WAITING_FF_B: {
            if (recv_data == 0xff) {
                receive_state_  = GET_SENDER_ID;
                recv_checksum_ += recv_data;
            }
            else {
                receive_state_ = WAITING_FF_A;
            }
            break;
        }
        case GET_SENDER_ID: {
            recv_message_.sender_id = recv_data;
            if (recv_message_.sender_id == other_id_) {
                recv_checksum_ += recv_data;
                receive_state_  = GET_RECEIVER_ID;
            }
            else {
                printf("Error, the sender id is not exist!\n");
                receive_state_ = WAITING_FF_A;
            }
            break;
        }
        case GET_RECEIVER_ID: {
            recv_message_.receiver_id = recv_data;
            if (recv_message_.receiver_id == owner_id_) {
                recv_checksum_ += recv_data;
                receive_state_  = RECEIVE_LENGTH_H;
            }
            else {
                printf("Error, the receiver id is not exist!\n");
                receive_state_ = WAITING_FF_A;
            }
            break;
        }
        case RECEIVE_LENGTH_H: {
            recv_checksum_       += recv_data;
            recv_message_length_ |= recv_data << 8;
            receive_state_        = RECEIVE_LENGTH_L;
            break;
        }
        case RECEIVE_LENGTH_L: {
            recv_checksum_       += recv_data;
            recv_message_length_ |= recv_data;
            recv_message_.length  = recv_message_length_;
            receive_state_        = RECEIVE_PACKAGE;
            break;
        }
        case RECEIVE_PACKAGE: {
            recv_checksum_                        += recv_data;
            recv_message_.data[recv_byte_count_++] = recv_data;
            if (recv_byte_count_ >= recv_message_length_) {
                receive_state_ = RECEIVE_CHECKSUM;
                recv_checksum_ = recv_checksum_ % 255;
            }
            break;
        }
        case RECEIVE_CHECKSUM: {
            if (recv_data == (unsigned char)recv_checksum_) {
                recv_checksum_ = 0;
                receive_state_ = WAITING_FF_A;
                printf("Receive a package!\n");
                return TRUE;
            }
            else {
                printf("Checksum is error!\n");
                receive_state_ = WAITING_FF_A;
            }
            break;
        }
        default: {
            receive_state_ = WAITING_FF_A;
        }
    }

    return FALSE;
}

unsigned char CommunicationLink::analyseReceivePackage(void)
{
    unsigned char  analysis_state = FALSE;
    unsigned char *single_command;

    command_state_ = (CommunicationCommandState)recv_message_.data[0];

    // The slave need to check the state of SHAKE_HANDS.
    if (link_mode_ == MODE_SLAVE) {
        if (!shake_hands_state_ && command_state_ != SHAKE_HANDS) {
            sendData(SHAKE_HANDS, (unsigned char *)single_command, 0);
            return TRUE;
        }
    }

    switch (command_state_) {
        case SHAKE_HANDS: {
            analysis_state = analyseWriteCommand(
                command_state_,
                (unsigned char *)&data_type_->global_coordinate_actual_,
                sizeof(data_type_->global_coordinate_actual_));
            break;
        }
        case READ_GLOBAL_COORDINATE: {
            analysis_state = analyseReadCommand(
                command_state_,
                (unsigned char *)&data_type_->global_coordinate_actual_,
                sizeof(data_type_->global_coordinate_actual_));
            break;
        }
        case READ_GLOBAL_COORD_SPEED: {
            analysis_state = analyseReadCommand(
                command_state_,
                (unsigned char *)&data_type_->global_coord_speed_actual_,
                sizeof(data_type_->global_coord_speed_actual_));
            break;
        }
        case READ_ROBOT_COORDINATE: {
            analysis_state = analyseReadCommand(
                command_state_,
                (unsigned char *)&data_type_->robot_coordinate_actual_,
                sizeof(data_type_->robot_coordinate_actual_));
            break;
        }
        case READ_ROBOT_COORD_SPEED: {
            analysis_state = analyseReadCommand(
                command_state_,
                (unsigned char *)&data_type_->robot_coord_speed_actual_,
                sizeof(data_type_->robot_coord_speed_actual_));
            break;
        }
        case READ_ROBOT_IMU: {
            analysis_state = analyseReadCommand(
                command_state_,
                (unsigned char *)&data_type_->robot_imu_actual_,
                sizeof(data_type_->robot_imu_actual_));
            break;
        }
        case READ_MOTOR_SPEED: {
            analysis_state = analyseReadCommand(
                command_state_,
                (unsigned char *)&data_type_->motor_speed_actual_,
                sizeof(data_type_->motor_speed_actual_));
            break;
        }
        case READ_MOTOR_MILEAGE: {
            analysis_state = analyseReadCommand(
                command_state_,
                (unsigned char *)&data_type_->motor_mileage_actual_,
                sizeof(data_type_->motor_mileage_actual_));
            break;
        }
        case READ_ROBOT_HEIGHT: {
            analysis_state = analyseReadCommand(
                command_state_,
                (unsigned char *)&data_type_->robot_height_actual_,
                sizeof(data_type_->robot_height_actual_));
            break;
        }
        case READ_MOTOR_THRUST: {
            analysis_state = analyseReadCommand(
                command_state_,
                (unsigned char *)&data_type_->motor_thrust_actual_,
                sizeof(data_type_->motor_thrust_actual_));
            break;
        }
        case READ_ROBOT_SPACE_POSE: {
            analysis_state = analyseReadCommand(
                command_state_,
                (unsigned char *)&data_type_->robot_space_pose_actual_,
                sizeof(data_type_->robot_space_pose_actual_));
            break;
        }
        case READ_ROBOT_SYSTEM_INFO: {
            analysis_state = analyseReadCommand(
                command_state_,
                (unsigned char *)&data_type_->robot_system_info_actual_,
                sizeof(data_type_->robot_system_info_actual_));
            break;
        }
        case WRITE_GLOBAL_COORD_SPEED: {
            analysis_state = analyseWriteCommand(
                command_state_,
                (unsigned char *)&data_type_->global_coord_speed_target_,
                sizeof(data_type_->global_coord_speed_target_));
            break;
        }
        case WRITE_ROBOT_COORD_SPEED: {
            analysis_state = analyseWriteCommand(
                command_state_,
                (unsigned char *)&data_type_->robot_coord_speed_target_,
                sizeof(data_type_->robot_coord_speed_target_));
            break;
        }
        case WRITE_MOTOR_SPEED: {
            analysis_state = analyseWriteCommand(
                command_state_,
                (unsigned char *)&data_type_->motor_speed_target_,
                sizeof(data_type_->motor_speed_target_));
            break;
        }
        case WRITE_ROBOT_IMU: {
            analysis_state = analyseWriteCommand(
                command_state_,
                (unsigned char *)&data_type_->robot_imu_target_,
                sizeof(data_type_->robot_imu_target_));
            break;
        }
        case WRITE_ROBOT_HEIGHT: {
            analysis_state = analyseWriteCommand(
                command_state_,
                (unsigned char *)&data_type_->robot_height_target_,
                sizeof(data_type_->robot_height_target_));
            break;
        }
        case WRITE_MOTOR_THRUST: {
            analysis_state = analyseWriteCommand(
                command_state_,
                (unsigned char *)&data_type_->motor_thrust_target_,
                sizeof(data_type_->motor_thrust_target_));
            break;
        }
        case WRITE_ROBOT_SPACE_POSE: {
            analysis_state = analyseWriteCommand(
                command_state_,
                (unsigned char *)&data_type_->robot_space_pose_target_,
                sizeof(data_type_->robot_space_pose_target_));
            break;
        }
        default: {
            analysis_state = FALSE;
            break;
        }
    }

    // Clear the parameters.
    recv_message_.sender_id   = 0;
    recv_message_.receiver_id = 0;
    recv_message_.length      = 0;
    recv_message_.data[0]     = 0;

    return analysis_state;
}

unsigned char CommunicationLink::analyseReadCommand(
    CommunicationCommandState command_state,
    unsigned char *data_type,
    unsigned short data_type_length)
{
    // The slave feedback a package to master, and master save package.
    if (link_mode_ == MODE_MASTER) {
        if ((recv_message_.length - 1) != data_type_length) {
            printf("Error, the master can not read message from slave!");
            return FALSE;
        }
        memcpy(data_type, &recv_message_.data[1],
               data_type_length);
        recv_package_state_[(unsigned char)command_state] = TRUE;
    }
    // The master publish a read command to slave, and the slave feedback some
    // informations to master.
    else if (link_mode_ == MODE_SLAVE) {
        sendData(command_state, data_type, data_type_length);
        recv_package_state_[(unsigned char)command_state] = TRUE;
    }

    return TRUE;
}

unsigned char CommunicationLink::analyseWriteCommand(
    CommunicationCommandState command_state,
    unsigned char *data_type,
    unsigned short data_type_length)
{
    unsigned char *ack;

    // The master receive the slave's ack.
    if (link_mode_ = MODE_MASTER) {
        if (command_state == SHAKE_HANDS) {
            shake_hands_state_ = TRUE;
            printf("The slave is waiting master send data!\n");
        }
        else {
            printf("Receive a ack!\n");
        }
        recv_package_state_[(unsigned char)command_state] = TRUE;
    }
    // The master publish a write command to slave, the slave save this package
    // and feedback ack to master.
    else if (link_mode_ = MODE_SLAVE) {
        if ((recv_message_.length - 1) != data_type_length) {
            printf("Error, the slave can not read message from master!\n");
            return FALSE;
        }
        memcpy(data_type, &recv_message_.data[1], data_type_length);
        if (command_state == SHAKE_HANDS) {
            shake_hands_state_ = TRUE;
        }
        else {
            // The slave receive master's write package.
            sendData(command_state, ack, 0);
        }
        recv_package_state_[(unsigned char)command_state] = TRUE;
    }

    return TRUE;
}

#if !COMMUNICATION_LINK_LIB
int main(void)
{
    return 0;
}
#endif
