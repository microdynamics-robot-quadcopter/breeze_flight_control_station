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
 *  myyerrol         2016.7.21     Create this file
 *
 *  Description:
 *  This .h file provides encapsulation for communication protocol and
 *  defines interfaces for reading/writing serial port.
 **********************************************************************/

#ifndef COMMUNICATION_SERIAL_INTERFACE_H
#define COMMUNICATION_SERIAL_INTERFACE_H

#define COMMUNICATION_SERIAL_INTERFACE_LIB 1

#include <fstream>
#include <communication_link.h>
#include <communication_serial_port.h>

namespace communication_serial {

typedef boost::shared_ptr<CommunicationSerialPort>     CommSerialPort;
typedef boost::shared_ptr<CommunicationLink>           CommLink;
typedef boost::shared_ptr<boost::asio::deadline_timer> Timer;

class CommunicationSerialInterface
{
public:
    CommunicationSerialInterface(std::string serial_url,
                                 std::string config_addr);
    void checkShakeHandState(void);
    bool getFlagInit(void);
    bool updateCommandState(const CommunicationCommandState &command_state,
                            int count);
    IO getIOInstace(void);
    CommunicationDataType *getDataType(void);
private:
    void runTimeoutHandler(const boost::system::error_code &error_code);
    void sendCommand(const CommunicationCommandState command_state);
    u_int8_t checkUpdateState(const CommunicationCommandState command_state);
private:
    int                   timeout_;
    int                   link_command_set_[LAST_COMMAND];
    int                   link_command_set_current_[LAST_COMMAND];
    int                   link_command_frequency_[LAST_COMMAND];
    int                   link_command_count_[LAST_COMMAND];
    bool                  flag_timeout_;
    bool                  flag_init_;
    bool                  flag_ack_;
    std::fstream          config_file_;
    boost::mutex          mutex_wait_;
    CommSerialPort        serial_port_;
    CommLink              serial_link_;
    Timer                 timer_;
    CommunicationDataType data_type_;
};

}

#endif // COMMUNICATION_SERIAL_INTERFACE_H
