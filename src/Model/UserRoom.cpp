#include "UserRoom.hpp"

#include <vector>
#include <fstream>

#include "../../library/json.hpp"

#define USER_ROOM_JSON "../../../database/user_room.json"

using json = nlohmann::json;

std::vector<UserRoom> relationsUserRoom()
{
    std::ifstream user_room_json(USER_ROOM_JSON);
    json userRoomData;
    user_room_json >> userRoomData;
    user_room_json.close();

    std::vector<UserRoom> userRooms;

    for (auto& item : userRoomData["user_room"])
    {
        UserRoom userRoom;
        userRoom.user_id = item["user_id"];
        userRoom.room_id = item["room_id"];
        userRoom.is_owner = item["is_owner"];
        userRooms.push_back(userRoom);
    }
    return userRooms;
}

void insertUserRoom(UserRoom &u_r)
{
    json jsonData;
    std::ifstream inputFile(USER_ROOM_JSON);
    inputFile >> jsonData;
    inputFile.close();

    json newU_R;
    newU_R["room_id"] = u_r.room_id;
    newU_R["user_id"] = u_r.user_id;
    newU_R["is_owner"] = u_r.is_owner;

    jsonData["user_room"].push_back(newU_R);

    std::ofstream outputFile(USER_ROOM_JSON);
    outputFile << std::setw(4) << jsonData;
    outputFile.close();
}
