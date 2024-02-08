#ifndef __ROOM_H__
#define __ROOM_H__

#include "vector"
#include "../../../library/json.hpp"
#include "../../Model/Room.hpp"
#include "../../Model/User.hpp"
#include "../../Model/Category.hpp"
#include "type.h"
#include "route.h"
#include "question.h"

using json = nlohmann::json;


typedef struct
{
    std::vector<int> categories;
    std::string name_search = "";

    json toJson() {
        return json{
            {"categories", categories},
            {"name_search", name_search}
        };
    }
} RequestListRoomBody;

typedef struct
{
    std::string code = REQUEST_GET_RESOURCE;
    json header;
    std::string url = RequestRoomListRouter;
    RequestListRoomBody body;

    json toJson()
    {
        return json{
            {"code", code},
            {"url", url},
            {"header", header},
            {"body", body.toJson()}};
    }
} RequestListRoom;

typedef struct
{
    std::vector<Room> rooms;
    std::string message;

    json toJson()
    {
        json result;
        for (Room &room : rooms)
        {
            result["rooms"].push_back(room.toJson());
        }
        result["message"] = message;
        return result;
    }
} ResponseListRoomBody;

typedef struct
{
    std::string code = RESPONSE_GET_RESOURCE;
    std::string header;
    std::string url = ResponseRoomListRouter;
    std::string status;
    ResponseListRoomBody body;

    json toJson()
    {
        return json{
            {"code", code},
            {"url", url},
            {"header", header},
            {"status", status},
            {"body", body.toJson()}};
    }
} ResponseListRoom;

typedef struct
{
    bool is_private;
    std::string password;
    json toJson() {
        return json{
            {"is_private", is_private},
            {"password", password},
        };
    }
}ResquestJoinRoomBody;

typedef struct
{
    std::string code = REQUEST_GET_RESOURCE;
    json header;
    std::string url = RequestJoinRoomRouter;
    int param;
    ResquestJoinRoomBody body;

    json toJson()
    {
        return json{
            {"code", code},
            {"url", url},
            {"header", header},
            {"param", param},
            {"body", body.toJson()}
        };
    }
} RequestJoinRoom;

typedef struct
{
    Room room;
    bool is_owner;
    std::vector<User> usersReady;
    std::string message;

    json toJson()
    {
        json result;
        if (usersReady.size() > 0)
        {
            for (User &user : usersReady)
            {
                result["usersReady"].push_back(user.toJson());
            }
        }
        else
        {
            result["usersReady"] = nullptr;
        }

        result["room"] = room.toJson();
        result["is_owner"] = is_owner;
        result["message"] = message;
        return result;
    };
} ResponseJoinRoomBody;

typedef struct
{
    std::string code = RESPONSE_GET_RESOURCE;
    json header;
    std::string url = ResponseJoinRoomRouter;
    std::string status;
    ResponseJoinRoomBody body;

    json toJson()
    {
        return json{
            {"code", code},
            {"url", url},
            {"header", header},
            {"status", status},
            {"body", body.toJson()}};
    }
} ResponseJoinRoom;

typedef struct
{
    std::string code = REQUEST_GET_RESOURCE;
    json header;
    std::string url = RequestReadyRoomRouter;
    int param;

    json toJson()
    {
        return json{
            {"code", code},
            {"url", url},
            {"header", header},
            {"param", param}};
    }
} RequestReadyRoom;

typedef struct
{
    std::vector<User> usersReady;
    std::string message;

    json toJson()
    {
        json result;
        for (User &user : usersReady)
        {
            result["usersReady"].push_back(user.toJson());
        }
        result["message"] = message;
        return result;
    }
} ResponseReadyRoomBody;

typedef struct
{
    std::string code = RESPONSE_GET_RESOURCE;
    json header;
    std::string status;
    std::string url = ResponseReadyRoomRouter;
    ResponseReadyRoomBody body;

    json toJson()
    {
        return json{
            {"code", code},
            {"status", status},
            {"url", url},
            {"header", header},
            {"body", body.toJson()}};
    }
} ResponseReadyRoom;

typedef struct
{
    std::string code = REQUEST_DELETE_RESOURCE;
    json header;
    std::string url = RequestUnReadyRoomRouter;
    int param;

    json toJson()
    {
        return json{
            {"code", code},
            {"url", url},
            {"header", header},
            {"param", param}};
    }
} RequestUnReadyRoom;

typedef struct
{
    std::string code = RESPONSE_DELETE_RESOURCE;
    json header;
    std::string status;
    std::string url = ResponseUnReadyRoomRouter;
    ResponseReadyRoomBody body;

    json toJson()
    {
        return json{
            {"code", code},
            {"status", status},
            {"url", url},
            {"header", header},
            {"body", body.toJson()}};
    }
} ResponseUnReadyRoom;

