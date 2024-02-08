#include <iostream>
#include <vector>
#include <algorithm>

#include "AnswerController.hpp"
#include "ServerManager.hpp"
#include "../comunicate/server.h"
#include "../request/answer.h"
#include "../../Model/Question.hpp"
#include "../../Model/Option.hpp"
#include "../../Model/Answer.hpp"

AnswerController::AnswerController() = default;

void AnswerController::redriect(json request, int clientfd)
{
    std::string url = request["url"];

    if (url == RequestSubmitAnswerRouter)
    {
        submit(request, clientfd);
    }
}

void AnswerController::submit(json request, int clientfd)
{
    std::vector<Answer> answers = Answer::getAll();
    int auth_id = request["header"]["id"];
    int room_id = request["body"]["room_id"];
    int question_id = request["body"]["question_id"];
    int option_id = request["body"]["option_id"];

    pthread_mutex_lock(&ServerManager::mutex);
    std::vector<int> roomsActiveClock = ServerManager::roomsActiveClock;
    pthread_mutex_unlock(&ServerManager::mutex);

    ResponseSubmitAnswer response;
    auto it = std::find(roomsActiveClock.begin(), roomsActiveClock.end(), room_id);
    if (it == roomsActiveClock.end())
    {
        response.status = FAILURE;
        response.body.message = "Exam timeout! Cannot submit";
        response.body.option_id = -1;
        response.body.room_id = -1;
        response.body.room_id = -1;
        sendToClient(clientfd, response.toJson().dump().c_str());
    }
    else
    {
        Question question = Question::findById(question_id);
        Option option = Option::findById(option_id);

        int result = 0;
        if (option.correct == true)
        {
            result = question.level;
        }

        answers.erase(std::remove_if(answers.begin(), answers.end(),
                                     [auth_id, room_id, question_id](const Answer &answer)
                                     {
                                         return answer.user_id != auth_id ||
                                                answer.room_id != room_id ||
                                                answer.question_id != question_id;
                                     }),
                      answers.end());

        if (answers.empty())
        {
            Answer a = Answer(auth_id, room_id, question_id, option_id, result);
            Answer::create(a);
        }
        else
        {
            for (Answer &answer : answers)
            {
                answer.option_id = option_id;
                answer.result = result;
                Answer::edit(answer);
            }
        }

        response.status = SUCCESS;
        response.body.message = "Answer saved successfully";
        response.body.room_id = room_id;
        response.body.question_id = question_id;
        response.body.option_id = option_id;

        sendToClient(clientfd, response.toJson().dump().c_str());
    }
}