#ifndef __CATEGORY_H__
#define __CATEGORY_H__

#include "vector"
#include "type.h"
#include "route.h"
#include "../../../library/json.hpp"
#include "../../Model/Category.hpp"

using json = nlohmann::json;

typedef struct
{
    std::string code = REQUEST_GET_RESOURCE;
    json header;
    std::string url = RequestListCategoryRouter;
    int param;

    json toJson()
    {
        return json{
            {"code", code},
            {"url", url},
            {"header", header},
            {"param", param}};
    }
} RequestListCategory;

typedef struct 
{
    std::vector<Category> categories;
    json toJson()
    {
        json result;
        for (Category &c : categories)
        {
            result["categories"].push_back(c.toJson());
        }
        return result;
    }
} ResponseListCategoryBody;

typedef struct
{
    std::string code = RESPONSE_GET_RESOURCE;
    json header;
    std::string status;
    std::string url = ResponseListCategoryRouter;
    ResponseListCategoryBody body;

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
} ResponseListCategory;
#endif