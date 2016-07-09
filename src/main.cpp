#include "flight_control_station.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FlightControlStation w;
    w.show();

    return a.exec();
}
