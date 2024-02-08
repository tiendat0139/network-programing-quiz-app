#include "Room.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include "../../library/json.hpp"

using json = nlohmann::json;

#define ROOMS_JSON "../../../database/rooms.json"

Room::Room() = default;

// Constructor without auto-increase id
Room::Room(int id, const std::string &name, int capacity, const std::string &type,
            const std::string &start_time, const std::string &close_time,
            const std::string status, int time_limit, bool is_private, const std::string password)
    : id(id), name(name), capacity(capacity), type(type),
        start_time(start_time), close_time(close_time),
        status(status), time_limit(time_limit), is_private(is_private), password(password) {}

// Constructor with auto-increase id
Room::Room(const std::string &name, int capacity, const std::string &type,
            const std::string &start_time, const std::string &close_time,
            const std::string status, int time_limit, bool is_private, const std::string password)
    : name(name), capacity(capacity), type(type),
        start_time(start_time), close_time(close_time),
        status(status), time_limit(time_limit), is_private(is_private), password(password) {

    std::vector<Room> rooms = getAll();
    // Auto-increment id based on the last room's id in the ROOMS_JSON file
    if (!rooms.empty()) {
        id = rooms.back().id + 1;
    } else {
        id = 1; // If no one exist, start from id 1
    }
}

std::vector<Room> Room::getAll()
{
    std::vector<Room> rooms;

    // Load existing rooms from JSON
    json jsonData;
    std::ifstream inputFile(ROOMS_JSON);
    inputFile >> jsonData;
    inputFile.close();

    for (const auto &roomData : jsonData["rooms"])
    {
        Room room;
        room.id = roomData["id"];
        room.name = roomData["name"];
        room.capacity = roomData["capacity"];
        room.type = roomData["type"];
        room.start_time = roomData["start_time"];
        room.close_time = roomData["close_time"];
        room.status = roomData["status"];
        room.time_limit = roomData["time_limit"];
        room.is_private = roomData["is_private"];
        room.password = roomData["password"];

        rooms.push_back(room);
    }

    return rooms;
}

Room Room::findById(int roomId)
{
    // Load existing rooms from JSON
    json jsonData;
    std::ifstream inputFile(ROOMS_JSON);
    inputFile >> jsonData;
    inputFile.close();

    for (const auto &roomData : jsonData["rooms"])
    {
        if (roomData["id"] == roomId)
        {
            Room room;
            room.id = roomData["id"];
            room.name = roomData["name"];
            room.capacity = roomData["capacity"];
            room.type = roomData["type"];
            room.start_time = roomData["start_time"];
            room.close_time = roomData["close_time"];
            room.status = roomData["status"];
            room.time_limit = roomData["time_limit"];
            room.is_private = roomData["is_private"];
            room.password = roomData["password"];

            return room;
        }
    }

    // Return an empty room if not found
    return Room();
}

Room Room::edit(Room &updatedRoom)
{
    // Load existing rooms from JSON
    json jsonData;
    std::ifstream inputFile(ROOMS_JSON);
    inputFile >> jsonData;
    inputFile.close();

    // Find and update the room with matching id
    for (auto &roomData : jsonData["rooms"])
    {
        if (roomData["id"] == updatedRoom.id)
        {
            roomData["name"] = updatedRoom.name;
            roomData["capacity"] = updatedRoom.capacity;
            roomData["type"] = updatedRoom.type;
            roomData["start_time"] = updatedRoom.start_time;
            roomData["close_time"] = updatedRoom.close_time;
            roomData["status"] = updatedRoom.status;
            roomData["time_limit"] = updatedRoom.time_limit;
            roomData["is_private"] = updatedRoom.is_private;
            roomData["password"] = updatedRoom.password;
            break;
        }
    }

    // Write the updated data back to JSON file
    std::ofstream outputFile(ROOMS_JSON);
    outputFile << std::setw(4) << jsonData;
    outputFile.close();

    return updatedRoom;
}

Room Room::create(const Room &newRoom)
{
    // Load existing rooms from JSON
    json jsonData;
    std::ifstream inputFile(ROOMS_JSON);
    inputFile >> jsonData;
    inputFile.close();

    // Add the new room to the JSON data
    json newRoomJson;
    newRoomJson["id"] = newRoom.id;
    newRoomJson["name"] = newRoom.name;
    newRoomJson["capacity"] = newRoom.capacity;
    newRoomJson["type"] = newRoom.type;
    newRoomJson["start_time"] = newRoom.start_time;
    newRoomJson["close_time"] = newRoom.close_time;
    newRoomJson["status"] = newRoom.status;
    newRoomJson["time_limit"] = newRoom.time_limit;
    newRoomJson["is_private"] = newRoom.is_private;
    newRoomJson["password"] = newRoom.password;

    jsonData["rooms"].push_back(newRoomJson);

    // Write the updated data back to JSON file
    std::ofstream outputFile(ROOMS_JSON);
    outputFile << std::setw(4) << jsonData;
    outputFile.close();

    return newRoom;
}

void Room::Delete(const Room &roomToRemove)
{
    // Load existing rooms from JSON
    json jsonData;
    std::ifstream inputFile(ROOMS_JSON);
    inputFile >> jsonData;
    inputFile.close();

    // Find and remove the room with matching id
    auto &roomsArray = jsonData["rooms"];
    roomsArray.erase(std::remove_if(roomsArray.begin(), roomsArray.end(),
                                    [&roomToRemove](const auto &roomData)
                                    {
                                        return roomData["id"] == roomToRemove.id;
                                    }),
                     roomsArray.end());

    // Write the updated data back to JSON file
    std::ofstream outputFile(ROOMS_JSON);
    outputFile << std::setw(4) << jsonData;
    outputFile.close();
}