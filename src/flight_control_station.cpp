#include "flight_control_station.h"
#include "ui_flight_control_station.h"

FlightControlStation::FlightControlStation(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FlightControlStation)
{
    ui->setupUi(this);
}

FlightControlStation::~FlightControlStation()
{
    delete ui;
}
