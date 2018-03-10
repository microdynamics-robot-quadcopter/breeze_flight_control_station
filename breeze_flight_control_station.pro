#-------------------------------------------------
#
# Project created by QtCreator 2016-07-08T22:25:35
#
#-------------------------------------------------

QT += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET   = breeze_flight_control_station
TEMPLATE = app

INCLUDEPATH += \
    /usr/include/boost

INCLUDEPATH += \
    include \
    include/fcs_indicator \
    include/fcs_instrucment

INCLUDEPATH += \
    lib/communication_link/include \
    lib/communication_serial/include

LIBS += \
    /usr/lib/x86_64-linux-gnu/libboost_system.so \
    /usr/lib/x86_64-linux-gnu/libboost_thread.so

HEADERS += \
    include/flight_control_station.h \
    include/fcs_indicator/fcs_indicator_altitude.h \
    include/fcs_indicator/fcs_indicator_attitude.h \
    include/fcs_indicator/fcs_indicator_compass.h \
    include/fcs_instrucment/fcs_instrucment_pfd.h \
    include/fcs_instrucment/fcs_instrucment_alt.h \
    include/fcs_instrucment/fcs_instrucment_hsi.h \
    include/fcs_instrucment/fcs_instrucment_adi.h

SOURCES += \
    src/flight_control_station.cpp \
    src/main.cpp \
    src/fcs_indicator/fcs_indicator_altitude.cpp \
    src/fcs_indicator/fcs_indicator_attitude.cpp \
    src/fcs_indicator/fcs_indicator_compass.cpp \
    src/fcs_instrucment/fcs_instrucment_pfd.cpp \
    src/fcs_instrucment/fcs_instrucment_hsi.cpp \
    src/fcs_instrucment/fcs_instrucment_adi.cpp \
    src/fcs_instrucment/fcs_instrucment_alt.cpp

SOURCES += \
    lib/communication_serial/src/communication_port.cpp \
    lib/communication_serial/src/communication_serial_port.cpp \
    lib/communication_serial/src/communication_serial_interface.cpp \
    lib/communication_link/src/communication_link.cpp \
    lib/communication_link/src/communication_data_type.cpp

FORMS += \
    form/flight_control_station.ui

RESOURCES += \
    fcs_instrucment.qrc
