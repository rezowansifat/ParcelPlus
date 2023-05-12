#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "loginpage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_stackedWidget_currentChanged(int arg1);

    void on_pushButton_3_clicked();

    void on_get_started_home_clicked();

    void on_sl_admin_pushButton_1_clicked();

    void on_sl_user_pushButton_2_clicked();

    void on_al_pushButton_goto_login_clicked();

    void on_ur_pushButton_goto_login_clicked();

    void on_backpush_clicked();

    void on_backpushTosl_clicked();

private:
    Ui::MainWindow *ui;
    Loginpage *ptrLoginpage;
};
#endif // MAINWINDOW_H
