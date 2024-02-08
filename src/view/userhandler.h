#ifndef USERHANDLER_H
#define USERHANDLER_H

#include "../../library/json.hpp"

using json = nlohmann::json;

class UserHandler
{
public:
    UserHandler();

    void requestListUser();
    json responseListUser();
    void requestDeleteUser(int userId);
    json responseDeleteUser();
    void requestActiveUser(int userId, bool active);
    json responseActiveUser();
};

#endif // USERHANDLER_H

