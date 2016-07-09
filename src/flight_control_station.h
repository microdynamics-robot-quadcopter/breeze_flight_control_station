#ifndef FLIGHT_CONTROL_STATION_H
#define FLIGHT_CONTROL_STATION_H

#include <QMainWindow>
#include "flight_attitude_indicator.h"
#include "flight_altitude_indicator.h"

namespace Ui {
class FlightControlStation;
}

class FlightControlStation : public QMainWindow
{
    Q_OBJECT

public:
    explicit FlightControlStation(QWidget *parent = 0);
    ~FlightControlStation();
private slots:

private:
    Ui::FlightControlStation *ui;
    FlightAttitudeIndicator  *flight_attitude_indicator_;
    QADI                     *m_ADI;
};

#endif // FLIGHT_CONTROL_STATION_H
