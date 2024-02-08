#include "practicehandler.h"
#include "../app/comunicate/client.h"
#include "../app/request/practice.h"
#include "../../library/json.hpp"
#include "clientmanager.h"

PracticeHandler::PracticeHandler() {}

void PracticeHandler::requestCreatePractice(int category_id, std::string name, int time_limit)
{
    RequestCreatePractice request;
    request.header = ClientManager::authUser;
    request.body.category_id = category_id;
    request.body.name = name;
    request.body.time_limit = time_limit;

    sendToServer(request.toJson().dump().c_str());
}

json PracticeHandler::responseCreatePractice()
{
    char buff[BUFF_SIZE];
    recvFromServer(buff);

    return json::parse(buff);
}

void PracticeHandler::requestStartPractice(int room_id)
{
    RequestStartPractice request;
    request.header = ClientManager::authUser;
    request.param = room_id;

    sendToServer(request.toJson().dump().c_str());
}

json PracticeHandler::responseStartPractice()
{
    char buff[BUFF_SIZE];
    recvFromServer(buff);

    return json::parse(buff);
}

void PracticeHandler::requestEndPractice(int room_id)
{
    RequestEndPractice request;
    request.header = ClientManager::authUser;
    request.param = room_id;

    sendToServer(request.toJson().dump().c_str());
}

json PracticeHandler::responseEndPractice()
{
    char buff[BUFF_SIZE];
    recvFromServer(buff);

    return json::parse(buff);
}

