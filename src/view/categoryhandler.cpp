#include "categoryhandler.h"
#include "../app/comunicate/client.h"
#include "../app/request/category.h"
#include "../../library/json.hpp"
#include "clientmanager.h"

CategoryHandler::CategoryHandler() {}

void CategoryHandler::requestListCategory()
{
    RequestListCategory requestListCategory;
    requestListCategory.header = ClientManager::authUser;
    sendToServer(requestListCategory.toJson().dump().c_str());
}

json CategoryHandler::responseListCategory()
{
    char buff[BUFF_SIZE];
    recvFromServer(buff);

    return json::parse(buff);
}
