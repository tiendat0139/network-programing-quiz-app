#include <iostream>
#include <unordered_map>
#include <vector>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <sstream>
#include <thread>

#include "RoomController.hpp"
#include "../comunicate/server.h"
#include "../request/room.h"
#include "../../Model/Room.hpp"
#include "../../Model/User.hpp"
#include "../../Model/UserRoom.hpp"
#include "../../Model/RoomQuestion.hpp"
#include "ServerManager.hpp"
#include "../helper.hpp"

RoomController::RoomController() = default;
void countdownClock(int minutes, int room_id);
bool containsName(const Room &room, const std::string &searchTerm);

std::unordered_map<int, std::vector<int>> usersReady;

void RoomController::redriect(json request, int clientfd)
{
    std::string url = request["url"];

    if (url == RequestRoomListRouter)
    {
        list(request, clientfd);
    }
    else if (url == RequestJoinRoomRouter)
    {
        join(request, clientfd);
    }
    else if (url == RequestRoomOwnerListRouter)
    {
        listOwner(request, clientfd);
    }
    else if (url == RequestReadyRoomRouter)
    {
        ready(request, clientfd);
    }
    else if (url == RequestUnReadyRoomRouter)
    {
        unready(request, clientfd);
    }
    else if (url == RequestStartRoomRouter)
    {
        start(request, clientfd);
    }
    else if (url == RequestCreateRoomRouter)
    {
        create(request, clientfd);
    }
    else if (url == RequestRoomDetailRouter)
    {
        detail(request, clientfd);
    }
}

void RoomController::list(json request, int clientfd)
{
    std::vector<int> categories = request["body"]["categories"];
    std::string name_search = request["body"]["name_search"];
    std::vector<Room> rooms = Room::getAll();
    rooms.erase(std::remove_if(rooms.begin(), rooms.end(),
                               [](Room &room)
                               { return room.status != ROOM_LOBBY_STATUS || room.type != ROOM_EXAM_TYPE; }),
                rooms.end());
    ResponseListRoom response;
    if (categories.size() == 0 && name_search == "")
    {
        response.body.rooms = rooms;
    }
    if (categories.size() == 0 && name_search != "")
    {
        rooms.erase(std::remove_if(rooms.begin(), rooms.end(),
                                   [name_search](const Room &room)
                                   {
                                       return !containsName(room, name_search);
                                   }),
                    rooms.end());
        response.body.rooms = rooms;
    }
    std::vector<RoomQuestion> room_questions = relationsRoomQuestion();
    if (categories.size()!= 0 && name_search == "")
    {
        std::vector<Room> roomsFiltered;
        for (auto &room : rooms)
        {
            RoomQuestion rqFirst;
            for (auto &rq : room_questions)
            {
                if (rq.room_id == room.id)
                {
                    rqFirst = rq;
                    break;
                }
            }
            Question question = Question::findById(rqFirst.question_id);
            if (std::find(categories.begin(), categories.end(), question.category_id) != categories.end())
            {
                roomsFiltered.push_back(room);
            }
        }
        response.body.rooms = roomsFiltered;
    }
    if (categories.size() != 0 && name_search != "")
    {
        std::vector<Room> roomsFiltered;
        for (auto &room : rooms)
        {
            RoomQuestion rqFirst;
            for (auto &rq : room_questions)
            {
                if (rq.room_id == room.id)
                {
                    rqFirst = rq;
                    break;
                }
            }
            Question question = Question::findById(rqFirst.question_id);
            if (std::find(categories.begin(), categories.end(), question.category_id) != categories.end())
            {
                roomsFiltered.push_back(room);
            }
        }
        roomsFiltered.erase(std::remove_if(roomsFiltered.begin(), roomsFiltered.end(),
                                           [name_search](const Room &room)
                                           {
                                               return !containsName(room, name_search);
                                           }),
                            roomsFiltered.end());
        response.body.rooms = roomsFiltered;
    }
    if (response.body.rooms.empty())
    {
        response.status = FAILURE;
        response.body.message = "No matching rooms found";
    }
    else
    {
        response.status = SUCCESS;
        response.body.message = "Get list rooms success.";
    }
    sendToClient(clientfd, response.toJson().dump().c_str());
}

