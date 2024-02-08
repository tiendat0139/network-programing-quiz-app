#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <ctime>
#include <sstream>
#include <thread>

#include "PracticeController.hpp"
#include "ServerManager.hpp"
#include "../comunicate/server.h"
#include "../request/practice.h"
#include "../request/question.h"
#include "../../Model/Room.hpp"
#include "../../Model/Question.hpp"
#include "../../Model/Answer.hpp"
#include "../../Model/UserRoom.hpp"
#include "../../Model/RoomQuestion.hpp"

void countdownClockPractice(int minutes, int room_id);
PracticeController::PracticeController() = default;

void PracticeController::redriect(json request, int clientfd)
{
    std::string url = request["url"];

    if (url == RequestCreatePracticeRouter)
    {
        create(request, clientfd);
    }
    else if (url == RequestStartPracticeRouter)
    {
        start(request, clientfd);
    }
    else if (url == RequestEndPracticeRouter)
    {
        end(request, clientfd);
    }
}

void PracticeController::create(json request, int clientfd)
{
    int auth_id = request["header"]["id"];
    int category_id = request["body"]["category_id"];
    std::string name = request["body"]["name"];
    int time_limit = request["body"]["time_limit"];

    std::vector<UserRoom> usersRoom = relationsUserRoom();
    usersRoom.erase(std::remove_if(usersRoom.begin(), usersRoom.end(),
                                   [auth_id](const UserRoom &userRoom)
                                   {
                                       return userRoom.user_id != auth_id || !userRoom.is_owner;
                                   }),
                    usersRoom.end());

    std::vector<RoomQuestion> roomQuestions = relationsRoomQuestion();
    std::vector<Room> rooms;
    for (auto &u_r : usersRoom)
    {
        Room r = Room::findById(u_r.room_id);
        if (r.type == ROOM_PRACTICE_TYPE)
        {
            rooms.push_back(r);
        }
    }

    std::vector<Room> roomsTarget;
    for (auto &r : rooms)
    {
        std::vector<RoomQuestion> filteredRoomsQuestion;
        int r_id = r.id;
        std::copy_if(roomQuestions.begin(), roomQuestions.end(), std::back_inserter(filteredRoomsQuestion),
                     [r_id](const RoomQuestion &roomQ)
                     { return roomQ.room_id == r_id; });

        RoomQuestion rq = filteredRoomsQuestion.back();
        Question rCate = Question::findById(rq.question_id);
        if (rCate.category_id == category_id)
        {
            roomsTarget.push_back(r);
        }
    }

    std::vector<Answer> answers;

    std::vector<int> question_config;
    if (!roomsTarget.empty())
    {
        // Find score and increase difficutly
        Room roomLastest = rooms.back();
        int roomLastest_id = roomLastest.id;
        answers.erase(std::remove_if(answers.begin(), answers.end(),
                                     [auth_id, roomLastest_id](const Answer &answer)
                                     {
                                         return answer.room_id != roomLastest_id || answer.user_id != auth_id;
                                     }),
                      answers.end());

        int score1 = 0, score2 = 0, score3 = 0, score4 = 0, score5 = 0;
        for (auto &a : answers)
        {
            switch (a.result)
            {
            case 1:
                score1++;
                break;
            case 2:
                score2++;
                break;
            case 3:
                score3++;
                break;
            case 4:
                score4++;
                break;
            case 5:
                score5++;
                break;
            default:
                break;
            }
        }
        if (score1 == 0)
            score1 = 1;
        if (score2 == 0)
            score2 = 1;
        if (score3 == 0)
            score3 = 1;
        if (score4 == 0)
            score4 = 1;
        if (score5 == 0)
            score5 = 1;

        double temp1 = std::ceil(static_cast<double>(score1) / 0.7);
        double temp2 = std::ceil(static_cast<double>(score2) / 0.7);
        double temp3 = std::ceil(static_cast<double>(score3) / 0.7);
        double temp4 = std::ceil(static_cast<double>(score4) / 0.7);
        double temp5 = std::ceil(static_cast<double>(score5) / 0.7);

        question_config.push_back(static_cast<int>(temp1));
        question_config.push_back(static_cast<int>(temp2));
        question_config.push_back(static_cast<int>(temp3));
        question_config.push_back(static_cast<int>(temp4));
        question_config.push_back(static_cast<int>(temp5));
    }
    else
    {
        for (int i = 0; i < 5; i++)
        {
            question_config.push_back(1);
        }
    }

    std::vector<Question> questions = Question::getAll();
    std::vector<Question> filtered_questions;
    std::copy_if(questions.begin(), questions.end(), std::back_inserter(filtered_questions),
                 [category_id](const Question &q)
                 { return q.category_id == category_id; });

    std::vector<Question> selected_questions;
    int max_score = 0;
    for (size_t i = 0; i < question_config.size(); ++i)
    {
        int level = i + 1;
        int num_questions = question_config[i];
        max_score += num_questions * level;

        std::vector<Question> filtered_by_level;
        std::copy_if(filtered_questions.begin(), filtered_questions.end(), std::back_inserter(filtered_by_level),
                     [level](const Question &q)
                     { return q.level == level; });

        std::random_shuffle(filtered_by_level.begin(), filtered_by_level.end());
        std::copy_n(filtered_by_level.begin(), static_cast<std::size_t>(std::min(static_cast<int>(num_questions), static_cast<int>(filtered_by_level.size()))), std::back_inserter(selected_questions));
    }

    Room roomStore = Room(name, 1, ROOM_PRACTICE_TYPE, "", "", ROOM_LOBBY_STATUS, time_limit, false, "");
    Room::create(roomStore);
    for (const auto &q : selected_questions)
    {
        RoomQuestion rq;
        rq.question_id = q.id;
        rq.room_id = roomStore.id;
        insertRoomQuestion(rq);
    }
    UserRoom urStore;
    urStore.is_owner = true;
    urStore.room_id = roomStore.id;
    urStore.user_id = auth_id;
    insertUserRoom(urStore);

    ResponseCreatePractice response;
    response.status = SUCCESS;
    response.body.category = Category::findById(category_id);
    response.body.question_config = question_config;
    response.body.max_score = max_score;
    response.body.room = roomStore;

    sendToClient(clientfd, response.toJson().dump().c_str());
}

