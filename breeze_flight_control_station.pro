#-------------------------------------------------
#
# Project created by QtCreator 2016-07-08T22:25:35
#
#-------------------------------------------------

QT       += core gui svg multimedia multimediawidgets serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET   = breeze_flight_control_station
TEMPLATE = app

#INCLUDEPATH += \
#    /usr/include/boost

INCLUDEPATH += \
    include \
    include/fcs_indicator \
    include/fcs_instrucment \
    include/fcs_instrucment_widget \
    lib/communication_link/include \
    lib/communication_serial/include

#LIBS += \
#    /usr/lib/x86_64-linux-gnu/libboost_system.so \
#    /usr/lib/x86_64-linux-gnu/libboost_thread.so

HEADERS += \
    include/flight_control_station.h \
    include/fcs_indicator/fcs_indicator_altitude.h \
    include/fcs_indicator/fcs_indicator_attitude.h \
    include/fcs_indicator/fcs_indicator_compass.h \
    include/fcs_instrucment/fcs_instrucment_pfd.h \
    include/fcs_instrucment/fcs_instrucment_alt.h \
    include/fcs_instrucment/fcs_instrucment_hsi.h \
    include/fcs_instrucment/fcs_instrucment_adi.h \
    include/fcs_instrucment_widget/fcs_instrucment_widget_pfd.h \
    include/fcs_instrucment_widget/fcs_instrucment_widget_adi.h \
    include/fcs_instrucment_widget/fcs_instrucment_widget_alt.h \
    include/fcs_instrucment_widget/fcs_instrucment_widget_hsi.h \
    include/fcs_instrucment_layout.h \
    include/fcs_custom_tab_style.h \
    include/fcs_custom_tab_widget.h

SOURCES += \
    src/flight_control_station.cpp \
    src/main.cpp \
    src/fcs_indicator/fcs_indicator_altitude.cpp \
    src/fcs_indicator/fcs_indicator_attitude.cpp \
    src/fcs_indicator/fcs_indicator_compass.cpp \
    src/fcs_instrucment/fcs_instrucment_pfd.cpp \
    src/fcs_instrucment/fcs_instrucment_hsi.cpp \
    src/fcs_instrucment/fcs_instrucment_adi.cpp \
    src/fcs_instrucment/fcs_instrucment_alt.cpp \
    src/fcs_instrucment_widget/fcs_instrucment_widget_pfd.cpp \
    src/fcs_instrucment_widget/fcs_instrucment_widget_adi.cpp \
    src/fcs_instrucment_widget/fcs_instrucment_widget_alt.cpp \
    src/fcs_instrucment_widget/fcs_instrucment_widget_hsi.cpp \
    src/fcs_instrucment_layout.cpp \
    src/fcs_custom_tab_widget.cpp

SOURCES += \
#    lib/communication_serial/src/communication_port.cpp \
#    lib/communication_serial/src/communication_serial_port.cpp \
#    lib/communication_serial/src/communication_serial_interface.cpp \
#    lib/communication_link/src/communication_link.cpp \
#    lib/communication_link/src/communication_data_type.cpp

FORMS += \
    form/flight_control_station.ui \
    form/fcs_instrucment_widget/fcs_instrucment_widget_pfd.ui \
    form/fcs_instrucment_widget/fcs_instrucment_widget_adi.ui \
    form/fcs_instrucment_widget/fcs_instrucment_widget_alt.ui \
    form/fcs_instrucment_widget/fcs_instrucment_widget_hsi.ui

RESOURCES += \
    breeze_flight_control_station.qrc
