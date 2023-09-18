#include "adminlogin.h"
#include "ui_adminlogin.h"

adminlogin::adminlogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adminlogin)
{
    ui->setupUi(this);
    ptrAdminui = new adminui();
}

adminlogin::~adminlogin()
{
    delete ui;
    delete ptrAdminui;
}

void adminlogin::on_pushButton_5_clicked()
{
     ptrAdminui->show();
}

