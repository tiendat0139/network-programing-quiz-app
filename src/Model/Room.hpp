#ifndef ROOM_HPP
#define ROOM_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include "../../library/json.hpp"
#pragma once
using json = nlohmann::json;
extern std::string source;
class Room
{
public:
    int id;
    std::string name;
    int capacity;
    std::string type;
    std::string start_time;
    std::string close_time;
    std::string status;
    int time_limit;
    bool is_private;
    std::string password;

    Room();

    // Constructor without auto-increase id
    Room(int id, const std::string &name, int capacity, const std::string &type,
         const std::string &start_time, const std::string &close_time,
         const std::string status, int time_limit, bool is_private, const std::string password);

    // Constructor with auto-increase id
    Room(const std::string &name, int capacity, const std::string &type,
         const std::string &start_time, const std::string &close_time,
         const std::string status, int time_limit, bool is_private, const std::string password);

    static std::vector<Room> getAll();
    static Room findById(int id);
    static Room edit(Room &updatedRoom);
    static Room create(const Room &newRoom);
    static void Delete(const Room &roomToDelete);
    json toJson()
    {
          return json{
               {"id", id},
               {"name", name},
               {"capacity", capacity},
               {"type", type},
               {"start_time", start_time},
               {"close_time", close_time},
               {"status", status},
               {"time_limit", time_limit},
               {"is_private", is_private},
               // {"password", password},
          };
    };
};

#endif // ROOM_HPP
