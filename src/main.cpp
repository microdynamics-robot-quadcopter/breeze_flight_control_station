#include <QApplication>
#include <QDesktopWidget>
#include "flight_control_station.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FlightControlStation w;

    w.move((QApplication::desktop()->width()  - w.width()) / 2,
           (QApplication::desktop()->height() - w.height()) / 2);
    w.show();

    return a.exec();
}
