#ifndef FCS_INSTRUCMENT_WIDGET_ALT_H
#define FCS_INSTRUCMENT_WIDGET_ALT_H

#include <QWidget>

namespace Ui {
class FCSInstrucmentWidgetALT;
}

class FCSInstrucmentWidgetALT : public QWidget
{
    Q_OBJECT

public:
    explicit FCSInstrucmentWidgetALT(QWidget *parent = 0);
    ~FCSInstrucmentWidgetALT();

private:
    Ui::FCSInstrucmentWidgetALT *ui;
};

#endif // FCS_INSTRUCMENT_WIDGET_ALT_H
