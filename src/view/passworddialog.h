#ifndef PASSWORDDIALOG_H
#define PASSWORDDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class PasswordDialog;
}

class PasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PasswordDialog(QWidget *parent = nullptr, int roomId = 0,
                            bool is_private = false);
    ~PasswordDialog();

private slots:
    void on_submitPushButton_clicked();

private:
    Ui::PasswordDialog *ui;
    int roomId;
    bool isPrivate;
    bool isRoomOwner;
};

#endif // PASSWORDDIALOG_H
