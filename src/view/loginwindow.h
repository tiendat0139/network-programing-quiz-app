#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_loginPushButton_clicked();

    void on_registerPushButton_clicked();

    void on_registerPushButton_2_clicked();

    void on_loginPushButton_2_clicked();

private:
    Ui::LoginWindow *ui;
};

#endif // LOGINWINDOW_H
