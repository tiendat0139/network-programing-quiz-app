#ifndef __CATEGORY_H__
#define __CATEGORY_H__

#include "vector"
#include "type.h"
#include "route.h"
#include "../../../library/json.hpp"
#include "../../Model/User.hpp"

using json = nlohmann::json;

typedef struct
{
    std::string code = REQUEST_GET_RESOURCE;
    json header;
    std::string url = RequestListUserRouter;
    int param;

    json toJson()
    {
        return json{
            {"code", code},
            {"url", url},
            {"header", header},
            {"param", param}};
    }
} RequestListUser;

typedef struct 
{
    std::vector<User> users;
    std::string message;
    json toJson()
    {
        json result;
        result["message"] = message;
        for (User &u : users)
        {
            result["users"].push_back(u.toJson());
        }
        return result;
    }
} ResponseListUserBody;

typedef struct
{
    std::string code = RESPONSE_GET_RESOURCE;
    json header;
    std::string status;
    std::string url = ResponseListUserRouter;
    ResponseListUserBody body;

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
} ResponseListUser;

typedef struct
{
    std::string code = REQUEST_EDIT_RESOURCE;
    json header;
    std::string url = RequestActiveUserRouter;
    bool active;
    int param;

    json toJson()
    {
        return json{
            {"code", code},
            {"url", url},
            {"header", header},
            {"active", active},
            {"param", param}};
    }
} RequestActiveUser;

typedef struct 
{
    std::string message;
    User user;
    json toJson() {
        return json{
            {"message", message},
            {"user", user.toJson()}
        };
    }
}ResponseActiveUserBody;

typedef struct
{
    std::string code = RESPONSE_EDIT_RESOURCE;
    json header;
    std::string status;
    std::string url = ResponseActiveUserRouter;
    ResponseActiveUserBody body;

    json toJson()
    {
        return json{
            {"code", code},
            {"url", url},
            {"header", header},
            {"status", status},
            {"body", body.toJson()}};
    }
} ResponseActiveUser;

typedef struct
{
    std::string code = REQUEST_DELETE_RESOURCE;
    json header;
    std::string url = RequestDeleteUserRouter;
    int param;

    json toJson()
    {
        return json{
            {"code", code},
            {"url", url},
            {"header", header},
            {"param", param}};
    }
} RequestDeleteUser;

typedef struct 
{
    std::string code = RESPONSE_DELETE_RESOURCE;
    json header;
    std::string url = ResponseDeleteUserRouter;
    std::string status;
    std::string message;

    json toJson() {
        json result;
        result["code"] = code;
        result["header"] = header;
        result["url"] = url;
        result["status"] = status;
        result["body"]["message"] = message;

        return result;
    }
} ResponseDeleteUser;


#endif