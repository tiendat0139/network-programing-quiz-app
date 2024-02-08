#include "Question.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "../../library/json.hpp"

using json = nlohmann::json;

#define QUESTIONS_JSON "../../../database/questions.json"

Question::Question() = default;

// Constructor without auto-increase id
Question::Question(int id, const std::string &title, int level, int category_id)
    : id(id), title(title), level(level), category_id(category_id) {}

// Constructor with auto-increase id
Question::Question(const std::string &title, int level, int category_id)
    : id(id), title(title), level(level), category_id(category_id) {
    std::vector<Question> questions = getAll();
    if (!questions.empty()) {
        id = questions.back().id + 1;
    } else {
        id = 1; // If no one exist, start from id 1
    }
}


std::vector<Question> Question::getAll()
{
    std::vector<Question> questions;

    // Load existing questions from JSON
    json jsonData;
    std::ifstream inputFile(QUESTIONS_JSON);
    inputFile >> jsonData;
    inputFile.close();

    for (const auto &questionData : jsonData["questions"])
    {
        Question question;
        question.id = questionData["id"];
        question.title = questionData["title"];
        question.level = questionData["level"];
        question.category_id = questionData["category_id"];

        questions.push_back(question);
    }

    return questions;
}

Question Question::findById(int id)
{
    // Load existing questions from JSON
    json jsonData;
    std::ifstream inputFile(QUESTIONS_JSON);
    inputFile >> jsonData;
    inputFile.close();

    for (const auto &questionData : jsonData["questions"])
    {
        if (questionData["id"] == id)
        {
            Question question;
            question.id = questionData["id"];
            question.title = questionData["title"];
            question.level = questionData["level"];
            question.category_id = questionData["category_id"];

            return question;
        }
    }

    // Return an empty question if not found
    return Question();
}

Question Question::edit(const Question &updatedQuestion)
{
    // Load existing questions from JSON
    json jsonData;
    std::ifstream inputFile(QUESTIONS_JSON);
    inputFile >> jsonData;
    inputFile.close();

    // Find and update the question with matching id
    for (auto &questionData : jsonData["questions"])
    {
        if (questionData["id"] == updatedQuestion.id)
        {
            questionData["title"] = updatedQuestion.title;
            questionData["level"] = updatedQuestion.level;
            questionData["category_id"] = updatedQuestion.category_id;
            break;
        }
    }

    // Write the updated data back to JSON file
    std::ofstream outputFile(QUESTIONS_JSON);
    outputFile << std::setw(4) << jsonData;
    outputFile.close();

    return updatedQuestion;
}

Question Question::create(const Question &newQuestion)
{
    // Load existing questions from JSON
    json jsonData;
    std::ifstream inputFile(QUESTIONS_JSON);
    inputFile >> jsonData;
    inputFile.close();

    // Add the new question to the JSON data
    json newQuestionJson;
    newQuestionJson["id"] = newQuestion.id;
    newQuestionJson["title"] = newQuestion.title;
    newQuestionJson["level"] = newQuestion.level;
    newQuestionJson["category_id"] = newQuestion.category_id;

    jsonData["questions"].push_back(newQuestionJson);

    // Write the updated data back to JSON file
    std::ofstream outputFile(QUESTIONS_JSON);
    outputFile << std::setw(4) << jsonData;
    outputFile.close();

    return newQuestion;
}

void Question::Delete(const Question &questionToDelete)
{
    // Load existing questions from JSON
    json jsonData;
    std::ifstream inputFile(QUESTIONS_JSON);
    inputFile >> jsonData;
    inputFile.close();

    // Find and remove the question with matching id
    auto &questionsArray = jsonData["questions"];
    questionsArray.erase(std::remove_if(questionsArray.begin(), questionsArray.end(),
                                        [&questionToDelete](const auto &questionData)
                                        {
                                            return questionData["id"] == questionToDelete.id;
                                        }),
                         questionsArray.end());

    // Write the updated data back to JSON file
    std::ofstream outputFile(QUESTIONS_JSON);
    outputFile << std::setw(4) << jsonData;
    outputFile.close();
}