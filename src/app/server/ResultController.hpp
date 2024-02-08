#ifndef RESULTCONTROLLER_HPP
#define RESULTCONTROLLER_HPP

#include "../../../library/json.hpp"

using json = nlohmann::json;

class ResultController
{
public:
    ResultController();

    void redriect(json request, int clientfd);
    void room(json request, int clientfd);
    void history(json request, int clientfd);
};

#endif
