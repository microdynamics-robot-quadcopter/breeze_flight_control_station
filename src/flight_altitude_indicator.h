#ifndef FLIGHT_ALTITUDE_INDICATOR_H
#define FLIGHT_ALTITUDE_INDICATOR_H

#include <QWidget>

#define VALUE_CHANGING_STEP 1

class FlightAltitudeIndicator : public QWidget
{
    Q_OBJECT
public:
    explicit FlightAltitudeIndicator(QWidget *parent = 0);
    ~FlightAltitudeIndicator();
    void setAltitudeAndHeight(double altitude, double height);
    void setAltitude(double altitude);
    void setHeight(double height);
    double getAltitude(void);
    double getHeight(void);
signals:
    void replotCanvas(void);
public slots:
    void updateCanvas(void);
protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
    void keyPressEvent(QKeyEvent *event);
private:
    int    widget_size_min_;
    int    widget_size_max_;
    int    widget_size_curr_;
    int    widget_size_offset_;
    double altitude_;
    double height_;
};

#endif // FLIGHT_ALTITUDE_INDICATOR_H
