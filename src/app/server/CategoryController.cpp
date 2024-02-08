#include <iostream>
#include <vector>

#include "CategoryController.hpp"
#include "ServerManager.hpp"
#include "../comunicate/server.h"
#include "../request/category.h"

CategoryController::CategoryController() = default;

void CategoryController::redriect(json request, int clientfd)
{
    std::string url = request["url"];

    if (url == RequestListCategoryRouter)
    {
        list(request, clientfd);
    }
    
}

void CategoryController::list(json request, int clientfd)
{
    std::vector<Category> categories = Category::getAll();

    ResponseListCategory response;
    response.body.categories = categories;
    response.status = SUCCESS;
    sendToClient(clientfd, response.toJson().dump().c_str());
}