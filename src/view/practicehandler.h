#ifndef PRACTICEHANDLER_H
#define PRACTICEHANDLER_H

#include "../../library/json.hpp"

using json = nlohmann::json;

class PracticeHandler
{
public:
    PracticeHandler();

    void requestCreatePractice(int category_id, std::string name, int time_limit);
    json responseCreatePractice();

    void requestStartPractice(int room_id);
    json responseStartPractice();

    void requestEndPractice(int room_id);
    json responseEndPractice();
};

#endif // PRACTICEHANDLER_H
