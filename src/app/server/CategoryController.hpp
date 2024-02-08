#ifndef CATEGORYCONTROLLER_HPP
#define CATEGORYCONTROLLER_HPP

#include "../../../library/json.hpp"

using json = nlohmann::json;

class CategoryController
{
public:
    CategoryController();

    void redriect(json request, int clientfd);
    void list(json request, int clientfd);
};

#endif