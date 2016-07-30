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
 *  This .h file defines some elements for creating communication link.
 **********************************************************************/

#ifndef COMMUNICATION_LINK_H
#define COMMUNICATION_LINK_H

#include "communication_data_type.h"

#define LINK_MODE              1
#define COMMUNICATION_LINK_LIB 1

#if !LINK_MODE
#include "communication_link_port.h"
#endif

#define MESSAGE_BUFFER_SIZE 100
#define TRUE                1
#define FALSE               0

#define READ_COMMAND_STATE                                         \
do {                                                               \
    recv_package_state_[(unsigned char)command_state] = FALSE;     \
    sendData(command_state, single_command, 0);                    \
    break;                                                         \
} while(FALSE)

#define WRITE_COMMAND_STATE(type)                                  \
do {                                                               \
    recv_package_state_[(unsigned char)command_state] = FALSE;     \
    sendData(command_state, (unsigned char *)&type, sizeof(type)); \
    break;                                                         \
} while(FALSE)

typedef enum CommunicationMode {
    MODE_MASTER,
    MODE_SLAVE
} CommunicationMode;

typedef enum CommunicationReceiveState {
    WAITING_FF_A,
    WAITING_FF_B,
    GET_SENDER_ID,
    GET_RECEIVER_ID,
    RECEIVE_LENGTH_H,
    RECEIVE_LENGTH_L,
    RECEIVE_PACKAGE,
    RECEIVE_CHECKSUM
} CommunicationReceiveState;

typedef enum CommunicationCommandState {
    SHAKE_HANDS,
    READ_GLOBAL_COORDINATE,
    READ_GLOBAL_COORD_SPEED,
    READ_ROBOT_COORDINATE,
    READ_ROBOT_COORD_SPEED,
    READ_ROBOT_IMU,
    READ_MOTOR_SPEED,
    READ_MOTOR_MILEAGE,
    READ_ROBOT_HEIGHT,
    READ_MOTOR_THRUST,
    READ_ROBOT_SPACE_POSE,
    READ_ROBOT_SYSTEM_INFO,
    WRITE_GLOBAL_COORD_SPEED,
    WRITE_ROBOT_COORD_SPEED,
    WRITE_MOTOR_SPEED,
    WRITE_ROBOT_IMU,
    WRITE_ROBOT_HEIGHT,
    WRITE_MOTOR_THRUST,
    WRITE_ROBOT_SPACE_POSE,
    LAST_COMMAND
} CommunicationCommandState;

typedef struct CommunicationMessage {
    unsigned char  sender_id;
    unsigned char  receiver_id;
    unsigned short length;
    unsigned char  data[MESSAGE_BUFFER_SIZE];
} CommunicationMessage;

class CommunicationLink
{
public:
    CommunicationLink(unsigned char owner_id = 0x11,
                      unsigned char other_id = 0x01,
                      CommunicationDataType *data_type = 0);
    void setOwnerID(unsigned char owner_id);
    void setOtherID(unsigned char other_id);
    void setPortNum(unsigned char port_num);
    void enableAck(void);
    void disableAck(void);
    unsigned char sendCommandFromMaster(CommunicationCommandState command_state);
    unsigned char analyseReceiveByte(unsigned char recv_byte);
    unsigned char getReceiveState(CommunicationCommandState command_state);
    unsigned char *getSerializeData(void);
    unsigned short getSerializedLength(void);
private:
    void sendData(CommunicationCommandState command_state,
                  unsigned char *data_type,
                  unsigned short data_type_length);
    void sendMessage(void);
    unsigned char analyseReceiveStates(unsigned char recv_data);
    unsigned char analyseReceivePackage(void);
    unsigned char analyseReadCommand(CommunicationCommandState command_state,
                                     unsigned char *data_type,
                                     unsigned short data_type_length);
    unsigned char analyseWriteCommand(CommunicationCommandState command_state,
                                      unsigned char *data_type,
                                      unsigned short data_type_length);
private:
    unsigned char              shake_hands_state_;
    unsigned char              recv_package_state_[LAST_COMMAND];
    unsigned char              port_num_;
    unsigned char              owner_id_;
    unsigned char              other_id_;
    unsigned char              link_ack_en_;
    unsigned char              send_buffer_[MESSAGE_BUFFER_SIZE + 20];
    unsigned short             send_buffer_length_;
    unsigned short             recv_checksum_;
    unsigned short             recv_message_length_;
    unsigned short             recv_byte_count_;
    float                      recv_package_count_;
    float                      send_package_count_;
    float                      package_update_freq_;
    CommunicationDataType     *data_type_;
    CommunicationReceiveState  receive_state_;
    CommunicationCommandState  command_state_;
    CommunicationMode          link_mode_;
    CommunicationMessage       recv_message_;
    CommunicationMessage       send_message_;
};

#endif // COMMUNICATION_LINK_H
