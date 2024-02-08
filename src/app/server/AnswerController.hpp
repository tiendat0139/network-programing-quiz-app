#ifndef ANSWERCONTROLLER_HPP
#define ANSWERCONTROLLER_HPP

#include "../../../library/json.hpp"

using json = nlohmann::json;

class AnswerController
{
public:
    AnswerController();

    void redriect(json request, int clientfd);
    void submit(json request, int clientfd);
};

#endif