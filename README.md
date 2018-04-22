# breeze_flight_control_station

[![travis-ci_bulid_status](https://travis-ci.org/microdynamics-quadcopter/breeze_flight_control_station.svg?branch=master)](https://travis-ci.org/microdynamics-quadcopter/breeze_flight_control_station) ![release_downloads](https://img.shields.io/github/downloads/microdynamics-quadcopter/breeze_flight_control_station/total.svg) ![release](https://img.shields.io/github/release/microdynamics-quadcopter/breeze_flight_control_station.svg) [![gpl-3.0](https://img.shields.io/badge/license-GPL--3.0-blue.svg)](./LICENSE) ![version-1.0.0](https://img.shields.io/badge/version-1.0.0-FF69B4.svg) ![platform](https://img.shields.io/badge/platform-linux--64%20%7C%20win--64-orange.svg) [![joint_chat](https://img.shields.io/badge/gitter-join%20chat-yellow.svg)](https://gitter.im/microdynamics-quadcopter/developer)

## Description

Breeze flight control station can implement real-time monitoring and control on the computer client.

![breeze_fcs_1_flight_status](.images/breeze_fcs_1_flight_status.png)

![breeze_fcs_2_serial_console](.images/breeze_fcs_2_serial_console.png)

![breeze_fcs_3_data_plotter](.images/breeze_fcs_3_data_plotter.png)

![breeze_fcs_7_program_settings](.images/breeze_fcs_7_program_settings.png)

## Requirment

- Ubuntu 16.04
- Qt 5.9
- GCC 5.4
- Boost 1.58

## Configuration

Install some dependent pacages:

```sh
$> sudo apt-get update
$> sudo apt-get install build-essential libboost-all-dev
```

Download the repository:

```sh
$> cd ~/Desktop
$> git clone https://github.com/microdynamics-quadcopter/breeze_flight_control_station.git
```

Build the codes:

```sh
$> cd ~/Desktop/breeze_flight_control_station
$> mkdir build; cd build
$> /opt/Qt5.9.1/5.9.1/gcc_64/bin/qmake ../breeze_flight_control_station.pro
$> make
```

## Usage

```sh
$> cd ~/Desktop/breeze_flight_control_station/build
$> ./breeze_flight_control_station
```
