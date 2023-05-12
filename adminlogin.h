#ifndef ADMINLOGIN_H
#define ADMINLOGIN_H

#include <QDialog>
#include "adminui.h"

namespace Ui {
class adminlogin;
}

class adminlogin : public QDialog
{
    Q_OBJECT

public:
    explicit adminlogin(QWidget *parent = nullptr);
    ~adminlogin();

private slots:
    void on_pushButton_5_clicked();

private:
    Ui::adminlogin *ui;
    adminui *ptrAdminui;
};

#endif // ADMINLOGIN_H
