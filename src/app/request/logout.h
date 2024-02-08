#ifndef __LOGOUT_H__
#define __LOGOUT_H__

#include "../../../library/json.hpp"
#include "type.h"
#include "route.h"
#include "../../Model/User.hpp"

using json = nlohmann::json;


typedef struct
{
    std::string code = REQUEST_DELETE_RESOURCE;
    json header;
    std::string url = RequestLogoutRouter;
    std::string param;
    
    json toJson() {
        return json{
            {"code", code},
            {"url", url},
            {"header", header },
            {"param", param },
        };

    }
} RequestLogout;

typedef struct
{
    std::string code = RESPONSE_DELETE_RESOURCE;
    std::string url = ResponseLogoutRouter;
    std::string status;
    std::string header;
    std::string message;

    json toJson() {
        return json{
            {"code", code},
            {"url", url},
            {"status", status},
            {"header", header },
            {"message", message}
        };

    }
} ResponseLogout;

#endif
