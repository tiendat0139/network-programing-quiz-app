#include "Category.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "../../library/json.hpp"

using json = nlohmann::json;

#define CATEGORIES_JSON "../../../database/categories.json"

Category::Category() = default;

Category::Category(const std::string &name, const std::string &slug)
    : name(name), slug(slug)
{
    // Auto-increment id based on the last category's id
    std::vector<Category> categories = getAll();

    if (!categories.empty())
    {
        id = categories.back().id + 1;
    }
    else
    {
        id = 1;
    }
}

// Constructor without auto-increase id
Category::Category(int id, const std::string &name, const std::string &slug)
    : id(id), name(name), slug(slug) {}

std::vector<Category> Category::getAll()
{
    std::vector<Category> categories;

    // Load existing categories from JSON
    json jsonData;
    std::ifstream inputFile(CATEGORIES_JSON);
    inputFile >> jsonData;
    inputFile.close();

    for (const auto &categoryData : jsonData["categories"])
    {
        Category category;
        category.id = categoryData["id"];
        category.name = categoryData["name"];
        category.slug = categoryData["slug"];

        categories.push_back(category);
    }

    return categories;
}

Category Category::findById(int categoryId)
{
    // Load existing categories from JSON
    json jsonData;
    std::ifstream inputFile(CATEGORIES_JSON);
    inputFile >> jsonData;
    inputFile.close();

    for (const auto &categoryData : jsonData["categories"])
    {
        if (categoryData["id"] == categoryId)
        {
            Category category;
            category.id = categoryData["id"];
            category.name = categoryData["name"];
            category.slug = categoryData["slug"];

            return category;
        }
    }

    // Return an empty category if not found
    return Category();
}

Category Category::edit(Category &updatedCategory)
{
    // Load existing categories from JSON
    json jsonData;
    std::ifstream inputFile(CATEGORIES_JSON);
    inputFile >> jsonData;
    inputFile.close();

    // Find and update the category with matching id
    for (auto &categoryData : jsonData["categories"])
    {
        if (categoryData["id"] == updatedCategory.id)
        {
            categoryData["name"] = updatedCategory.name;
            categoryData["slug"] = updatedCategory.slug;
            break;
        }
    }

    // Write the updated data back to JSON file
    std::ofstream outputFile(CATEGORIES_JSON);
    outputFile << std::setw(4) << jsonData;
    outputFile.close();

    return updatedCategory;
}

Category Category::create(const Category &newCategory)
{
    // Load existing categories from JSON
    json jsonData;
    std::ifstream inputFile(CATEGORIES_JSON);
    inputFile >> jsonData;
    inputFile.close();

    // Add the new category to the JSON data
    json newCategoryJson;
    newCategoryJson["id"] = newCategory.id;
    newCategoryJson["name"] = newCategory.name;
    newCategoryJson["slug"] = newCategory.slug;

    jsonData["categories"].push_back(newCategoryJson);

    // Write the updated data back to JSON file
    std::ofstream outputFile(CATEGORIES_JSON);
    outputFile << std::setw(4) << jsonData;
    outputFile.close();

    return newCategory;
}

void Category::Delete(const Category &categoryToDelete)
{
    // Load existing categories from JSON
    json jsonData;
    std::ifstream inputFile(CATEGORIES_JSON);
    inputFile >> jsonData;
    inputFile.close();

    // Find and remove the category with matching id
    auto &categoriesArray = jsonData["categories"];
    categoriesArray.erase(std::remove_if(categoriesArray.begin(), categoriesArray.end(),
                                         [&categoryToDelete](const auto &categoryData)
                                         {
                                             return categoryData["id"] == categoryToDelete.id;
                                         }),
                          categoriesArray.end());

    // Write the updated data back to JSON file
    std::ofstream outputFile(CATEGORIES_JSON);
    outputFile << std::setw(4) << jsonData;
    outputFile.close();
}
