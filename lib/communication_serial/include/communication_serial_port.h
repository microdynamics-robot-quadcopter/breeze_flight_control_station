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
 *  myyerrol         2016.7.19     Create this file
 *
 *  Description:
 *  This .h file defines serial communication operation class.
 **********************************************************************/

#ifndef COMMUNICATION_SERIAL_PORT_H
#define COMMUNICATION_SERIAL_PORT_H

#include "communication_port.h"
#include "communication_serial_param.h"

#define COMMUNICATION_SERIAL_PORT_LIB 1

namespace communication_serial {

typedef boost::shared_ptr<boost::asio::serial_port> SerialPort;

class CommunicationSerialPort : public CommunicationPort
{
public:
    CommunicationSerialPort(void);
    CommunicationSerialPort(std::string serial_url);
    Buffer readBuffer(void);
    void writeBuffer(Buffer &data);
private:
    void startOneRead(void);
    void startOneWrite(void);
    void runMainThread(void);
    void runReadHandler(const boost::system::error_code &error_code,
                        u_int32_t trans_bytes);
    void runWriteHandler(const boost::system::error_code &error_code);
    bool initializeSerialPort(void);
private:
    Buffer                   buffer_temp_;
    boost::thread            thread_;
    boost::mutex             mutex_port_;
    boost::mutex             mutex_read_;
    boost::mutex             mutex_write_;
    CommunicationSerialParam serial_param_;
    SerialPort               serial_port_;
};

}

#endif // COMMUNICATION_SERIAL_PORT_H
