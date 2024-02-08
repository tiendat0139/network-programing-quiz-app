#include "client.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <chrono>
#include <ctime>
#include <sstream>
#include <fstream>

#include "../../view/clientmanager.h"

void logClient(const char *buff, bool flag)
{
    auto now = std::chrono::system_clock::now();
    std::time_t convertTime = std::chrono::system_clock::to_time_t(now);
    std::stringstream formattedTime;
    formattedTime << std::put_time(std::localtime(&convertTime), "%Y-%m-%d %H:%M:%S");
    std::string nowTime = formattedTime.str();

    std::ofstream logFile("/home/tiendat/v1/src/app/comunicate/client_log.txt", std::ios::app);
    if (!logFile.is_open())
    {
        perror("Error: Cannot open file log!");
        return;
    }

    if (flag)
    {
        json data = json::parse(buff);
        std::string code = data["code"];
        std::string url = data["url"];
        std::string status;
        std::string message;

        auto statusIt = data.find("status");
        if (statusIt != data.end()) {
            status = statusIt.value();
        } else {
            status = " ";
        }
        auto messageIt = data["body"].find("message");
        if (messageIt != data["body"].end()) {
            message = messageIt.value();
        } else {
            message = " ";
        }

        logFile << nowTime << " " << code << " " << url << " " << status << " " << message << std::endl;
    } else
    {
        logFile << nowTime << " " << buff << std::endl;
    }
    logFile.close();
}

int sendToServer(const char *buff)
{
    int sendBytes = 0;
    sendBytes = send(ClientManager::client_sock, buff, strlen(buff), 0);

    if (sendBytes <= 0)
    {
        logClient("Error: Cannot send data to server!", false);
        perror("Error: Cannot send data to server!");
        ClientManager::close_client_sock();
        exit(0);
    }
    logClient(buff, true);

    return sendBytes;
}

int recvFromServer(char *buff)
{
    int rcvBytes = 0;
    rcvBytes = recv(ClientManager::client_sock, buff, BUFF_SIZE - 1, 0);

    if (rcvBytes <= 0)
    {
        logClient("Error: Cannot received data from server!", false);
        perror("Error: Cannot received data from server!");
        close(ClientManager::client_sock);
        exit(0);
    }
    buff[rcvBytes] = '\0';
    logClient(buff, true);

    return rcvBytes;
}
