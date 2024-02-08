#ifndef ROOMCONTROLLER_HPP
#define ROOMCONTROLLER_HPP

#include "../../../library/json.hpp"

using json = nlohmann::json;

class RoomController
{
public:
    RoomController();

    void redriect(json request, int clientfd);
    void list(json request, int clientfd);
    void join(json request, int clientfd);
    void ready(json request, int clientfd);
    void unready(json request, int clientfd);
    void start(json request, int clientfd);
    void create(json request, int clientfd);
    void detail(json request, int clientfd);
    void listOwner(json request, int clientfd);
};

#endif
