#include "loginpage.h"
#include "ui_loginpage.h"

Loginpage::Loginpage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Loginpage)
{
    ui->setupUi(this);
    ptrAdminlogin = new adminlogin();
    ptrdblogin = new dblogin();
}

Loginpage::~Loginpage()
{
    delete ui;
    delete ptrAdminlogin;
    delete ptrdblogin;
}

void Loginpage::on_pushButton_5_clicked()
{
    ptrAdminlogin->show();
}


void Loginpage::on_pushButton_6_clicked()
{
    ptrdblogin->show();
}

