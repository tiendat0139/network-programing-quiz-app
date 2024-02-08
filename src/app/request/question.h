#ifndef __QUESTION_H__
#define __QUESTION_H__

#include <vector>
#include <utility>
#include "../../../library/json.hpp"
#include "../../Model/Question.hpp"
#include "../../Model/Option.hpp"
#include "type.h"
#include "route.h"

typedef struct
{
    Question question;
    std::vector<Option> options;

    json toJson()
    {
        json result;
        for (Option &o : options)
        {
            result["options"].push_back(o.toJson());
        }
        result["question"] = question.toJson();
        return result;
    }
} QuestionContent;

typedef struct
{
    int category_id;
    std::vector<int> question_config;

    json toJson()
    {
        json q_config = question_config;
        return json{
            {"category_id", category_id},
            {"question_config", q_config}
        };
    }
} QuestionsExam;

typedef struct
{
    std::string title;
    int category_id;
    int level;
    std::vector<std::pair<std::string, bool>> options;

    json toJson()
    {
        json result;
        result["title"] = title;
        result["category_id"] = category_id;
        result["level"] = level;
        for (const auto& option : options){
            result["options"].push_back({{"content", option.first}, {"correct", option.second}});
        }
        return result;
    }

} RequestCreateQuestionBody;

typedef struct
{
    std::string code = REQUEST_CREATE_RESOURCE;
    json header;
    std::string url = RequestCreateQuestionRouter;
    RequestCreateQuestionBody body;

    json toJson()
    {
        return json{
            {"code", code},
            {"url", url},
            {"header", header},
            {"body", body.toJson()}};
    }
} RequestCreateQuestion;

typedef struct
{
    std::string code = RESPONSE_CREATE_RESOURCE;
    json header;
    std::string status;
    std::string url = ResponseCreateQuestionRouter;
    Question body;

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
} ResponseCreateQuestion;

typedef struct {
    int question_id;
    std::string title;
    int category_id;
    int level;
    std::vector<std::pair<std::string, bool>> options;

    json toJson()
    {
        return json{
            {"question_id", question_id},
            {"title", title},
            {"category_id", category_id},
            {"level", level},
            {"options", options}
        };
    }
} RequestUpdateQuestionBody;

typedef struct {
    std::string code = REQUEST_CREATE_RESOURCE;
    json header;
    std::string url = RequestUpdateQuestionRouter;
    RequestUpdateQuestionBody body;

    json toJson() {
        return json {
            {"code", code},
            {"url", url},
            {"header", header},
            {"body", body.toJson()}
        };
    }
} RequestUpdateQuestion;


typedef struct {
    std::string code = RESPONSE_EDIT_RESOURCE;
    json header;
    std::string status;
    std::string url = ResponseUpdateQuestionRouter;
    Question body;

    json toJson()
    {
        return json {
            {"code", code},
            {"url", url},
            {"status", status},
            {"header", header},
            {"body", body.toJson()}
        };
    }
} ResponseUpdateQuestion;

typedef struct {
    std::string code = REQUEST_GET_RESOURCE;
    json header;
    std::string url = RequestGetQuestionByRoomRouter;
    int room_id;

    json toJson() {
        return json{
            {"code", code},
            {"header", header},
            {"url", url},
            {"room_id", room_id}
        };
    }
} RequesGetQuestionByRoom;


typedef struct
{
    std::vector<QuestionContent> questions;
    std::string message;
    json toJson()
    {
        json result;
        for (QuestionContent &q : questions)
        {
            result["questions"].push_back(q.toJson());
        }
        result["message"] = message;
        return result;
    }
}ResponseGetQuestionByRoomBody;


typedef struct {
    std::string code = RESPONSE_GET_RESOURCE;
    json header;
    std::string status;
    std::string url = ResponseGetQuestionByRoomRouter;
    ResponseGetQuestionByRoomBody body;

    json toJson(){
        return json{
            {"code", code},
            {"header", header},
            {"status", status},
            {"url", url},
            {"body", body.toJson()}
        };
    }
} ResponseGetQuestionByRoom;

typedef struct {
    std::string code = REQUEST_DELETE_RESOURCE;
    json header;
    std::string url = RequestDeleteQuestionRouter;
    int question_id;

    json toJson() {
        return json {
            {"code", code},
            {"header", header},
            {"url", url},
            {"question_id", question_id}
        };
    }
} RequestDeleteQuestion;

typedef struct{
    std::string message;

    json toJson() {
        return json{
            {"message", message},
        };
    }
}ResponseDeleteQuestionBody;
typedef struct {
    std::string code = RESPONSE_DELETE_RESOURCE;
    json header;
    std::string url = ResponseDeleteQuestionRouter;
    std::string status;
    ResponseDeleteQuestionBody body;

    json toJson(){
        return json {
            {"code", code},
            {"header", header},
            {"status", status},
            {"url", url},
            {"body", body.toJson()},
        };
    }

} ResponseDeleteQuestion;

typedef struct
{
    std::string code = REQUEST_GET_RESOURCE;
    json header;
    std::string url = RequestConfigQuestionRouter;
    int param;

    json toJson() {
        return json{
            {"code", code},
            {"url", url},
            {"header", header },
            {"param", param}
        };
    }
} RequestConfigQuestion;

typedef struct
{
    int room_id;
    std::string room_name;
    std::vector<int> question_config;

    json toJson() {
        return json{
            {"room_id", room_id},
            {"room_name", room_name},
            {"question_config", question_config},
        };
    }
}RoomConfigQuestion;

typedef struct
{
    std::string message;
    std::vector<RoomConfigQuestion> room_questions;

    json toJson() {
        json result;
        for (RoomConfigQuestion &rq : room_questions)
        {
            result["room_questions"].push_back(rq.toJson());
        }
        result["message"] = message;
        return result;
    };
} ResponseConfigQuestionBody;

typedef struct
{
    std::string code = RESPONSE_GET_RESOURCE;
    json header;
    std::string status;
    std::string url = ResponseConfigQuestionRouter;
    ResponseConfigQuestionBody body;

    json toJson() {
        return json{
            {"code", code},
            {"url", url},
            {"status", status},
            {"header", header },
            {"body", body.toJson()}
        };
    }
} ResponseConfigQuestion;


typedef struct {
    std::string code = REQUEST_GET_RESOURCE;
    json header;
    std::string url = RequestGetQuestionByCategoryRouter;
    int category_id;

    json toJson() {
        return json{
            {"code", code},
            {"header", header},
            {"url", url},
            {"category_id", category_id}
        };
    }
} RequestGetQuestionByCategory;

typedef struct
{
    std::vector<QuestionContent> questions;
    std::string message;
    json toJson()
    {
        json result;
        for (QuestionContent &q : questions)
        {
            result["questions"].push_back(q.toJson());
        }
        result["message"] = message;
        return result;
    }
}ResponseGetQuestionByCategoryBody;

typedef struct {
    std::string code = RESPONSE_GET_RESOURCE;
    json header;
    std::string status;
    std::string url = ResponseGetQuestionByCategoryRouter;
    ResponseGetQuestionByCategoryBody body;

    json toJson(){
        return json{
            {"code", code},
            {"header", header},
            {"status", status},
            {"url", url},
            {"body", body.toJson()}
        };
    }
} ResponseGetQuestionByCategory;
#endif
