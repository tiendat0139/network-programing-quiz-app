#ifndef USER_ROOM
#define USER_ROOM

#include <vector>

typedef struct 
{
    int user_id;
    int room_id;
    bool is_owner;
} UserRoom;

std::vector<UserRoom> relationsUserRoom();
void insertUserRoom(UserRoom &u_r);
#endif