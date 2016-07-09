#ifndef FLIGHT_ATTITUDE_INDICATOR_H
#define FLIGHT_ATTITUDE_INDICATOR_H

#include <QWidget>

#define VALUE_CHANGING_STEP  1

class FlightAttitudeIndicator : public QWidget
{
    Q_OBJECT
public:
    explicit FlightAttitudeIndicator(QWidget *parent = 0);
    ~FlightAttitudeIndicator();
    void setPitchAndRoll(double pitch, double roll);
    void setPitch(double pitch);
    void setRoll(double roll);
    double getPitch(void);
    double getRoll(void);
signals:
    void replotCanvas(void);
protected slots:
    void updateCanvas(void);
protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent *event);
private:
    int    widget_size_min_;
    int    widget_size_max_;
    int    widget_size_curr_;
    int    widget_size_offset_;
    double pitch_;
    double roll_;
};

#endif // FLIGHT_ATTITUDE_INDICATOR_H
