#ifndef CREATEROOM_H
#define CREATEROOM_H

#include <QMainWindow>

namespace Ui {
class CreateRoom;
}

class CreateRoom : public QMainWindow
{
    Q_OBJECT

public:
    explicit CreateRoom(QWidget *parent = nullptr);
    ~CreateRoom();

private slots:
    void on_nextButton_clicked();

    void on_createButton_clicked();

    void on_backButton_clicked();

    void on_privateRadioButton_clicked();

    void on_closeModalPushButton_clicked();

private:
    Ui::CreateRoom *ui;
};

#endif // CREATEROOM_H
