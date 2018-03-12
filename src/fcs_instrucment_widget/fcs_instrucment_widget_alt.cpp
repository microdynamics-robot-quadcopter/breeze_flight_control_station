#include "fcs_instrucment_widget_alt.h"
#include "ui_fcs_instrucment_widget_alt.h"

FCSInstrucmentWidgetALT::FCSInstrucmentWidgetALT(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FCSInstrucmentWidgetALT)
{
    ui->setupUi(this);
}

FCSInstrucmentWidgetALT::~FCSInstrucmentWidgetALT()
{
    delete ui;
}
