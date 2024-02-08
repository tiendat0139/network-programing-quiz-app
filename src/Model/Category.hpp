#ifndef CATEGORY_HPP
#define CATEGORY_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include "../../library/json.hpp"
#pragma once
using json = nlohmann::json;
extern std::string source;
class Category
{
public:
    int id;
    std::string name;
    std::string slug;

    Category();

    Category(const std::string &name, const std::string &slug);

    // Constructor without auto-increase id
    Category(int id, const std::string &name, const std::string &slug);

    static std::vector<Category> getAll();
    static Category findById(int categoryId);
    static Category edit(Category &updatedCategory);
    static Category create(const Category &newCategory);
    static void Delete(const Category &categoryToDelete);
    json toJson()
    {
        return json{
            {"id", id},
            {"name", name},
            {"slug", slug},
        };
    }
};

#endif // CATEGORY_HPP
