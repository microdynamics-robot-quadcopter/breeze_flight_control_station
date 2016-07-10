#include "flight_control_station.h"
#include "ui_flight_control_station.h"

FlightControlStation::FlightControlStation(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FlightControlStation)
{
    ui->setupUi(this);
    this->setWindowTitle("Flight Control Station");

    flight_attitude_indicator_ = new FlightAttitudeIndicator(this);
    flight_altitude_indicator_ = new FlightAltitudeIndicator(this);
    flight_compass_indicator_  = new FlightCompassIndicator(this);

    ui->layoutIndicator->addWidget(flight_attitude_indicator_);
    ui->layoutIndicator->addWidget(flight_altitude_indicator_);
    ui->layoutIndicator->addWidget(flight_compass_indicator_);

    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

FlightControlStation::~FlightControlStation()
{
    delete ui;
}
