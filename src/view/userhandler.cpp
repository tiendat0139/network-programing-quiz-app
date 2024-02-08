#include "userhandler.h"
#include "../app/comunicate/client.h"
#include "../app/request/user.h"
#include "../../library/json.hpp"
#include "clientmanager.h"

UserHandler::UserHandler()
{

}

void UserHandler::requestListUser()
{
    RequestListUser requestListUser;
    requestListUser.header = ClientManager::authUser;
    sendToServer(requestListUser.toJson().dump().c_str());
}

json UserHandler::responseListUser()
{
    char buff[BUFF_SIZE];
    recvFromServer(buff);

    return json::parse(buff);
}

void UserHandler::requestDeleteUser(int userId)
{
    RequestDeleteUser requestDeleteUser;
    requestDeleteUser.param = userId;
    requestDeleteUser.header = ClientManager::authUser;
    sendToServer(requestDeleteUser.toJson().dump().c_str());
}

json UserHandler::responseDeleteUser()
{
    char buff[BUFF_SIZE];
    recvFromServer(buff);

    return json::parse(buff);
}

void UserHandler::requestActiveUser(int userId, bool active)
{
    RequestActiveUser requestActiveUser;
    requestActiveUser.param = userId;
    requestActiveUser.active = active;
    requestActiveUser.header = ClientManager::authUser;
    sendToServer(requestActiveUser.toJson().dump().c_str());
}

json UserHandler::responseActiveUser()
{
    char buff[BUFF_SIZE];
    recvFromServer(buff);

    return json::parse(buff);
}
