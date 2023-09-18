#include "dblogin.h"
#include "ui_dblogin.h"

dblogin::dblogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dblogin)
{
    ui->setupUi(this);
}

dblogin::~dblogin()
{
    delete ui;
}
