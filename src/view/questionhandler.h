#ifndef QUESTIONHANDLER_H
#define QUESTIONHANDLER_H

#include "../../library/json.hpp"
#include "../app/request/question.h"

using json = nlohmann::json;

class QuestionHandler
{
public:
    QuestionHandler();

    void requestCreateQuestion(RequestCreateQuestionBody body);
    json responseCreateQuestion();

    void requestGetQuestionByRoom(int room_id);
    json responseGetQuestionByRoom();

    void requestGetQuestionByCategory(int category_id);
    json responseGetQuestionByCategory();

    void requestDeleteQuestion(int question_id);
    json responseDeleteQuestion();

    void requestConfigQuestion();
    json responseConfigQuestion();
};

#endif // QUESTIONHANDLER_H
