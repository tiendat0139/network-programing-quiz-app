#include "Option.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "../../library/json.hpp"

using json = nlohmann::json;

#define OPTIONS_JSON "../../../database/options.json"

Option::Option() = default;

// Constructor without auto-increase id
Option::Option(int id, int question_id, const std::string &content, bool correct)
    : id(id), question_id(question_id), content(content), correct(correct) {}

// Constructor with auto-increase id
Option::Option(int question_id, const std::string &content, bool correct)
    : question_id(question_id), content(content), correct(correct)
{
    std::vector<Option> options = getAll();
    // Auto-increment id based on the last option's id in the OPTIONS_JSON file
    if (!options.empty())
    {
        id = options.back().id + 1;
    }
    else
    {
        id = 1; // If no one exist, start from id 1
    }
}

// Constructor with default value of correct
Option::Option(int question_id, const std::string &content)
    : question_id(question_id), content(content) {
        std::vector<Option> options = getAll();
        // Auto-increment id based on the last option's id in the OPTIONS_JSON file
        if (!options.empty()) {
            id = options.back().id + 1;
        } else {
            id = 1; // If no one exist, start from id 1
        }

        correct = false;
    }

std::vector<Option> Option::getAll()
{
    std::vector<Option> options;

    // Load existing options from JSON
    json jsonData;
    std::ifstream inputFile(OPTIONS_JSON);
    inputFile >> jsonData;
    inputFile.close();

    for (const auto &optionData : jsonData["options"])
    {
        Option option;
        option.id = optionData["id"];
        option.question_id = optionData["question_id"];
        option.content = optionData["content"];
        option.correct = optionData["correct"];

        options.push_back(option);
    }

    return options;
}

Option Option::findById(int optionId)
{
    // Load existing options from JSON
    json jsonData;
    std::ifstream inputFile(OPTIONS_JSON);
    inputFile >> jsonData;
    inputFile.close();

    for (const auto &optionData : jsonData["options"])
    {
        if (optionData["id"] == optionId)
        {
            Option option;
            option.id = optionData["id"];
            option.question_id = optionData["question_id"];
            option.content = optionData["content"];
            option.correct = optionData["correct"];

            return option;
        }
    }

    // Return an empty option if not found
    return Option();
}

Option Option::edit(Option &updatedOption)
{
    // Load existing options from JSON
    json jsonData;
    std::ifstream inputFile(OPTIONS_JSON);
    inputFile >> jsonData;
    inputFile.close();

    // Find and update the option with matching id
    for (auto &optionData : jsonData["options"])
    {
        if (optionData["id"] == updatedOption.id)
        {
            optionData["question_id"] = updatedOption.question_id;
            optionData["content"] = updatedOption.content;
            optionData["correct"] = updatedOption.correct;
            break;
        }
    }

    // Write the updated data back to JSON file
    std::ofstream outputFile(OPTIONS_JSON);
    outputFile << std::setw(4) << jsonData;
    outputFile.close();

    return updatedOption;
}

Option Option::create(const Option &newOption)
{
    // Load existing options from JSON
    json jsonData;
    std::ifstream inputFile(OPTIONS_JSON);
    inputFile >> jsonData;
    inputFile.close();

    // Add the new option to the JSON data
    json newOptionJson;
    newOptionJson["id"] = newOption.id;
    newOptionJson["question_id"] = newOption.question_id;
    newOptionJson["content"] = newOption.content;
    newOptionJson["correct"] = newOption.correct;

    jsonData["options"].push_back(newOptionJson);

    // Write the updated data back to JSON file
    std::ofstream outputFile(OPTIONS_JSON);
    outputFile << std::setw(4) << jsonData;
    outputFile.close();

    return newOption;
}

void Option::Delete(const Option &optionToDelete)
{
    // Load existing options from JSON
    json jsonData;
    std::ifstream inputFile(OPTIONS_JSON);
    inputFile >> jsonData;
    inputFile.close();

    // Find and remove the option with matching id
    auto &optionsArray = jsonData["options"];
    optionsArray.erase(std::remove_if(optionsArray.begin(), optionsArray.end(),
                                      [&optionToDelete](const auto &optionData)
                                      {
                                          return optionData["id"] == optionToDelete.id;
                                      }),
                       optionsArray.end());

    // Write the updated data back to JSON file
    std::ofstream outputFile(OPTIONS_JSON);
    outputFile << std::setw(4) << jsonData;
    outputFile.close();
}