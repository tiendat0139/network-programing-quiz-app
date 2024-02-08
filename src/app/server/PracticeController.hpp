#ifndef PRACTICECONTROLLER_HPP
#define PRACTICECONTROLLER_HPP

#include "../../../library/json.hpp"

using json = nlohmann::json;

class PracticeController
{
public:
    PracticeController();

    void redriect(json request, int clientfd);
    void create(json request, int clientfd);
    void start(json request, int clientfd);
    void end(json request, int clientfd);
};

#endif