#ifndef AUTHCONTROLLER_HPP
#define AUTHCONTROLLER_HPP

#include "../../../library/json.hpp"

using json = nlohmann::json;

class AuthController
{
public:
    AuthController();

    void login(json request, int clientfd);
    void logout(json request, int clientfd);
    void signup(json request, int clientfd);
};

#endif