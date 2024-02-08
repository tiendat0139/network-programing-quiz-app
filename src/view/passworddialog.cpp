#include "passworddialog.h"
#include "ui_passworddialog.h"
#include "animations.h"

#include "createroomdialog.h"
#include "ui_createroomdialog.h"
#include "../app/request/room.h"
#include "roomhandler.h"

#include <QString>
#include <QDialog>
#include <QDebug>
#include <iostream>

PasswordDialog::PasswordDialog(QWidget *parent, int roomId,
                               bool is_private) :
    QDialog(parent),
    ui(new Ui::PasswordDialog),
    roomId(roomId),
    isPrivate(is_private)
{
    setModal(true);
    ui->setupUi(this);
    setWindowTitle("Room Password");
}

void PasswordDialog::on_submitPushButton_clicked()
{
    QString enteredPassword = ui->passwordLineEdit->text();

    if(!enteredPassword.isEmpty()) {
        RoomHandler roomHandler;
        roomHandler.requestJoinRoom(roomId, isPrivate, enteredPassword.toStdString());

        json joinRes = roomHandler.responseJoinRoom();

        if(joinRes["status"] == SUCCESS) {
            accept();
        } else {
            Animations::moveBothX(ui->lockIcon, 50, 20);
        }
    } else {
        Animations::moveBothX(ui->lockIcon, 50, 20);
    }
}

PasswordDialog::~PasswordDialog()
{
    delete ui;
}


