#ifndef ANSWER_HPP
#define ANSWER_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include "../../library/json.hpp"

using json = nlohmann::json;

class Answer
{
public:
    int id;
    int user_id;
    int room_id;
    int question_id;
    int option_id;
    int result;

    Answer();

    // Constructor with auto-increase id
    Answer(int user_id, int room_id, int question_id, int option_id, int result);

    // Constructor with specific id
    Answer(int id, int user_id, int room_id, int question_id, int option_id, int result);

    // Constructor with default values for option_id and result
    Answer(int user_id, int room_id, int question_id);

    static std::vector<Answer> getAll();
    static Answer findById(int id);
    static Answer edit(const Answer &updatedAnswer);
    static Answer create(const Answer &newAnswer);
    static void Delete(const Answer &answerToDelete);
    json toJson()
    {
        return json{
            {"id", id},
            {"user_id", user_id},
            {"room_id", room_id},
            {"question_id", question_id},
            {"option_id", option_id},
            {"result", result},
        };
    }
};

#endif // ANSWER_HPP
