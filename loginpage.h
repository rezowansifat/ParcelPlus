#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QDialog>
#include "adminlogin.h"
#include "dblogin.h"

namespace Ui {
class Loginpage;
}

class Loginpage : public QDialog
{
    Q_OBJECT

public:
    explicit Loginpage(QWidget *parent = nullptr);
    ~Loginpage();

private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::Loginpage *ui;
    adminlogin *ptrAdminlogin;
    dblogin *ptrdblogin;

};

#endif // LOGINPAGE_H
