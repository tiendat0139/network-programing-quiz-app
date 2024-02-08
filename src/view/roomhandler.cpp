#include "roomhandler.h"
#include "../app/comunicate/client.h"
#include "../app/request/room.h"
#include "../../library/json.hpp"
#include "clientmanager.h"

using json = nlohmann::json;

RoomHandler::RoomHandler() {}

void RoomHandler::requestListRoom(std::vector<int> categories, std::string name_search)
{
    RequestListRoom requestListRoom;
    requestListRoom.header = ClientManager::authUser;
    requestListRoom.body.categories = categories;
    requestListRoom.body.name_search = name_search;
    sendToServer(requestListRoom.toJson().dump().c_str());
}

json RoomHandler::responseListRoom()
{
    char buff[BUFF_SIZE];
    recvFromServer(buff);

    return json::parse(buff);
}

void RoomHandler::requestJoinRoom(int room_id, bool is_private, std::string password)
{
    RequestJoinRoom request;
    request.header = ClientManager::authUser;
    request.param = room_id;
    request.body.is_private = is_private;
    request.body.password = password;
    sendToServer(request.toJson().dump().c_str());
}

json RoomHandler::responseJoinRoom()
{
    char buff[BUFF_SIZE];
    recvFromServer(buff);

    return json::parse(buff);
}

void RoomHandler::requestReadyRoom(int room_id)
{
    RequestReadyRoom request;
    request.header = ClientManager::authUser;
    request.param = room_id;
    sendToServer(request.toJson().dump().c_str());
}
json RoomHandler::responseReadyRoom()
{
    char buff[BUFF_SIZE];
    recvFromServer(buff);

    return json::parse(buff);
}

void RoomHandler::requestUnReadyRoom(int room_id)
{
    RequestUnReadyRoom request;
    request.header = ClientManager::authUser;
    request.param = room_id;
    sendToServer(request.toJson().dump().c_str());
}

json RoomHandler::responseUnReadyRoom()
{
    char buff[BUFF_SIZE];
    recvFromServer(buff);

    return json::parse(buff);
}

void RoomHandler::requestStartRoom(int room_id)
{
    RequestStartRoom request;
    request.header = ClientManager::authUser;
    request.body.room_id = room_id;
    sendToServer(request.toJson().dump().c_str());
}

json RoomHandler::responseStartRoom()
{
    char buff[BUFF_SIZE];
    recvFromServer(buff);

    return json::parse(buff);
}

void RoomHandler::requestCreateRoom(RequestCreateRoomBody body, QuestionsExam questions_exam)
{

    RequestCreateRoom request;
    request.header = ClientManager::authUser;
    request.body = body;
    request.questions_exam = questions_exam;

    sendToServer(request.toJson().dump().c_str());
}

json RoomHandler::responseCreateRoom()
{
    char buff[BUFF_SIZE];
    recvFromServer(buff);

    return json::parse(buff);
}

void RoomHandler::requestDetailRoom(int room_id)
{
    ResquestDetailRoom request;
    request.header = ClientManager::authUser;
    request.param = room_id;
    sendToServer(request.toJson().dump().c_str());
}

json RoomHandler::responseDetailRoom()
{
    char buff[BUFF_SIZE];
    recvFromServer(buff);

    return json::parse(buff);
}

void RoomHandler::requestListRoomOwner()
{
    RequestListRoomOwner request;
    request.header = ClientManager::authUser;
    sendToServer(request.toJson().dump().c_str());
}

json RoomHandler::responseListRoomOwner()
{
    char buff[BUFF_SIZE];
    recvFromServer(buff);

    return json::parse(buff);
}


