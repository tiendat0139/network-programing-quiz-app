#include "AuthController.hpp"

#include <vector>
#include <unordered_map>
#include <algorithm>

#include "../request/login.h"
#include "../request/logout.h"
#include "../request/registration.h"
#include "../comunicate/server.h"
#include "../../Model/User.hpp"
#include "ServerManager.hpp"
#include "../helper.hpp"
 
std::vector<User> loggedUsers;

AuthController::AuthController() = default;

void AuthController::login(json request, int clientfd)
{
    std::string code = request["code"];
    std::string url = request["url"];
    std::string header = request["header"];
    std::string email = request["body"]["email"];
    std::string password = request["body"]["password"];

    User user = User::findByEmail(email);
    ResponseLogin responseLogin;

    if (user.email.empty())
    {
        responseLogin.status = FAILURE;
        responseLogin.body.message = "Account not exists.";
    }
    else
    {
        std::string hasedPassword = sha256(password);
        if (user.status == 0)
        {
            responseLogin.status = FAILURE;
            responseLogin.body.message = "Account has been locked.";
        }
        else if (hasedPassword != user.password)
        {
            responseLogin.status = FAILURE;
            responseLogin.body.message = "Password incorrect.";
        }
        else if (hasedPassword == user.password)
        {
            pthread_mutex_lock(&ServerManager::mutex);
            auto it = std::find_if(loggedUsers.begin(), loggedUsers.end(),
                                   [&user](const User &userIter)
                                   { return userIter.id == user.id; });
            if (it != loggedUsers.end())
            {
                responseLogin.status = FAILURE;
                responseLogin.body.message = "Account is logged in another location.";
            }
            else
            {
                responseLogin.status = SUCCESS;
                responseLogin.body.message = "Login success!";
                responseLogin.body.user = user;
                loggedUsers.push_back(user);
                ServerManager::client_auth.emplace_back(std::unordered_map<int, int>{{clientfd, user.id}});

            }
            pthread_mutex_unlock(&ServerManager::mutex);
        }
    }

    sendToClient(clientfd, responseLogin.toJson().dump().c_str());
}

void AuthController::logout(json request, int clientfd)
{
    int userId = request["header"]["id"];

    pthread_mutex_lock(&ServerManager::mutex);
    loggedUsers.erase(
        std::remove_if(loggedUsers.begin(), loggedUsers.end(),
                       [userId](const User &user)
                       { return user.id == userId; }),
        loggedUsers.end());

    ServerManager::client_auth.erase(std::remove_if(ServerManager::client_auth.begin(), ServerManager::client_auth.end(),
                             [clientfd](std::unordered_map<int, int>& clientUserMap) {
                                 return clientUserMap.find(clientfd) != clientUserMap.end();
                             }),
                ServerManager::client_auth.end());
    pthread_mutex_unlock(&ServerManager::mutex);

    ResponseLogout responseLogout;
    responseLogout.status = SUCCESS;
    responseLogout.message = "Loggout success!";

    sendToClient(clientfd, responseLogout.toJson().dump().c_str());
}

void AuthController::signup(json request, int clientfd)
{
    std::string name = request["body"]["name"];
    std::string email = request["body"]["email"];
    std::string password = request["body"]["password"];

    std::string hashedPassword = sha256(password);

    User newUser = User(name, email, hashedPassword);
    User::create(newUser);

    ResponseRegistration response;
    response.status = SUCCESS;
    response.body = newUser;

    sendToClient(clientfd, response.toJson().dump().c_str());
}