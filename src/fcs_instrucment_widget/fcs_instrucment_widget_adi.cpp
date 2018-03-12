#include "fcs_instrucment_widget_adi.h"
#include "ui_fcs_instrucment_widget_adi.h"

FCSInstrucmentWidgetADI::FCSInstrucmentWidgetADI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FCSInstrucmentWidgetADI)
{
    ui->setupUi(this);
}

FCSInstrucmentWidgetADI::~FCSInstrucmentWidgetADI()
{
    delete ui;
}
