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
 *  This .cpp file implements encapsulation for communication protocol
 *  and interfaces for reading/writing serial port.
 **********************************************************************/

#include <communication_serial_interface.h>

namespace communication_serial {

CommunicationSerialInterface::CommunicationSerialInterface(
    std::string serial_url,
    std::string config_addr)
{
    std::string serial_port_mode = serial_url.substr(0, serial_url.find("://"));

    if (serial_port_mode == "serial") {
        serial_port_ = boost::make_shared<CommunicationSerialPort>(serial_url);
        timeout_ = 500;
        serial_link_ = boost::make_shared<CommunicationLink>(0x01, 0x11,
                                                             &data_type_);
        timer_.reset(new boost::asio::deadline_timer(
                             *(serial_port_->getIOInstance()),
                             boost::posix_time::milliseconds(timeout_)));
    }
    else {
    }

    config_file_.open(config_addr.c_str(), std::fstream::in);

    if (config_file_.is_open()) {
        for (int i = 0; i < LAST_COMMAND; i++) {
            std::string command_name;
            config_file_ >> command_name >> link_command_set_[i]
                         >> link_command_frequency_[i];
            std::cout << command_name << link_command_set_[i]
                      << link_command_frequency_[i] << std::endl;
        }
        config_file_.close();
        flag_init_ = serial_port_->getFlagInit();
    }
    else {
        std::cerr << "Config file can't be opened!" << std::endl;
        flag_init_ = false;
    }
}

void CommunicationSerialInterface::checkShakeHandState(void)
{
    if (serial_link_->getReceiveState(SHAKE_HANDS)) {
        sendCommand(SHAKE_HANDS);
        std::cout << "Send shake hands command." << std::endl;
    }
}

bool CommunicationSerialInterface::getFlagInit(void)
{
    return flag_init_;
}

bool CommunicationSerialInterface::updateCommandState(
    const CommunicationCommandState &command_state,
    int count)
{
    boost::asio::deadline_timer circle_timer_(*(serial_port_->getIOInstance()));
    circle_timer_.expires_from_now(boost::posix_time::milliseconds(timeout_));

    if (!link_command_set_[command_state]) {
        int cnt = count % 100;
        if (cnt % (100 / link_command_frequency_[command_state]) == 0) {
            sendCommand(command_state);
        }
        else {
            return false;
        }
    }

    Buffer data = serial_port_->readBuffer();
    flag_ack_ = false;

    while (!flag_ack_) {
        for (int i = 0; i < data.size(); i++) {
            if (serial_link_->analyseReceiveByte(data[i])) {
                flag_ack_ = true;
            }
        }
        data = serial_port_->readBuffer();
        if (circle_timer_.expires_from_now().is_negative()) {
            std::cerr << "Timeout, skip this package!" << std::endl;
            return false;
        }
    }

    return true;
}

IO CommunicationSerialInterface::getIOInstace(void)
{
    return serial_port_->getIOInstance();
}

CommunicationDataType *CommunicationSerialInterface::getDataType(void)
{
    return &data_type_;
}

void CommunicationSerialInterface::runTimeoutHandler(
    const boost::system::error_code &error_code)
{
    if (!error_code) {
        std::cerr << "Timeout!" << std::endl;
        boost::mutex::scoped_lock lock(mutex_wait_);
        flag_timeout_ = true;
    }
}

void CommunicationSerialInterface::sendCommand(
    const CommunicationCommandState command_state)
{
    std::cout << "Send command: " << command_state << std::endl;
    serial_link_->sendCommandFromMaster(command_state);
    Buffer data(serial_link_->getSerializeData(),
                serial_link_->getSerializeData() +
                serial_link_->getSerializedLength());
    serial_port_->writeBuffer(data);
}

u_int8_t CommunicationSerialInterface::checkUpdateState(
    const CommunicationCommandState command_state)
{
    if (link_command_set_current_[command_state] &
        serial_link_->getReceiveState(command_state)) {
        return TRUE;
    }
    if (!link_command_set_current_[command_state]) {
        return TRUE;
    }

    return FALSE;
}

}

#if !COMMUNICATION_SERIAL_INTERFACE_LIB
int main(void)
{
    return 0;
}
#endif
