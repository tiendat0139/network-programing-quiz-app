#ifndef ANSWERHANDLER_H
#define ANSWERHANDLER_H

#include "../../library/json.hpp"

using json = nlohmann::json;

class AnswerHandler
{
public:
    AnswerHandler();

    void requestSubmitAnswer(int room_id, int question_id, int option_id);
    json responseSubmitAnswer();
};

#endif // ANSWERHANDLER_H
