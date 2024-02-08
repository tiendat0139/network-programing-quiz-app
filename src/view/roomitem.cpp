#include "roomitem.h"
#include "ui_roomitem.h"

#include <QDebug>
#include <QDateTime>

RoomItem::RoomItem(QWidget *parent, int roomId, const QString& name,
                   int capacity, int time_limit, const QString& start_time, bool isPrivate) :
    QWidget(parent),
    ui(new Ui::RoomItem),
    roomId(roomId),
    isPrivate(isPrivate)
{
    ui->setupUi(this);
    ui->nameLabel->setText(name);
    ui->capacityLabel->setText(QString::number(capacity));
    ui->timeLimitLabel->setText(QString::number(time_limit));

    QDateTime currentDateTime = QDateTime::currentDateTime();

    if(start_time == "") {
        ui->startTimeLabel->setText(currentDateTime.toString("yyyy-MM-dd"));
    } else {
        ui->startTimeLabel->setText(start_time);
    }

    if (!isPrivate) ui->lockLabel->hide();
}

void RoomItem::on_joinPushButton_clicked()
{
    emit joinPushButton_clicked(roomId, isPrivate);
}

RoomItem::~RoomItem()
{
    delete ui;
}

