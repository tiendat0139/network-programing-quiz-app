#include "serverlistener.h"


#include "clientmanager.h"
#include "../app/comunicate/client.h"

#include "createroomdialog.h"
#include "ui_createroomdialog.h"
#include "../app/request/room.h"
#include "roomhandler.h"
#include "serverlistener.h"

#include <pthread.h>
#include <QDebug>
#include <QVariant>
#include <iostream>

ServerListener::ServerListener(QObject *parent) : QObject(parent)
{

}
void ServerListener::startListening() {
    char buff[BUFF_SIZE];

    json response;
    while (1) {
        recvFromServer(buff);
        response = json::parse(buff);

        if (response["url"] == ResponseReadyRoomRouter)
        {
            auto users = response["body"]["usersReady"];

            QVector<QPair<QString, QString>> userList;
            for(auto user : users) {
                QString username = QString::fromStdString(user["name"]);
                QString email = QString::fromStdString(user["email"]);
                qDebug() << username << email;
                userList.append(qMakePair(username, email));
            }

            emit serverResponse("userReady", QVariant::fromValue(userList));
            qDebug() << "emit user ready";
        }else if (response["url"] == ResponseUnReadyRoomRouter ) {

        } else if (response["url"] == ResponseStartRoomRouter) {
            std::cout << " -----Start Room ---- "  << std::endl;

            emit serverResponse("start", QVariant());

            break;
        }
    }

}
