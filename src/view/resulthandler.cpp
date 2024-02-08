#include "resulthandler.h"
#include "../app/comunicate/client.h"
#include "../app/request/result.h"
#include "clientmanager.h"


ResultHandler::ResultHandler() {}

void ResultHandler::requestRoomResult(int room_id)
{
    RequestRoomResult request;
    request.header = ClientManager::authUser;
    request.param = room_id;

    sendToServer(request.toJson().dump().c_str());
}

json ResultHandler::responseRoomResult()
{
    char buff[BUFF_SIZE];
    recvFromServer(buff);

    return json::parse(buff);
}

void ResultHandler::requestHistoryResult()
{
    RequestHistoryResult request;
    request.header = ClientManager::authUser;

    sendToServer(request.toJson().dump().c_str());
}

json ResultHandler::responseHistoryResult()
{
    char buff[BUFF_SIZE];
    recvFromServer(buff);

    return json::parse(buff);
}
