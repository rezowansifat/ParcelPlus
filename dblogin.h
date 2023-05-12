#ifndef DBLOGIN_H
#define DBLOGIN_H

#include <QDialog>

namespace Ui {
class dblogin;
}

class dblogin : public QDialog
{
    Q_OBJECT

public:
    explicit dblogin(QWidget *parent = nullptr);
    ~dblogin();

private:
    Ui::dblogin *ui;
};

#endif // DBLOGIN_H
