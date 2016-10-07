#include "interfacejogo.h"
#include "ui_interfacejogo.h"

InterfaceJogo::InterfaceJogo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InterfaceJogo)
{
    ui->setupUi(this);
}

InterfaceJogo::~InterfaceJogo()
{
    delete ui;
}
