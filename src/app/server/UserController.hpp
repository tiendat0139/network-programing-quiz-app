#ifndef USERCONTROLLER_HPP
#define USERCONTROLLER_HPP

#include "../../../library/json.hpp"

using json = nlohmann::json;

class UserController
{
public:
    UserController();

    void redriect(json request, int clientfd);
    void list(json request, int clientfd);
    void active(json request, int clientfd);
    void Delete(json request, int clientfd);
};

#endif