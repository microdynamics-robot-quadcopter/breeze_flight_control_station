#-------------------------------------------------
#
# Project created by QtCreator 2016-07-08T22:25:35
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET   = breeze_flight_control_station
TEMPLATE = app

INCLUDEPATH += \
    /usr/include/boost

INCLUDEPATH += \
    include

INCLUDEPATH += \
    lib/communication_link/include \
    lib/communication_serial/include

LIBS += \
    /usr/lib/x86_64-linux-gnu/libboost_system.so \
    /usr/lib/x86_64-linux-gnu/libboost_thread.so

HEADERS += \
    include/flight_altitude_indicator.h \
    include/flight_attitude_indicator.h \
    include/flight_compass_indicator.h \
    include/flight_control_station.h

SOURCES += \
    src/flight_altitude_indicator.cpp \
    src/flight_attitude_indicator.cpp \
    src/flight_compass_indicator.cpp \
    src/flight_control_station.cpp \
    src/main.cpp

SOURCES += \
    lib/communication_serial/src/communication_port.cpp \
    lib/communication_serial/src/communication_serial_port.cpp \
    lib/communication_serial/src/communication_serial_interface.cpp \
    lib/communication_link/src/communication_link.cpp \
    lib/communication_link/src/communication_data_type.cpp

FORMS += \
    form/flight_control_station.ui
