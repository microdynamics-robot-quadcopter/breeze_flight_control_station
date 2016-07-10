#ifndef FLIGHT_COMPASS_INDICATOR_H
#define FLIGHT_COMPASS_INDICATOR_H

#include <QWidget>

#define VALUE_CHANGING_STEP 1

class FlightCompassIndicator : public QWidget
{
    Q_OBJECT
public:
    explicit FlightCompassIndicator(QWidget *parent = 0);
    ~FlightCompassIndicator();
    void setYaw(double yaw);
    double getYaw(void);
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
    double yaw_;
};

#endif // FLIGHT_COMPASS_INDICATOR_H
