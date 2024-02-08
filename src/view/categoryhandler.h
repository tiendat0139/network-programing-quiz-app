#ifndef CATEGORYHANDLER_H
#define CATEGORYHANDLER_H

#include "../../library/json.hpp"

using json = nlohmann::json;

class CategoryHandler
{
public:
    CategoryHandler();

    void requestListCategory();
    json responseListCategory();
};

#endif // CATEGORYHANDLER_H
