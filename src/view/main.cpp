#include "loginwindow.h"
#include "mainwindow.h"
#include "createroomdialog.h"
#include "clientmanager.h"
#include "examwindow.h"
#include "addquestiondialog.h"
#include "adminwindow.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int client_sock;
    struct sockaddr_in server_addr; /* server's address information */
    int bytes_sent;
    int bytes_received;

    // Step 1: Construct socket
    client_sock = socket(AF_INET, SOCK_STREAM, 0);

    // Step 2: Specify server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);

    // Step 3: Request to connect server
    if (connect(client_sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) < 0)
    {
        printf("\nError!Can not connect to sever! Client exit immediately! ");
        return 0;
    }

    ClientManager::client_sock = client_sock;
    LoginWindow l;
//    MainWindow m;
//    ExamWindow e;
//      CreateRoom cr;
//    PasswordDialog pd;
//    CreateRoomDiaLog crd;
//      AdminWindow aw;
//    AddQuestionDiaLog aqd;
//    CreatePracticeDiaLog cpd;

//    m.show();
     l.show();
//    e.show();
//    lb.show();
//      cr.show();
//    crd.show();
//    pd.show();
//      aw.show();
//    aqd.show();
//    cpd.show();

    return a.exec();
}
