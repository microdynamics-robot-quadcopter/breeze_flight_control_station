#include "fcs_instrucment_widget_pfd.h"
#include "ui_fcs_instrucment_widget_pfd.h"

FCSInstrucmentWidgetPFD::FCSInstrucmentWidgetPFD(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FCSInstrucmentWidgetPFD)
{
    ui->setupUi(this);
}

FCSInstrucmentWidgetPFD::~FCSInstrucmentWidgetPFD()
{
    delete ui;
}
