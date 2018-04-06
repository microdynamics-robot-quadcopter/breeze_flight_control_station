#-------------------------------------------------
#
# Project created by QtCreator 2016-07-08T22:25:35
#
#-------------------------------------------------

QT       += core gui svg multimedia multimediawidgets serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET   = breeze_flight_control_station
TEMPLATE = app

#INCLUDEPATH += \
#    /usr/include/boost

INCLUDEPATH += \
    include \
#    include/fcs_indicator \
    include/fcs_instrucment \
    include/fcs_instrucment_widget \
#    lib/communication_link/include \
#    lib/communication_serial/include
    lib/qcustomplot

#LIBS += \
#    /usr/lib/x86_64-linux-gnu/libboost_system.so \
#    /usr/lib/x86_64-linux-gnu/libboost_thread.so

HEADERS += \
    include/flight_control_station.h \
    include/fcs_instrucment/fcs_instrucment_pfd.h \
    include/fcs_instrucment_widget/fcs_instrucment_widget_pfd.h \
    include/fcs_instrucment_layout.h \
    include/fcs_custom_tab_style.h \
    include/fcs_custom_tab_widget.h

HEADERS += \
    lib/qcustomplot/qcustomplot.h

SOURCES += \
    src/flight_control_station.cpp \
    src/main.cpp \
    src/fcs_instrucment/fcs_instrucment_pfd.cpp \
    src/fcs_instrucment_widget/fcs_instrucment_widget_pfd.cpp \
    src/fcs_instrucment_layout.cpp \
    src/fcs_custom_tab_widget.cpp

SOURCES += \
#    lib/communication_serial/src/communication_port.cpp \
#    lib/communication_serial/src/communication_serial_port.cpp \
#    lib/communication_serial/src/communication_serial_interface.cpp \
#    lib/communication_link/src/communication_link.cpp \
#    lib/communication_link/src/communication_data_type.cpp
    lib/qcustomplot/qcustomplot.cpp

FORMS += \
    form/flight_control_station.ui \
    form/fcs_instrucment_widget/fcs_instrucment_widget_pfd.ui

RESOURCES += \
    breeze_flight_control_station.qrc
