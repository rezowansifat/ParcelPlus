#include "adminui.h"
#include "ui_adminui.h"

adminui::adminui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adminui)
{
    ui->setupUi(this);
}

adminui::~adminui()
{
    delete ui;
}