void PracticeController::start(json request, int clientfd)
{
    int room_id = request["param"];

    auto now = std::chrono::system_clock::now();
    std::time_t convertTime = std::chrono::system_clock::to_time_t(now);
    std::stringstream formattedTime;
    formattedTime << std::put_time(std::localtime(&convertTime), "%Y-%m-%d %H:%M:%S");

    Room r = Room::findById(room_id);
    r.status = ROOM_DOING_STATUS;
    r.start_time = formattedTime.str();
    Room room = Room::edit(r);

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

    // Start Clock thread
    std::thread clockThreadPractice(countdownClockPractice, r.time_limit, room_id);
    clockThreadPractice.detach();

    ResponseStartPractice response;
    response.body.room = r;
    response.body.questions = questionsExam;
    response.status = SUCCESS;

    sendToClient(clientfd, response.toJson().dump().c_str());

}

void PracticeController::end(json request, int clientfd)
{
    int room_id = request["param"];

    auto now = std::chrono::system_clock::now();
    std::time_t convertTime = std::chrono::system_clock::to_time_t(now);
    std::stringstream formattedTime;
    formattedTime << std::put_time(std::localtime(&convertTime), "%Y-%m-%d %H:%M:%S");

    Room room = Room::findById(room_id);
    ResponseEndPractice response;
    if(room.type == ROOM_PRACTICE_TYPE) {
        room.status = ROOM_CLOSE_STATUS;
        room.close_time = formattedTime.str();
        Room::edit(room);

        response.status = SUCCESS;
        response.message = "Submit practice room success";
    }
    sendToClient(clientfd, response.toJson().dump().c_str());
}

void countdownClockPractice(int minutes, int room_id)
{
    auto duration = std::chrono::minutes(minutes);

    pthread_mutex_lock(&ServerManager::mutex);
    ServerManager::roomsActiveClock.push_back(room_id);
    pthread_mutex_unlock(&ServerManager::mutex);

    std::this_thread::sleep_for(duration);

    pthread_mutex_lock(&ServerManager::mutex);
    ServerManager::roomsActiveClock.erase(std::remove(ServerManager::roomsActiveClock.begin(), ServerManager::roomsActiveClock.end(), room_id),
                                          ServerManager::roomsActiveClock.end());
    pthread_mutex_unlock(&ServerManager::mutex);

    auto now = std::chrono::system_clock::now();
    std::time_t convertTime = std::chrono::system_clock::to_time_t(now);
    std::stringstream formattedTime;
    formattedTime << std::put_time(std::localtime(&convertTime), "%Y-%m-%d %H:%M:%S");

    Room room = Room::findById(room_id);
    room.status = ROOM_CLOSE_STATUS;
    room.close_time = formattedTime.str();
    Room::edit(room);
}
