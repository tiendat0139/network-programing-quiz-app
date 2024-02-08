#include "server.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <sstream>
#include <fstream>

#include "../server/ServerManager.hpp"
#include "../../../library/json.hpp"

using json = nlohmann::json;

#define BUFF_SIZE 65536

void logServer(int clientfd, const char *buff, bool flag)
{
    auto now = std::chrono::system_clock::now();
    std::time_t convertTime = std::chrono::system_clock::to_time_t(now);
    std::stringstream formattedTime;
    formattedTime << std::put_time(std::localtime(&convertTime), "%Y-%m-%d %H:%M:%S");
    std::string nowTime = formattedTime.str();

    std::ofstream logFile("../comunicate/server_log.txt", std::ios::app);
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

        logFile << nowTime << " " << clientfd << " " << code << " " << url << " " << status << " " << message << std::endl;
    } else
    {
        logFile << nowTime << " " << clientfd << " " << buff << std::endl;
    }
    logFile.close();
}

int sendToClient(int client_fd, const char *buff)
{
    int sendBytes = 0;
    sendBytes = send(client_fd, buff, strlen(buff), 0);

    if (sendBytes <= 0)
    {
        pthread_mutex_lock(&ServerManager::mutex);
        ServerManager::client_auth.erase(std::remove_if(ServerManager::client_auth.begin(), ServerManager::client_auth.end(),
                             [client_fd](std::unordered_map<int, int>& clientUserMap) {
                                 return clientUserMap.find(client_fd) != clientUserMap.end();
                             }),
                ServerManager::client_auth.end());
        pthread_mutex_unlock(&ServerManager::mutex);

        logServer(client_fd, "Error: Cannot send data to client!", false);
        perror("Error: Cannot send data to client!");
        close(client_fd);
    }
    logServer(client_fd, buff, true);

    return sendBytes;
}

int recvFromClient(int client_fd, char *buff)
{
    int rcvBytes = 0;
    rcvBytes = recv(client_fd, buff, BUFF_SIZE - 1, 0);

    if (rcvBytes <= 0)
    {
        pthread_mutex_lock(&ServerManager::mutex);
        ServerManager::client_auth.erase(std::remove_if(ServerManager::client_auth.begin(), ServerManager::client_auth.end(),
                             [client_fd](std::unordered_map<int, int>& clientUserMap) {
                                 return clientUserMap.find(client_fd) != clientUserMap.end();
                             }),
                ServerManager::client_auth.end());
        pthread_mutex_unlock(&ServerManager::mutex);

        logServer(client_fd, "Error: Cannot received data from client!", false);
        perror("Error: Cannot received data from client!");
        close(client_fd);
        return -1;
    }
    buff[rcvBytes] = '\0';
    logServer(client_fd, buff, true);

    return rcvBytes;
}
