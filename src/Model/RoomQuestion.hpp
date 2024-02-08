#ifndef ROOM_QUESTION
#define ROOM_QUESTION

#include <vector>

typedef struct 
{
    int room_id;
    int question_id;
} RoomQuestion;

std::vector<RoomQuestion> relationsRoomQuestion();
void insertRoomQuestion(RoomQuestion &r_q);
#endif