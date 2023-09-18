#ifndef ADMINUI_H
#define ADMINUI_H

#include <QDialog>

namespace Ui {
class adminui;
}

class adminui : public QDialog
{
    Q_OBJECT

public:
    explicit adminui(QWidget *parent = nullptr);
    ~adminui();

private:
    Ui::adminui *ui;
};

#endif // ADMINUI_H
