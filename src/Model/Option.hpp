#ifndef OPTION_HPP
#define OPTION_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include "../../library/json.hpp"
#pragma once
using json = nlohmann::json;
extern std::string source;
class Option
{
public:
    int id;
    int question_id;
    std::string content;
    bool correct;

    Option();

    // Constructor without auto-increase id
    Option(int id, int question_id, const std::string &content, bool correct);

    // Constructor with auto-increase id
    Option(int question_id, const std::string &content, bool correct);

    // Constructor with default value of is_right
    Option(int question_id, const std::string &content);

    static std::vector<Option> getAll();
    static Option findById(int optionId);
    static Option edit(Option &updatedOption);
    static Option create(const Option &newOption);
    static void Delete(const Option &optionToDelete);
    json toJson()
    {
        return json{
            {"id", id},
            {"question_id", question_id},
            {"content", content},
            {"correct", correct},
        };
    }
};

#endif // OPTION_HPP
