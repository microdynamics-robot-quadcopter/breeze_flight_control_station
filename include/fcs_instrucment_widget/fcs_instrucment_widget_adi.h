#ifndef FCS_INSTRUCMENT_WIDGET_ADI_H
#define FCS_INSTRUCMENT_WIDGET_ADI_H

#include <QWidget>

namespace Ui {
class FCSInstrucmentWidgetADI;
}

class FCSInstrucmentWidgetADI : public QWidget
{
    Q_OBJECT

public:
    explicit FCSInstrucmentWidgetADI(QWidget *parent = 0);
    ~FCSInstrucmentWidgetADI();

private:
    Ui::FCSInstrucmentWidgetADI *ui;
};

#endif // FCS_INSTRUCMENT_WIDGET_ADI_H
