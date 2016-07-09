#-------------------------------------------------
#
# Project created by QtCreator 2016-07-08T22:25:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = breeze_flight_control_station
TEMPLATE = app


SOURCES += main.cpp\
        flight_control_station.cpp \
    flight_attitude_indicator.cpp \
    flight_altitude_indicator.cpp

HEADERS  += flight_control_station.h \
    flight_attitude_indicator.h \
    flight_altitude_indicator.h

FORMS    += flight_control_station.ui