void RoomController::listOwner(json request, int clientfd)
{
    int auth_id = request["header"]["id"];
    std::vector<Room> rooms;
    std::vector<UserRoom> user_rooms = relationsUserRoom();

    user_rooms.erase(std::remove_if(user_rooms.begin(), user_rooms.end(),
                                    [auth_id](UserRoom &ur)
                                    { return ur.user_id != auth_id || ur.is_owner != true; }),
                     user_rooms.end());

    std::vector<Room> roomsOwner;
    for (const auto &u_r : user_rooms)
    {
        Room r = Room::findById(u_r.room_id);
        rooms.push_back(r);
    }

    rooms.erase(std::remove_if(rooms.begin(), rooms.end(),
                               [](Room &room)
                               { return room.status != ROOM_CLOSE_STATUS || room.type != ROOM_EXAM_TYPE; }),
                rooms.end());

    ResponseListRoomOwner response;
    if (rooms.empty())
    {
        response.status = FAILURE;
        response.body.message = "No matching rooms found";
    }
    else
    {
        response.status = SUCCESS;
        response.body.rooms = rooms;
        response.body.message = "Get list rooms owner success";
    }

    sendToClient(clientfd, response.toJson().dump().c_str());
}

void RoomController::join(json request, int clientfd)
{
    int auth_id = request["header"]["id"];
    int room_id = request["param"];
    bool is_private = request["body"]["is_private"];
    std::string password = request["body"]["password"];
    Room room = Room::findById(room_id);
    ResponseJoinRoom response;

    if (is_private && sha256(password) != room.password)
    {
        response.status = FAILURE;
        response.body.message = "Password is incorrect";
        sendToClient(clientfd, response.toJson().dump().c_str());
    }
    else
    {
        bool checkOwner = false;
        std::vector<UserRoom> User_Room = relationsUserRoom();

        checkOwner = std::any_of(User_Room.begin(), User_Room.end(),
                                 [auth_id, room_id](const UserRoom &item)
                                 {
                                     return item.user_id == auth_id &&
                                            item.room_id == room_id &&
                                            item.is_owner;
                                 });
        response.body.is_owner = checkOwner;
        response.body.room = room;
        response.status = SUCCESS;
        response.body.message = "Join room successful!";

        std::vector<User> usersReadyResponse;
        pthread_mutex_lock(&ServerManager::mutex);
        auto it = usersReady.find(room_id);
        if (it != usersReady.end())
        {
            for (auto u_id : it->second)
            {
                usersReadyResponse.push_back(User::findById(u_id));
            }

            response.body.usersReady = usersReadyResponse;
        }

        pthread_mutex_unlock(&ServerManager::mutex);

        sendToClient(clientfd, response.toJson().dump().c_str());
    }
}

void RoomController::ready(json request, int clientfd)
{
    int room_id = request["param"];
    int auth_id = request["header"]["id"];
    Room room = Room::findById(room_id);
    ResponseReadyRoom response;

    pthread_mutex_lock(&ServerManager::mutex);

    auto it = usersReady.find(room_id);
    if (it != usersReady.end() && it->second.size() == room.capacity)
    {
        response.status = FAILURE;
        response.body.message = "Room is full";

        sendToClient(clientfd, response.toJson().dump().c_str());
    }
    else if (room.status != ROOM_LOBBY_STATUS)
    {
        response.status = FAILURE;
        response.body.message = "Room isnot lobby status";

        sendToClient(clientfd, response.toJson().dump().c_str());
    }
    else
    {
        if (it == usersReady.end())
        {
            std::vector<int> user_ids;
            user_ids.push_back(auth_id);
            usersReady.emplace(room_id, user_ids);
        }
        else
        {
            it->second.push_back(auth_id);
        }

        std::vector<std::unordered_map<int, int>> clientUserMaps = ServerManager::client_auth;
        std::vector<User> usersReadyResponse;

        auto usersReadyInRoom = usersReady.find(room_id);
        for (int id : usersReadyInRoom->second)
        {
            User u = User::findById(id);
            usersReadyResponse.push_back(u);
        }

        response.status = SUCCESS;
        response.body.usersReady = usersReadyResponse;

        for (int item : usersReadyInRoom->second)
        {
            auto i = std::find_if(clientUserMaps.begin(), clientUserMaps.end(),
                                  [item](const std::unordered_map<int, int> &clientUserMap)
                                  {
                                      return std::any_of(clientUserMap.begin(), clientUserMap.end(),
                                                         [item](const auto &entry)
                                                         {
                                                             return entry.second == item;
                                                         });
                                  });

            for (const auto &entry : *i)
            {
                sendToClient(entry.first, response.toJson().dump().c_str());
            }
        }

        std::vector<UserRoom> user_room = relationsUserRoom();
        auto itOwner = std::find_if(user_room.begin(), user_room.end(), [room_id](const UserRoom &ur)
                                    { return ur.room_id == room_id && ur.is_owner == true; });
        int owner_id = itOwner->user_id;

        auto iOwner = std::find_if(clientUserMaps.begin(), clientUserMaps.end(),
                                   [owner_id](const std::unordered_map<int, int> &clientUserMap)
                                   {
                                       return std::any_of(clientUserMap.begin(), clientUserMap.end(),
                                                          [owner_id](const auto &entry)
                                                          {
                                                              return entry.second == owner_id;
                                                          });
                                   });

        for (const auto &entry : *iOwner)
        {
            sendToClient(entry.first, response.toJson().dump().c_str());
        }
    }
    pthread_mutex_unlock(&ServerManager::mutex);
}