typedef struct
{
    int room_id;
    json toJson()
    {
        return json{
            {"room_id", room_id},
        };
    }
} RequestStartRoomBody;

typedef struct
{
    std::string code = REQUEST_CREATE_RESOURCE;
    json header;
    std::string url = RequestStartRoomRouter;
    RequestStartRoomBody body;

    json toJson()
    {
        return json{
            {"code", code},
            {"url", url},
            {"header", header},
            {"body", body.toJson()}
        };
    }
} RequestStartRoom;

typedef struct
{
    Room room;
    // std::vector<QuestionContent> questions;
    json toJson()
    {
        json result;
        // for (QuestionContent &q : questions)
        // {
        //     result["questions"].push_back(q.toJson());
        // }
        result["room"] = room.toJson();
        return result;
    }
} ResponseStartRoomBody;

typedef struct
{
    std::string code = RESPONSE_CREATE_RESOURCE;
    json header;
    std::string status;
    std::string url = ResponseStartRoomRouter;
    ResponseStartRoomBody body;

    json toJson()
    {
        return json{
            {"code", code},
            {"url", url},
            {"status", status},
            {"header", header},
            {"body", body.toJson()}
        };
    }
} ResponseStartRoom;

typedef struct
{
    std::string name;
    int time_limit;
    int capacity;
    bool is_private;
    std::string password;
    std::string type;
    json toJson()
    {
        return json{
            {"name", name},
            {"time_limit", time_limit},
            {"capacity", capacity},
            {"is_private", is_private},
            {"password", password},
            {"type", type},
        };
    }
} RequestCreateRoomBody;

typedef struct
{
    std::string code = REQUEST_CREATE_RESOURCE;
    json header;
    std::string url = RequestCreateRoomRouter;
    RequestCreateRoomBody body;
    QuestionsExam questions_exam;

    json toJson()
    {
        return json{
            {"code", code},
            {"url", url},
            {"header", header},
            {"body", body.toJson()},
            {"questions_exam", questions_exam.toJson()}
        };
    }
} RequestCreateRoom;

typedef struct
{
    Room room;
    Category category;
    int max_score;
    std::vector<int> question_config;

    json toJson(){
        json qc = question_config;
        return json{
            {"room", room.toJson()},
            {"category", category.toJson()},
            {"max_score", max_score},
            {"question_config", qc},
        };
    }
}ResponseCreateRoomBody;

typedef struct
{
    std::string code = RESPONSE_CREATE_RESOURCE;
    json header;
    std::string status;
    std::string url = ResponseCreateRoomRouter;
    ResponseCreateRoomBody body;

    json toJson()
    {
        return json{
            {"code", code},
            {"url", url},
            {"status", status},
            {"header", header},
            {"body", body.toJson()},
        };
    }
} ResponseCreateRoom;


typedef struct
{
    std::string code = REQUEST_GET_RESOURCE;
    json header;
    std::string url = RequestRoomDetailRouter;
    int param;

    json toJson() {
        return json{
            {"code", code},
            {"url", url},
            {"header", header },
            {"param", param}
        };

    }
} ResquestDetailRoom;

typedef struct
{
    Room room;
    bool is_owner;
    std::vector<int> question_config;
    std::string message;

    json toJson() {
        return json{
            {"room", room.toJson()},
            {"is_owner", is_owner},
            {"question_config", question_config},
            {"message", message}
        };
    };
} ResponseDetailRoomBody;

typedef struct
{
    std::string code = RESPONSE_GET_RESOURCE;
    json header;
    std::string url = ResponseRoomDetailRouter;
    std::string status;
    ResponseDetailRoomBody body;

    json toJson() {
        return json{
            {"code", code},
            {"url", url},
            {"header", header },
            {"body", body.toJson()}
        };
    }
} ResponseDetailRoom;

typedef struct
{
    std::string code = REQUEST_GET_RESOURCE;
    json header;
    std::string url = RequestRoomOwnerListRouter;
    int param;
    json toJson()
    {
        return json{
            {"code", code},
            {"url", url},
            {"header", header},
            {"param", param}};
    }
} RequestListRoomOwner;

typedef struct
{
    std::string code = RESPONSE_GET_RESOURCE;
    std::string header;
    std::string url = ResponseRoomOwnerListRouter;
    std::string status;
    ResponseListRoomBody body;
    json toJson()
    {
        return json{
            {"code", code},
            {"url", url},
            {"header", header},
            {"status", status},
            {"body", body.toJson()}};
    }
} ResponseListRoomOwner;

#endif
