#ifndef FLIGHT_CONTROL_STATION_H
#define FLIGHT_CONTROL_STATION_H

#include <QMainWindow>

namespace Ui {
class FlightControlStation;
}

class FlightControlStation : public QMainWindow
{
    Q_OBJECT

public:
    explicit FlightControlStation(QWidget *parent = 0);
    ~FlightControlStation();

private:
    Ui::FlightControlStation *ui;
};

#endif // FLIGHT_CONTROL_STATION_H
