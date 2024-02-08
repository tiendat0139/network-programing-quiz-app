#include "roompassword.h"
#include "ui_roompassword.h"

#include <QDialog>

RoomPassword::RoomPassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RoomPassword)
{
    setModal(true);
    ui->setupUi(this);
}

void RoomPassword::on_closeModalPushButton_clicked()
{
  this->hide();
}


RoomPassword::~RoomPassword()
{
    delete ui;
}

