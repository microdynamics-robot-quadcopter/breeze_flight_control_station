#ifndef FCS_INSTRUCMENT_WIDGET_HSI_H
#define FCS_INSTRUCMENT_WIDGET_HSI_H

#include <QWidget>

namespace Ui {
class FCSInstrucmentWidgetHSI;
}

class FCSInstrucmentWidgetHSI : public QWidget
{
    Q_OBJECT

public:
    explicit FCSInstrucmentWidgetHSI(QWidget *parent = 0);
    ~FCSInstrucmentWidgetHSI();

private:
    Ui::FCSInstrucmentWidgetHSI *ui;
};

#endif // FCS_INSTRUCMENT_WIDGET_HSI_H
