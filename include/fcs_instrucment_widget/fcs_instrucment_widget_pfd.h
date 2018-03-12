#ifndef FCS_INSTRUCMENT_WIDGET_PFD_H
#define FCS_INSTRUCMENT_WIDGET_PFD_H

#include <QWidget>

namespace Ui {
class FCSInstrucmentWidgetPFD;
}

class FCSInstrucmentWidgetPFD : public QWidget
{
    Q_OBJECT

public:
    explicit FCSInstrucmentWidgetPFD(QWidget *parent = 0);
    ~FCSInstrucmentWidgetPFD();

private:
    Ui::FCSInstrucmentWidgetPFD *ui;
};

#endif // FCS_INSTRUCMENT_WIDGET_PFD_H
