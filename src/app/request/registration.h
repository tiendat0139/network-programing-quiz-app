#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <vector>
#include <utility>

#include "route.h"
#include "type.h"
#include "../../../library/json.hpp"

typedef struct 
{
    std::string name;
    std::string email;
    std::string password;

    json toJson() {
        return json {
            {"name", name},
            {"email", email},
            {"password", password}
        };
    }
} RequestRegistrationBody;

typedef struct {
    std::string code = REQUEST_CREATE_RESOURCE;
    std::string url = RequestRegistrationRouter;
    json header;
    RequestRegistrationBody body;

    json toJson () {
        return json {
            {"code", code},
            {"header", header},
            {"url", url},
            {"body", body.toJson()}
        };
    }

} RequestRegistration;

typedef struct {
    std::string code = RESPONSE_CREATE_RESOURCE;
    json header;
    std::string url = ResponseRegistrationRouter;
    std::string status;
    User body;

    json toJson() {
        return json{
            {"code", code},
            {"header", header},
            {"status", status},
            {"url", url},
            {"body", body.toJson()}
        };
    }
} ResponseRegistration;

#endif