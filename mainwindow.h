#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void loadDbUsers();

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

    void on_ur_pushButton_userReg_clicked();

    void on_pushButton_clicked();

    void on_al_pushButton_admin_login_2_clicked();

    void on_al_pushButton_admin_login_clicked();

    void on_userlogut_clicked();

    void on_ap_pushButton_add_clicked();

    void on_user_pushButton_addpercle_clicked();

    void on_userlogut_2_clicked();

    void on_user_pushButton_goaddpercle_clicked();

    void on_myPercle_pushButton_clicked();

    void on_user_pushButton_addpercle_2_clicked();

    void on_userlogut_5_clicked();

    void on_admin_logout_clicked();

    void on_user_pushButton_goaddpercle_3_clicked();

    void on_allp_updatep_pushButton_clicked();

    void on_userlogut_9_clicked();

    void on_userlogut_3_clicked();

    void on_user_pushButton_addpercle_3_clicked();

    void on_userlogut_10_clicked();

private:
    Ui::MainWindow *ui;
    QString userEmailAddress;
    QString percleMail;

};
#endif // MAINWINDOW_H
