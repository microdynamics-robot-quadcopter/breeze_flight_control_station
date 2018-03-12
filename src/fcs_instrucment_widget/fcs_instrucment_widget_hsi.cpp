#include "fcs_instrucment_widget_hsi.h"
#include "ui_fcs_instrucment_widget_hsi.h"

FCSInstrucmentWidgetHSI::FCSInstrucmentWidgetHSI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FCSInstrucmentWidgetHSI)
{
    ui->setupUi(this);
}

FCSInstrucmentWidgetHSI::~FCSInstrucmentWidgetHSI()
{
    delete ui;
}
