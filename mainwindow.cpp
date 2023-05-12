#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()
{
    ptrLoginpage->show();
}


void MainWindow::on_stackedWidget_currentChanged(int arg1)
{

}

void MainWindow::on_get_started_home_clicked()
{
  ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_sl_admin_pushButton_1_clicked()
{
  ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_sl_user_pushButton_2_clicked()
{
  ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_al_pushButton_goto_login_clicked()
{
  ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_ur_pushButton_goto_login_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_backpush_clicked()
{
    int previousIndex = ui->stackedWidget->currentIndex() - 1;
    if (previousIndex < 0) {
        previousIndex = ui->stackedWidget->count() - 1;
    }
    ui->stackedWidget->setCurrentIndex(previousIndex);
}


void MainWindow::on_backpushTosl_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

