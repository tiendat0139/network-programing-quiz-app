#include "answerhandler.h"
#include "../app/comunicate/client.h"
#include "../app/request/answer.h"
#include "../../library/json.hpp"
#include "clientmanager.h"

AnswerHandler::AnswerHandler() {}

void AnswerHandler::requestSubmitAnswer(int room_id, int question_id, int option_id)
{
    RequestSubmitAnswer request;
    request.header = ClientManager::authUser;
    request.body.room_id = room_id;
    request.body.question_id = question_id;
    request.body.option_id = option_id;

    sendToServer(request.toJson().dump().c_str());
}

json AnswerHandler::responseSubmitAnswer()
{
    char buff[BUFF_SIZE];
    recvFromServer(buff);

    return json::parse(buff);
}
