#include "useritem.h"
#include "ui_useritem.h"
#include "styles.h"

UserItem::UserItem(QWidget *parent, int index, int user_id, const QString& name, const QString& email, int status) :
    QWidget(parent),
    ui(new Ui::UserItem)
{
    userId = user_id;
    ui->setupUi(this);
    ui->idLabel->setText(QString::number(index));
    ui->nameLabel->setText(name);
    ui->emailLabel->setText(email);
    if(status == 1){
        ui->statusLable->setText("Actived");
        Styles::activeStatus(ui->statusLable);
        ui->unBlockButton->hide();
    }
    if(status == 0){
        ui->statusLable->setText("Blocked");
        Styles::blockStatus(ui->statusLable);
        ui->blockButton->hide();
    }
}

void UserItem::on_deleteButton_clicked()
{
    emit deleteButton_clicked(userId);
}

void UserItem::on_blockButton_clicked()
{
    emit blockButton_clicked(userId);
}

void UserItem::on_unBlockButton_clicked()
{
    emit unBlockButton_clicked(userId);
}

UserItem::~UserItem()
{
    delete ui;
}


