#ifndef RESULTHANDLER_H
#define RESULTHANDLER_H

#include "../../library/json.hpp"

using json = nlohmann::json;

class ResultHandler
{
public:
    ResultHandler();

    void requestRoomResult(int room_id);
    json responseRoomResult();

    void requestHistoryResult();
    json responseHistoryResult();
};

#endif // RESULTHANDLER_H
