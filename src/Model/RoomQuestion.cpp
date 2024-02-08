#include "RoomQuestion.hpp"

#include <vector>
#include <fstream>

#include "../../library/json.hpp"

#define ROOM_QUESTION_JSON "../../../database/room_question.json"

using json = nlohmann::json;

std::vector<RoomQuestion> relationsRoomQuestion()
{
    std::ifstream room_question_json(ROOM_QUESTION_JSON);
    json roomQuestionData;
    room_question_json >> roomQuestionData;
    room_question_json.close();

    std::vector<RoomQuestion> roomQuestions;

    for (auto& item : roomQuestionData["room_question"])
    {
        RoomQuestion r_q;
        r_q.question_id = item["question_id"];
        r_q.room_id = item["room_id"];
        roomQuestions.push_back(r_q);
    }
    return roomQuestions;
}

void insertRoomQuestion(RoomQuestion &r_q)
{
    json jsonData;
    std::ifstream inputFile(ROOM_QUESTION_JSON);
    inputFile >> jsonData;
    inputFile.close();

    json newR_Q;
    newR_Q["room_id"] = r_q.room_id;
    newR_Q["question_id"] = r_q.question_id;

    jsonData["room_question"].push_back(newR_Q);

    std::ofstream outputFile(ROOM_QUESTION_JSON);
    outputFile << std::setw(4) << jsonData;
    outputFile.close();
}