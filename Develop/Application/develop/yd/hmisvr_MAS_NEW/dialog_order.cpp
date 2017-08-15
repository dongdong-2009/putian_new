#include "dialog_order.h"
#include "ui_dialog_order.h"

Dialog_order::Dialog_order(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_order)
{
    ui->setupUi(this);
}

Dialog_order::~Dialog_order()
{
    delete ui;
}
