#ifndef __PRACTICE_H__
#define __PRACTICE_H__

#include "vector"
#include "type.h"
#include "route.h"
#include "../../Model/Category.hpp"
#include "question.h"
#include "../../Model/Room.hpp"
#include "../../../library/json.hpp"

using json = nlohmann::json;

typedef struct {
    std::string name;
    int time_limit;
    int category_id;

    json toJson() {
        return json{
            {"name", name},
            {"time_limit", time_limit},
            {"category_id", category_id},
        };
    }
} RequestCreatePracticeBody;

typedef struct
{
    std::string code = REQUEST_CREATE_RESOURCE;
    json header;
    std::string url = RequestCreatePracticeRouter;
    RequestCreatePracticeBody body;

    json toJson()
    {
        return json{
            {"code", code},
            {"url", url},
            {"header", header},
            {"body", body.toJson()}
        };
    }
} RequestCreatePractice;

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
}ResponseCreatePracticeBody;


typedef struct
{
    std::string code = RESPONSE_CREATE_RESOURCE;
    json header;
    std::string status;
    std::string url = ResponseCreatePracticeRouter;
    ResponseCreatePracticeBody body;

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
} ResponseCreatePractice;

typedef struct
{
    std::string code = REQUEST_GET_RESOURCE;
    json header;
    std::string url = RequestStartPracticeRouter;
    int param;

    json toJson()
    {
        return json{
            {"code", code},
            {"url", url},
            {"header", header},
            {"param", param}
        };
    }
} RequestStartPractice;

typedef struct
{
    Room room;
    std::vector<QuestionContent> questions;
    json toJson()
    {
        json result;
        for (QuestionContent &q : questions)
        {
            result["questions"].push_back(q.toJson());
        }
        result["room"] = room.toJson();
        return result;
    }
} ResponseStartPracticeBody;

typedef struct
{
    std::string code = RESPONSE_CREATE_RESOURCE;
    json header;
    std::string status;
    std::string url = ResponseStartPracticeRouter;
    ResponseStartPracticeBody body;

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
} ResponseStartPractice;

typedef struct
{
    std::string code = REQUEST_EDIT_RESOURCE;
    json header;
    std::string url = RequestEndPracticeRouter;
    int param;

    json toJson()
    {
        return json{
            {"code", code},
            {"url", url},
            {"header", header},
            {"param", param}
        };
    }
}RequestEndPractice;

typedef struct
{
    std::string code = RESPONSE_EDIT_RESOURCE;
    json header;
    std::string url = ResponseEndPracticeRouter;
    std::string status;
    std::string message;
    
    json toJson()
    {
        json result;

        result["code"] = code;
        result["header"] = header;
        result["url"] = url;
        result["status"] = status;
        result["body"]["meessage"] = message;

        return result;
    }
}ResponseEndPractice;

#endif