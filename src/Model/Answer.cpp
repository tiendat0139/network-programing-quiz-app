#include "Answer.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "../../library/json.hpp"

using json = nlohmann::json;

#define ANSWERS_JSON "../../../database/answers.json"

Answer::Answer() = default;

// Constructor with auto-increase id
Answer::Answer(int user_id, int room_id, int question_id, int option_id, int result)
    : user_id(user_id), room_id(room_id), question_id(question_id), option_id(option_id), result(result)
{
    std::vector<Answer> answers = getAll();
    // Auto-increment id based on the last answer's id in the ANSWERS_JSON file
    if (!answers.empty())
    {
        id = answers.back().id + 1;
    }
    else
    {
        id = 1; // If no one exist, start from id 1
    }
}

Answer::Answer(int id, int user_id, int room_id, int question_id, int option_id, int result) 
    : id(id), user_id(user_id), room_id(room_id), question_id(question_id), option_id(option_id), result(result) {}

// Constructor with default value of option_id and result_id
Answer::Answer(int user_id, int room_id, int question_id)
    : user_id(user_id), room_id(room_id), question_id(question_id)
{

    std::vector<Answer> answers = getAll();
    // Auto-increment id based on the last answer's id in the ANSWERS_JSON file
    if (!answers.empty())
    {
        id = answers.back().id + 1;
    }
    else
    {
        id = 1; // If no one exist, start from id 1
    }
    option_id = 0;
    result = 0;
}

std::vector<Answer> Answer::getAll()
{
    std::vector<Answer> answers;

    // Load existing answers from JSON
    json jsonData;
    std::ifstream inputFile(ANSWERS_JSON);
    inputFile >> jsonData;
    inputFile.close();

    for (const auto &answerData : jsonData["answers"])
    {
        Answer answer;
        answer.id = answerData["id"];
        answer.user_id = answerData["user_id"];
        answer.room_id = answerData["room_id"];
        answer.question_id = answerData["question_id"];
        answer.option_id = answerData["option_id"];
        answer.result = answerData["result"];

        answers.push_back(answer);
    }

    return answers;
}

Answer Answer::findById(int id)
{
    // Load existing answers from JSON
    json jsonData;
    std::ifstream inputFile(ANSWERS_JSON);
    inputFile >> jsonData;
    inputFile.close();

    for (const auto &answerData : jsonData["answers"])
    {
        if (answerData["id"] == id)
        {
            Answer answer;
            answer.id = answerData["id"];
            answer.user_id = answerData["user_id"];
            answer.room_id = answerData["room_id"];
            answer.question_id = answerData["question_id"];
            answer.option_id = answerData["option_id"];
            answer.result = answerData["result"];

            return answer;
        }
    }

    // Return an empty answer if not found
    return Answer();
}

Answer Answer::edit(const Answer &updatedAnswer)
{
    // Load existing answers from JSON
    json jsonData;
    std::ifstream inputFile(ANSWERS_JSON);
    inputFile >> jsonData;
    inputFile.close();

    // Find and update the answer with matching id
    for (auto &answerData : jsonData["answers"])
    {
        if (answerData["id"] == updatedAnswer.id)
        {
            answerData["user_id"] = updatedAnswer.user_id;
            answerData["room_id"] = updatedAnswer.room_id;
            answerData["question_id"] = updatedAnswer.question_id;
            answerData["option_id"] = updatedAnswer.option_id;
            answerData["result"] = updatedAnswer.result;
            break;
        }
    }

    // Write the updated data back to JSON file
    std::ofstream outputFile(ANSWERS_JSON);
    outputFile << std::setw(4) << jsonData;
    outputFile.close();

    return updatedAnswer;
}

Answer Answer::create(const Answer &newAnswer)
{
    // Load existing answers from JSON
    json jsonData;
    std::ifstream inputFile(ANSWERS_JSON);
    inputFile >> jsonData;
    inputFile.close();

    // Add the new answer to the JSON data
    json newAnswerJson;
    newAnswerJson["id"] = newAnswer.id;
    newAnswerJson["user_id"] = newAnswer.user_id;
    newAnswerJson["room_id"] = newAnswer.room_id;
    newAnswerJson["question_id"] = newAnswer.question_id;
    newAnswerJson["option_id"] = newAnswer.option_id;
    newAnswerJson["result"] = newAnswer.result;

    jsonData["answers"].push_back(newAnswerJson);

    // Write the updated data back to JSON file
    std::ofstream outputFile(ANSWERS_JSON);
    outputFile << std::setw(4) << jsonData;
    outputFile.close();

    return newAnswer;
}

void Answer::Delete(const Answer &answerToDelete)
{
    // Load existing answers from JSON
    json jsonData;
    std::ifstream inputFile(ANSWERS_JSON);
    inputFile >> jsonData;
    inputFile.close();

    // Find and remove the answer with matching id
    auto &answersArray = jsonData["answers"];
    answersArray.erase(std::remove_if(answersArray.begin(), answersArray.end(),
                                      [&answerToDelete](const auto &answerData)
                                      {
                                          return answerData["id"] == answerToDelete.id;
                                      }),
                       answersArray.end());

    // Write the updated data back to JSON file
    std::ofstream outputFile(ANSWERS_JSON);
    outputFile << std::setw(4) << jsonData;
    outputFile.close();
}