void RoomController::unready(json request, int clientfd)
{
    int room_id = request["param"];
    int auth_id = request["header"]["id"];

    pthread_mutex_lock(&ServerManager::mutex);

    auto it = usersReady.find(room_id);

    if (it != usersReady.end())
    {
        auto userIt = std::find(it->second.begin(), it->second.end(), auth_id);

        if (userIt != it->second.end())
        {
            it->second.erase(userIt);
        }
    }

    std::vector<std::unordered_map<int, int>> clientUserMaps = ServerManager::client_auth;
    std::vector<User> usersReadyResponse;

    auto usersReadyInRoom = usersReady.find(room_id);
    for (int id : usersReadyInRoom->second)
    {
        User u = User::findById(id);
        usersReadyResponse.push_back(u);
    }

    ResponseReadyRoom response;
    response.status = SUCCESS;
    response.body.usersReady = usersReadyResponse;

    for (int item : usersReadyInRoom->second)
    {
        auto i = std::find_if(clientUserMaps.begin(), clientUserMaps.end(),
                              [item](const std::unordered_map<int, int> &clientUserMap)
                              {
                                  return std::any_of(clientUserMap.begin(), clientUserMap.end(),
                                                     [item](const auto &entry)
                                                     {
                                                         return entry.second == item;
                                                     });
                              });

        for (const auto &entry : *i)
        {
            sendToClient(entry.first, response.toJson().dump().c_str());
        }
    }
    pthread_mutex_unlock(&ServerManager::mutex);

    std::vector<UserRoom> user_room = relationsUserRoom();
    auto itOwner = std::find_if(user_room.begin(), user_room.end(), [room_id](const UserRoom &ur)
                                { return ur.room_id == room_id && ur.is_owner == true; });
    int owner_id = itOwner->user_id;

    auto iOwner = std::find_if(clientUserMaps.begin(), clientUserMaps.end(),
                               [owner_id](const std::unordered_map<int, int> &clientUserMap)
                               {
                                   return std::any_of(clientUserMap.begin(), clientUserMap.end(),
                                                      [owner_id](const auto &entry)
                                                      {
                                                          return entry.second == owner_id;
                                                      });
                               });

    for (const auto &entry : *iOwner)
    {
        sendToClient(entry.first, response.toJson().dump().c_str());
    }

    auto itAuth = std::find_if(clientUserMaps.begin(), clientUserMaps.end(),
                               [auth_id](const std::unordered_map<int, int> &clientUserMap)
                               {
                                   return std::any_of(clientUserMap.begin(), clientUserMap.end(),
                                                      [auth_id](const auto &entry)
                                                      {
                                                          return entry.second == auth_id;
                                                      });
                               });

    for (const auto &entry : *itAuth)
    {
        sendToClient(entry.first, response.toJson().dump().c_str());
    }
}

