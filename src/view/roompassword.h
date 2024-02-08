#ifndef ROOMPASSWORD_H
#define ROOMPASSWORD_H

#include <QDialog>

namespace Ui {
class RoomPassword;
}

class RoomPassword : public QDialog
{
    Q_OBJECT

public:
    explicit RoomPassword(QWidget *parent = nullptr);
    ~RoomPassword();

private slots:
    void on_closeModalPushButton_clicked();

private:
    Ui::RoomPassword *ui;
};

#endif // ROOMPASSWORD_H
