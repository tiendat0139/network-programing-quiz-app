#include "UserController.hpp"

#include "../comunicate/server.h"
#include "../request/user.h"
#include "../../Model/User.hpp"
#include "ServerManager.hpp"

UserController::UserController() = default;

void UserController::redriect(json request, int clientfd)
{
    std::string url = request["url"];
    if (url == RequestListUserRouter)
    {
        list(request, clientfd);
    }
    else if (url == RequestActiveUserRouter)
    {
        active(request, clientfd);
    }
    else if (url == RequestDeleteUserRouter)
    {
        Delete(request, clientfd);
    }
}

void UserController::list(json request, int clientfd)
{
    std::vector<User> users = User::getAll();
    users.erase(std::remove_if(users.begin(), users.end(),[](const User& user) { return user.role == "Admin"; }), users.end());

    ResponseListUser response;
    response.status = SUCCESS;
    response.body.users = users;
    response.body.message = "Get list users success";

    sendToClient(clientfd, response.toJson().dump().c_str());
}

void UserController::active(json request, int clientfd)
{
    int user_id = request["param"];
    bool active = request["active"];

    User user = User::findById(user_id);
    if (active)
    {
        user.status = 1;
    } else
    {
        user.status = 0;
    }
    User::edit(user);

    ResponseActiveUser response;
    response.status = SUCCESS;
    response.body.user = user;
    response.body.message = "Edit user status success";

    sendToClient(clientfd, response.toJson().dump().c_str());
}

void UserController::Delete(json request, int clientfd)
{
    int user_id = request["param"];
    User user = User::findById(user_id);
    User::Delete(user);

    ResponseDeleteUser response;
    response.status = SUCCESS;
    response.message = "Delete user success";

    sendToClient(clientfd, response.toJson().dump().c_str());
}
