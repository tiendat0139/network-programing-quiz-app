#ifndef __ANSWER_H__
#define __ANSWER_H__

#include "vector"
#include "type.h"
#include "route.h"
#include "../../../library/json.hpp"

using json = nlohmann::json;

typedef struct
{
    int room_id;
    int question_id;
    int option_id;

    json toJson() {
        return {
            {"room_id", room_id},
            {"question_id", question_id},
            {"option_id", option_id},
        };
    }
} RequestSubmitAnswerBody;

typedef struct
{
    std::string code = REQUEST_CREATE_RESOURCE;
    json header;
    std::string url = RequestSubmitAnswerRouter;
    RequestSubmitAnswerBody body;

    json toJson()
    {
        return json{
            {"code", code},
            {"url", url},
            {"header", header},
            {"body", body.toJson()}
        };
    }
} RequestSubmitAnswer;

typedef struct 
{
   std::string message;
   int room_id;
   int question_id;
   int option_id;
   json toJson() {
        return json{
            {"message", message},
            {"room_id", room_id},
            {"question_id", question_id},
            {"option_id", option_id},
        };
   }
    
} ResponseSubmitAnswerBody;

typedef struct
{
    std::string code = RESPONSE_CREATE_RESOURCE;
    json header;
    std::string status;
    std::string url = ResponseSubmitAnswerRouter;
    ResponseSubmitAnswerBody body;

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
} ResponseSubmitAnswer;

#endif