#ifndef QUESTION_HPP
#define QUESTION_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include "../../library/json.hpp"
#pragma once
using json = nlohmann::json;
extern std::string source;
class Question
{
public:
    int id;
    std::string title;
    int level;
    int category_id;

    Question();

    // Constructor without auto-increase id
    Question(int id, const std::string &title, int level, int category_id);

    // Constructor with auto-increase id
    Question(const std::string &title, int level, int category_id);

    static std::vector<Question> getAll();
    static Question findById(int id);
    static Question edit(const Question &updatedQuestion);
    static Question create(const Question &newQuestion);
    static void Delete(const Question &questionToDelete);
    json toJson()
    {
          return json{
               {"id", id},
               {"title", title},
               {"level", level},
               {"category_id", category_id},
          };
    };
};

#endif // QUESTION_HPP
