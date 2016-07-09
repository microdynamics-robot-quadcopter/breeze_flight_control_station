#include "flight_control_station.h"
#include "ui_flight_control_station.h"

FlightControlStation::FlightControlStation(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FlightControlStation)
{
    ui->setupUi(this);
    this->setWindowTitle("Flight Control Station");

    flight_attitude_indicator_ = new FlightAttitudeIndicator(this);
    ui->layoutIndicator->addWidget(flight_attitude_indicator_);

    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

FlightControlStation::~FlightControlStation()
{
    delete ui;
}
