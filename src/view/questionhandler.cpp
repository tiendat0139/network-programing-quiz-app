#include "questionhandler.h"
#include "../app/comunicate/client.h"
#include "clientmanager.h"

QuestionHandler::QuestionHandler() {}

void QuestionHandler::requestCreateQuestion(RequestCreateQuestionBody body)
{
    RequestCreateQuestion request;
    request.header = ClientManager::authUser;
    request.body = body;

    sendToServer(request.toJson().dump().c_str());
}

json QuestionHandler::responseCreateQuestion()
{
    char buff[BUFF_SIZE];
    recvFromServer(buff);

    return json::parse(buff);
}

void QuestionHandler::requestGetQuestionByRoom(int room_id)
{
    RequesGetQuestionByRoom request;
    request.header = ClientManager::authUser;
    request.room_id = room_id;

    sendToServer(request.toJson().dump().c_str());
}

json QuestionHandler::responseGetQuestionByRoom()
{
    char buff[BUFF_SIZE];
    recvFromServer(buff);

    return json::parse(buff);
}

void QuestionHandler::requestGetQuestionByCategory(int category_id)
{
    RequestGetQuestionByCategory request;
    request.header = ClientManager::authUser;
    request.category_id = category_id;

    sendToServer(request.toJson().dump().c_str());
}

json QuestionHandler::responseGetQuestionByCategory()
{
    char buff[BUFF_SIZE];
    recvFromServer(buff);

    return json::parse(buff);
}

void QuestionHandler::requestDeleteQuestion(int question_id)
{
    RequestDeleteQuestion request;
    request.header = ClientManager::authUser;
    request.question_id = question_id;

    sendToServer(request.toJson().dump().c_str());
}

json QuestionHandler::responseDeleteQuestion()
{
    char buff[BUFF_SIZE];
    recvFromServer(buff);

    return json::parse(buff);
}

void QuestionHandler::requestConfigQuestion()
{
    RequestConfigQuestion request;
    request.header = ClientManager::authUser;

    sendToServer(request.toJson().dump().c_str());
}

json QuestionHandler::responseConfigQuestion()
{
    char buff[BUFF_SIZE];
    recvFromServer(buff);

    return json::parse(buff);
}
