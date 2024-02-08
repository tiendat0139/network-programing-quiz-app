#ifndef ROOMHANDLER_H
#define ROOMHANDLER_H

#include "../../library/json.hpp"
#include "../app/request/room.h"

using json = nlohmann::json;

class RoomHandler
{
public:
    RoomHandler();
    void requestListRoom(std::vector<int> categories, std::string name_search);
    json responseListRoom();

    void requestJoinRoom(int room_id, bool is_private, std::string password);
    json responseJoinRoom();

    void requestReadyRoom(int room_id);
    json responseReadyRoom();

    void requestUnReadyRoom(int room_id);
    json responseUnReadyRoom();

    void requestStartRoom(int room_id);
    json responseStartRoom();

    void requestCreateRoom(RequestCreateRoomBody body, QuestionsExam questions_exam);
    json responseCreateRoom();

    void requestDetailRoom(int room_id);
    json responseDetailRoom();

    void requestListRoomOwner();
    json responseListRoomOwner();
};

#endif // ROOMHANDLER_H
