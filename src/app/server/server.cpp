#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <openssl/sha.h>
#include <pthread.h>
#include <fstream>

#include "AuthController.hpp"
#include "RoomController.hpp"
#include "CategoryController.hpp"
#include "AnswerController.hpp"
#include "QuestionController.hpp"
#include "ResultController.hpp"
#include "PracticeController.hpp"
#include "UserController.hpp"
#include "../comunicate/server.h"
#include "../request/route.h"
#include "ServerManager.hpp"

#define BACKLOG 5

std::vector<int> listClientFd;

void *client_handler(void *arg)
{
    int clientfd;

    pthread_detach(pthread_self());
    clientfd = *((int *)arg);

    pthread_mutex_lock(&ServerManager::mutex);
    pthread_mutex_unlock(&ServerManager::mutex);

    free(arg);

    while (1)
    {
        char buff[BUFF_SIZE];

        int recvBytes = recvFromClient(clientfd, buff);
        if(recvBytes == -1) break;
        
        if (strcmp(buff, "\0") == 0) {
            break;
        }
        json request = json::parse(buff);
        std::string code = request["code"];
        std::string url = request["url"];
        if (url == RequestLoginRouter)
        {
            AuthController loginController = AuthController();
            loginController.login(request, clientfd);
        } else if (url == RequestRegistrationRouter) {
            AuthController signupController = AuthController();
            signupController.signup(request, clientfd);
        } else {
            if (url == RequestLogoutRouter )
            {
                AuthController logout = AuthController();
                logout.logout(request, clientfd);
            }

            if (url.find("/room/") != std::string::npos)
            {
                RoomController roomController;
                roomController.redriect(request, clientfd);
            }

            if (url.find("/category/") != std::string::npos)
            {
                CategoryController categoryController;
                categoryController.redriect(request, clientfd);
            }

            if (url.find("/answer/") != std::string::npos)
            {
                AnswerController answerController;
                answerController.redriect(request, clientfd);
            }

            if (url.find("/question/") != std::string::npos) {
                QuestionController questionController;
                questionController.redirect(request, clientfd);
            }

            if (url.find("/result/") != std::string::npos)
            {
                ResultController resultController;
                resultController.redriect(request, clientfd);
            }

            if (url.find("/practice/") != std::string::npos)
            {
                PracticeController practiceController;
                practiceController.redriect(request, clientfd);
            }

            if (url.find("/user/") != std::string::npos)
            {
                UserController userController;
                userController.redriect(request, clientfd);
            }

        }

    }
    pthread_mutex_lock(&ServerManager::mutex);
    ServerManager::client_auth.erase(std::remove_if(ServerManager::client_auth.begin(), ServerManager::client_auth.end(),
                             [clientfd](std::unordered_map<int, int>& clientUserMap) {
                                 return clientUserMap.find(clientfd) != clientUserMap.end();
                             }),
                ServerManager::client_auth.end());
    pthread_mutex_unlock(&ServerManager::mutex);
    close(clientfd);
}

int main(int argc, char const *argv[])
{
    if (argc <= 1)
    {
        printf("PortNumber is required. Pleae enter PortNumber\n");
        return 0;
    }
    else if (argc >= 3)
    {
        printf("Enter only one PortNumber\n");
        return 0;
    }

    int listenfd;
    int *connfd;
    struct sockaddr_in server;
    struct sockaddr_in client;
    socklen_t sin_size;
    pthread_t tid;

    // Construct a TCP socket to listen connection request
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("\nError: ");
        return 0;
    }

    // Bind address to socket
    memset(&server, '\0', sizeof server);
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[1]));
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(listenfd, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        perror("\nError: ");
        return 0;
    }

    // Listen request from client
    if (listen(listenfd, BACKLOG) == -1)
    {
        perror("\nError: ");
        return 0;
    }

    // Communicate with client
    while (1)
    {
        connfd = (int*)malloc(sizeof(int));
        sin_size = sizeof(struct sockaddr_in);
        if ((*connfd = accept(listenfd, (struct sockaddr *)&client, &sin_size)) == -1)
            perror("\nError: ");
        printf("You got a connection from %s\n", inet_ntoa(client.sin_addr)); /* prints client's IP */

        pthread_create(&tid, NULL, &client_handler, connfd);
    }

    close(listenfd);
    return 0;
}
