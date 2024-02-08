#include "lobbywindow.h"
#include "ui_lobbywindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>

LobbyWindow::LobbyWindow(QWidget *parent, const QString &room_id) :
    QMainWindow(parent),
    ui(new Ui::LobbyWindow)
{
    ui->setupUi(this);
    ui->examNameLabel->setText(room_id);

    QVBoxLayout *userList = ui->userList;
    userList->setAlignment(Qt::AlignTop);
    userList->addWidget(createUserItem());
}

QWidget* LobbyWindow::createUserItem()
{
    QWidget* container = new QWidget;

    QHBoxLayout* userLayout = new QHBoxLayout(container);
    QLabel* idLabel = new QLabel(QString("1"));
    idLabel->setStyleSheet("font-family: Source Sans 3; "
                           "max-width: 75px; "
                           "min-width: 75px; "
                           "max-height: 60px; ");
    QLabel* nameLabel = new QLabel(QString("Nguyen Tien Dat"));
    nameLabel->setStyleSheet("font-family: Source Sans 3; "
                             "max-width: 290px; "
                             "min-width: 290px; ");
    QLabel* pointLabel = new QLabel(QString("1200"));
    pointLabel->setStyleSheet("font-family: Source Sans 3;");

    userLayout->addWidget(idLabel);
    userLayout->addWidget(nameLabel);
    userLayout->addWidget(pointLabel);

    container->setLayout(userLayout);
    container->setStyleSheet("background-color: #fff; "
                             "border-radius: 8px; ");
    return container;
}

LobbyWindow::~LobbyWindow()
{
    delete ui;
}
