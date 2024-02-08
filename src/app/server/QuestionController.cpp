#include <iostream>
#include <unordered_map>
#include <vector>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <sstream>

#include "QuestionController.hpp"
#include "RoomController.hpp"
#include "../comunicate/server.h"
#include "../request/room.h"
#include "../../Model/Room.hpp"
#include "../../Model/User.hpp"
#include "../../Model/UserRoom.hpp"
#include "../../Model/RoomQuestion.hpp"
#include "../../Model/Option.hpp"
#include "ServerManager.hpp"

QuestionController::QuestionController() = default;

void QuestionController::redirect(json request, int clientfd)
{
    std::string url = request["url"];
    if (url == RequestCreateQuestionRouter)
    {
        create(request, clientfd);
    }
    else if (url == RequestGetQuestionByRoomRouter)
    {
        getByRoom(request, clientfd);
    }
    else if (url == RequestGetQuestionByCategoryRouter)
    {
        getByCategory(request, clientfd);
    }
    else if (url == RequestUpdateQuestionRouter)
    {
        update(request, clientfd);
    }
    else if (url == RequestDeleteQuestionRouter)
    {
        Delete(request, clientfd);
    }
    else if (url == RequestConfigQuestionRouter)
    {
        config(request, clientfd);
    }
}

void QuestionController::create(json request, int clientfd)
{
    std::string title = request["body"]["title"];
    int category_id = request["body"]["category_id"];
    int level = request["body"]["level"];

    // create new with auto increase id and save to database
    Question newQues = Question(title, level, category_id);
    Question::create(newQues);

    for (const auto &o : request["body"]["options"])
    {
        std::string content = o["content"];
        bool correct = o["correct"];
        Option option = Option(newQues.id, content, correct);
        Option::create(option);
    }
    ResponseCreateQuestion response;
    response.status = SUCCESS;
    response.body = newQues;

    sendToClient(clientfd, response.toJson().dump().c_str());
}

void QuestionController::getByRoom(json request, int clientfd)
{
    int room_id = request["room_id"];

    std::vector<RoomQuestion> relationsRQ = relationsRoomQuestion();
    std::vector<QuestionContent> questionsExam;
    std::vector<Option> options = Option::getAll();

    relationsRQ.erase(std::remove_if(relationsRQ.begin(), relationsRQ.end(),
                                     [room_id](const RoomQuestion &r_q)
                                     {
                                         return r_q.room_id != room_id;
                                     }),
                      relationsRQ.end());

    for (RoomQuestion &rq : relationsRQ)
    {
        Question q = Question::findById(rq.question_id);
        int q_id = q.id;
        std::vector<Option> filteredOptions;
        std::copy_if(options.begin(), options.end(), std::back_inserter(filteredOptions),
                     [q_id](const Option &option)
                     {
                         return option.question_id == q_id;
                     });
        QuestionContent qc;
        qc.question = q;
        qc.options = filteredOptions;

        questionsExam.push_back(qc);
    }

    ResponseGetQuestionByRoom response;
    response.status = SUCCESS;
    response.body.questions = questionsExam;
    response.body.message = "Get list question by room success.";

    sendToClient(clientfd, response.toJson().dump().c_str());
}

void QuestionController::getByCategory(json request, int clientfd)
{
    int category_id = request["category_id"];

    std::vector<Question> questions = Question::getAll();
    std::vector<Option> options = Option::getAll();

    questions.erase(std::remove_if(questions.begin(), questions.end(),
                               [category_id](Question &question)
                               { return question.category_id != category_id; }),
                questions.end());

    std::vector<QuestionContent> questionsContents;
    for (auto &q : questions)
    {
        int question_id = q.id;
        std::vector<Option> filtered_options;
        std::copy_if(options.begin(), options.end(), std::back_inserter(filtered_options),
                    [question_id](const Option& o) { return o.question_id == question_id; });

        QuestionContent qc;
        qc.question = q;
        qc.options = filtered_options;
        questionsContents.push_back(qc);
    }
    std::reverse(questionsContents.begin(), questionsContents.end());
    ResponseGetQuestionByCategory response;
    response.body.questions = questionsContents;
    if (questionsContents.empty())
    {
        response.status = FAILURE;
        response.body.message = "No questions data available.";
    } else
    {
        response.status = SUCCESS;
        response.body.message = "Get list question by category success.";
    }

    sendToClient(clientfd, response.toJson().dump().c_str());
}

void QuestionController::update(json request, int clientfd)
{
}

void QuestionController::Delete(json request, int clientfd)
{
    int question_id = request["question_id"];
    Question ques = Question::findById(question_id);
    Question::Delete(ques);

    ResponseDeleteQuestion response;
    response.status = SUCCESS;
    response.body.message = "Delete question success!";

    sendToClient(clientfd, response.toJson().dump().c_str());
}

void QuestionController::config(json request, int clientfd)
{
    int auth_id = request["header"]["id"];

    std::vector<RoomQuestion> room_questions = relationsRoomQuestion();
    std::vector<UserRoom> user_rooms = relationsUserRoom();

    user_rooms.erase(std::remove_if(user_rooms.begin(), user_rooms.end(),
                                    [auth_id](const UserRoom &room)
                                    {
                                        return !(room.user_id == auth_id && room.is_owner);
                                    }),
                     user_rooms.end());

    std::vector<RoomConfigQuestion> roomConfigQuestions;
    for (auto &u_r : user_rooms)
    {
        Room room = Room::findById(u_r.room_id);
        int room_id = room.id;

        std::vector<RoomQuestion> filtered_room_questions;
        std::copy_if(room_questions.begin(), room_questions.end(), std::back_inserter(filtered_room_questions),
                     [room_id](const RoomQuestion &room_question)
                     { return room_question.room_id == room_id; });

        int level1 = 0, level2 = 0, level3 = 0, level4 = 0, level5 = 0;
        for (auto &item : filtered_room_questions)
        {
            Question q = Question::findById(item.question_id);
            switch (q.level)
            {
            case 1:
                level1++;
                break;
            case 2:
                level2++;
                break;
            case 3:
                level3++;
                break;
            case 4:
                level4++;
                break;
            case 5:
                level5++;
                break;
            default:
                break;
            }
        }
        std::vector<int> q_config;
        q_config.push_back(level1);
        q_config.push_back(level2);
        q_config.push_back(level3);
        q_config.push_back(level4);
        q_config.push_back(level5);

        RoomConfigQuestion rcq;
        rcq.room_id = room_id;
        rcq.room_name = room.name;
        rcq.question_config = q_config;

        roomConfigQuestions.push_back(rcq);
    }

    ResponseConfigQuestion response;
    response.body.room_questions = roomConfigQuestions;
    if (roomConfigQuestions.empty())
    {
        response.status = FAILURE;
        response.body.message = "No rooms were created in the past.";
    } else
    {
        response.status = SUCCESS;
        response.body.message = "Get list rooms config questiosn success.";
    }

    sendToClient(clientfd, response.toJson().dump().c_str());
}
