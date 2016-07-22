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
 *  myyerrol         2016.7.19     Create this file
 *
 *  Description:
 *  This .cpp file implements serial communication operation class.
 **********************************************************************/

#include <iostream>
#include <communication_serial_port.h>

namespace communication_serial {

CommunicationSerialPort::CommunicationSerialPort(void) :
    CommunicationPort("serial:///dev/ttyUSB0")
{
    serial_param_.port_ = "/dev/ttyUSB0";

    if (!initializeSerialPort()) {
        std::cerr << "Failed to initialize serial port!" << std::endl;
        flag_init_ = false;
    }
    else {
        std::cout << "Initialize serial port successfully!" << std::endl;
        flag_init_ = true;
    }
}

CommunicationSerialPort::CommunicationSerialPort(std::string serial_url) :
    CommunicationPort(serial_url)
{
    if (comm_url_.substr(0, comm_url_.find("://")) != "serial") {
        std::cerr << "URL is error!" << std::endl;
        return ;
    }

    serial_param_.port_ = comm_url_.substr(comm_url_.find("://") + 3,
                                           comm_url_.length() -
                                           comm_url_.find("://"));

    if (!initializeSerialPort()) {
        std::cerr << "Failed to initialize serial port!" << std::endl;
        flag_init_ = false;
    }
    else {
        std::cout << "Initialize serial port successfully!" << std::endl;
        flag_init_ = true;
    }
}

Buffer CommunicationSerialPort::readBuffer(void)
{
    boost::mutex::scoped_lock lock(mutex_read_);
    Buffer data;

    if (!buffer_read_.empty()) {
        Buffer data(buffer_read_.front());
        buffer_read_.pop();
        return data;
    }

    return data;
}

void CommunicationSerialPort::writeBuffer(Buffer &data)
{
    boost::mutex::scoped_lock lock(mutex_write_);

    buffer_write_.push(data);
    startOneWrite();
}

void CommunicationSerialPort::startOneRead(void)
{
    boost::mutex::scoped_lock lock(mutex_port_);

    serial_port_->async_read_some(
        boost::asio::buffer(buffer_temp_),
        boost::bind(&CommunicationSerialPort::runReadHandler, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
}

void CommunicationSerialPort::startOneWrite(void)
{
    boost::mutex::scoped_lock lock(mutex_port_);

    if (!buffer_write_.empty()) {
        boost::asio::async_write(*serial_port_,
                                 boost::asio::buffer(buffer_write_.front()),
                                 boost::bind(
                                     &CommunicationSerialPort::runWriteHandler,
                                     this,
                                     boost::asio::placeholders::error));
        buffer_write_.pop();
    }
}

void CommunicationSerialPort::runMainThread(void)
{
    std::cout << "Start thread to read/write serial port!" << std::endl;
    startOneRead();
    io_service_->run();
}

void CommunicationSerialPort::runReadHandler(
    const boost::system::error_code &error_code,
    u_int32_t trans_bytes)
{
    if (error_code) {
        std::cerr << "Read serial port error!" << std::endl;
        return ;
    }

    boost::mutex::scoped_lock lock(mutex_read_);
    Buffer data(buffer_temp_.begin(), buffer_temp_.begin() + trans_bytes);
    buffer_read_.push(data);
    startOneRead();
}

void CommunicationSerialPort::runWriteHandler(
    const boost::system::error_code &error_code)
{
    if (error_code) {
        std::cerr << "Write serial port error!" << std::endl;
        return ;
    }

    boost::mutex::scoped_lock lock(mutex_write_);

    if (!buffer_write_.empty()) {
        startOneWrite();
    }
}

bool CommunicationSerialPort::initializeSerialPort(void)
{
    try {
        serial_port_ = boost::make_shared<boost::asio::serial_port>(
             boost::ref(*io_service_), serial_param_.port_);
        serial_port_->set_option(boost::asio::serial_port::baud_rate(
            serial_param_.baud_rate_));
        serial_port_->set_option(boost::asio::serial_port::flow_control(
            (boost::asio::serial_port::flow_control::type)
            serial_param_.flow_control_));
        serial_port_->set_option(boost::asio::serial_port::parity(
            (boost::asio::serial_port::parity::type)
            serial_param_.parity_));
        serial_port_->set_option(boost::asio::serial_port::stop_bits(
            (boost::asio::serial_port::stop_bits::type)
            serial_param_.stop_bits_));
        serial_port_->set_option(boost::asio::serial_port::character_size(8));
    }
    catch(std::exception &exce) {
        std::cerr << "Failed to open serial port!" << std::endl;
        std::cerr << "Error information: " << "(" << exce.what() << ")"
                  << std::endl;
        return false;
    }

    buffer_temp_.resize(1024);

    try {
        thread_ = boost::thread(boost::bind(
                                    &CommunicationSerialPort::runMainThread,
                                    this));
    }
    catch (std::exception &exce) {
        std::cerr << "Failed to create serial port thread!" << std::endl;
        std::cerr << "Error information: " << "(" << exce.what() << ")"
                  << std::endl;
        return false;
    }

    return true;
}

}

#if !COMMUNICATION_SERIAL_PORT_LIB
int main(void)
{
    return 0;
}
#endif