void RoomController::start(json request, int clientfd)
{
    int auth_id = request["header"]["id"];
    int room_id = request["body"]["room_id"];

    auto now = std::chrono::system_clock::now();
    std::time_t convertTime = std::chrono::system_clock::to_time_t(now);
    std::stringstream formattedTime;
    formattedTime << std::put_time(std::localtime(&convertTime), "%Y-%m-%d %H:%M:%S");

    Room r = Room::findById(room_id);
    r.status = ROOM_DOING_STATUS;
    r.start_time = formattedTime.str();
    Room room = Room::edit(r);

    // std::vector<RoomQuestion> relationsRQ = relationsRoomQuestion();
    // std::vector<QuestionContent> questionsExam;
    // std::vector<Option> options = Option::getAll();

    // relationsRQ.erase(std::remove_if(relationsRQ.begin(), relationsRQ.end(),
    //                                  [room_id](const RoomQuestion &r_q)
    //                                  {
    //                                      return r_q.room_id != room_id;
    //                                  }),
    //                   relationsRQ.end());

    // for (RoomQuestion &rq : relationsRQ)
    // {
    //     Question q = Question::findById(rq.question_id);
    //     int q_id = q.id;
    //     std::vector<Option> filteredOptions;
    //     std::copy_if(options.begin(), options.end(), std::back_inserter(filteredOptions),
    //                  [q_id](const Option &option)
    //                  {
    //                      return option.question_id == q_id;
    //                  });
    //     QuestionContent qc;
    //     qc.question = q;
    //     qc.options = filteredOptions;

    //     questionsExam.push_back(qc);
    // }

    // Start Clock thread
    std::thread clockThread(countdownClock, r.time_limit, room_id);
    clockThread.detach();

    ResponseStartRoom response;
    response.body.room = r;
    // response.body.questions = questionsExam;
    response.status = SUCCESS;

    pthread_mutex_unlock(&ServerManager::mutex);
    std::vector<std::unordered_map<int, int>> clientUserMaps = ServerManager::client_auth;

    auto usersReadyInRoom = usersReady.find(room_id);

    for (int item : usersReadyInRoom->second)
    {
        auto i = std::find_if(clientUserMaps.begin(), clientUserMaps.end(),
                              [item](const std::unordered_map<int, int> &clientUserMap)
                              {
                                  return std::any_of(clientUserMap.begin(), clientUserMap.end(),
                                                     [item](const auto &entry)
                                                     {
                                                         return entry.second == item;
                                                     });
                              });

        for (const auto &entry : *i)
        {
            UserRoom ur;
            ur.user_id = entry.second;
            ur.room_id = room_id;
            ur.is_owner = false;
            insertUserRoom(ur);
            sendToClient(entry.first, response.toJson().dump().c_str());
        }
    }
    pthread_mutex_unlock(&ServerManager::mutex);

    std::vector<UserRoom> user_room = relationsUserRoom();
    auto itOwner = std::find_if(user_room.begin(), user_room.end(), [room_id](const UserRoom &ur)
                                { return ur.room_id == room_id && ur.is_owner == true; });
    int owner_id = itOwner->user_id;

    auto iOwner = std::find_if(clientUserMaps.begin(), clientUserMaps.end(),
                               [owner_id](const std::unordered_map<int, int> &clientUserMap)
                               {
                                   return std::any_of(clientUserMap.begin(), clientUserMap.end(),
                                                      [owner_id](const auto &entry)
                                                      {
                                                          return entry.second == owner_id;
                                                      });
                               });

    for (const auto &entry : *iOwner)
    {
        sendToClient(entry.first, response.toJson().dump().c_str());
    }
}

void RoomController::create(json request, int clientfd)
{
    std::string name = request["body"]["name"];
    std::string type = request["body"]["type"];
    int capacity = request["body"]["capacity"];
    int time_limit = request["body"]["time_limit"];
    bool is_private = request["body"]["is_private"];

    std::string password;
    if (is_private)
    {
        std::string passRequest = request["body"]["password"];
        password = sha256(passRequest);
    }
    else
    {
        password = "";
    }

    Room room = Room(name, capacity, type, "", "", ROOM_LOBBY_STATUS, time_limit, is_private, password);
    Room::create(room);

    std::vector<Question> questions = Question::getAll();
    int category_id = request["questions_exam"]["category_id"];
    json question_config = request["questions_exam"]["question_config"];

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

    for (const auto &q : selected_questions)
    {
        RoomQuestion rq;
        rq.question_id = q.id;
        rq.room_id = room.id;
        insertRoomQuestion(rq);
    }

    int auth_id = request["header"]["id"];
    UserRoom ur;
    ur.user_id = auth_id;
    ur.room_id = room.id;
    ur.is_owner = true;
    insertUserRoom(ur);

    ResponseCreateRoom response;
    response.status = SUCCESS;
    response.body.room = room;
    response.body.category = Category::findById(category_id);
    response.body.max_score = max_score;
    response.body.question_config = question_config.get<std::vector<int>>();

    sendToClient(clientfd, response.toJson().dump().c_str());
}

void RoomController::detail(json request, int clientfd)
{
    int auth_id = request["header"]["id"];
    int room_id = request["param"];

    std::vector<UserRoom> User_Room = relationsUserRoom();

    bool checkOwner = false;

    checkOwner = std::any_of(User_Room.begin(), User_Room.end(),
                             [auth_id, room_id](const UserRoom &item)
                             {
                                 return item.user_id == auth_id &&
                                        item.room_id == room_id &&
                                        item.is_owner;
                             });

    std::vector<RoomQuestion> room_questions = relationsRoomQuestion();
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

    ResponseDetailRoom response;
    response.status = SUCCESS;
    response.body.is_owner = checkOwner;
    response.body.room = Room::findById(room_id);
    response.body.question_config = q_config;
    response.body.message = "Get room detail success";

    sendToClient(clientfd, response.toJson().dump().c_str());
}

void countdownClock(int minutes, int room_id)
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

bool containsName(const Room &room, const std::string &searchTerm)
{
    return room.name.find(searchTerm) != std::string::npos;
}
