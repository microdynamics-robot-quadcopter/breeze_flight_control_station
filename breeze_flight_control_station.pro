#-------------------------------------------------
#
# Project created by QtCreator 2016-07-08T22:25:35
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET   = breeze_flight_control_station
TEMPLATE = app

SOURCES += \
    src/flight_altitude_indicator.cpp \
    src/flight_attitude_indicator.cpp \
    src/flight_compass_indicator.cpp \
    src/flight_control_station.cpp \
    src/main.cpp

HEADERS += \
    include/flight_altitude_indicator.h \
    include/flight_attitude_indicator.h \
    include/flight_compass_indicator.h \
    include/flight_control_station.h

FORMS += \
    form/flight_control_station.ui

INCLUDEPATH += include
