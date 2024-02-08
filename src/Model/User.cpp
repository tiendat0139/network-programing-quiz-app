#include "User.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include "../../library/json.hpp"

#define USERS_JSON "../../../database/users.json"

using json = nlohmann::json;

User::User() = default;

// Constructor with auto-increase id
User::User(std::string n, std::string e, std::string p, int s, std::string r)
    : name(n), email(e), password(p), status(s), role(r)
{
    std::vector<User> users = getAll();
    // Auto-increment id based on the last user's id in the USERS_JSON file
    if (!users.empty()) {
        id = users.back().id + 1;
    } else {
        id = 1; // If no one exist, start from id 1
    }
}

// Constructor without auto-increase id
User::User(int i, std::string n, std::string e, std::string p, int s, std::string r)
    : id(i), name(n), email(e), password(p), status(s), role(r) {}

// Constructor with default value of status and role
User::User(std::string n, std::string e, std::string p)
    : name(n), email(e), password(p) {
    // Auto-increment id based on the last user's id in the USERS_JSON file
    std::vector<User> users = getAll();
    if (!users.empty()) {
        id = users.back().id + 1;
    } else {
        id = 1; // If no users exist, start from id 1
    }
    status = 1;
    role = "User";
}

std::vector<User> User::getAll()
{
    std::vector<User> users;

    // Load existing users from JSON
    json jsonData;
    std::ifstream inputFile(USERS_JSON);
    inputFile >> jsonData;
    inputFile.close();

    for (const auto &userData : jsonData["users"])
    {
        User user;
        user.id = userData["id"];
        user.name = userData["name"];
        user.email = userData["email"];
        user.password = userData["password"];
        user.role = userData["role"];
        user.status = userData["status"];

        users.push_back(user);
    }

    return users;
}

User User::findById(int id)
{
    // Load existing answers from JSON
    json jsonData;
    std::ifstream inputFile(USERS_JSON);
    inputFile >> jsonData;
    inputFile.close();

    for (const auto &userData : jsonData["users"])
    {
        if (userData["id"] == id)
        {
            User user;
            user.id = userData["id"];
            user.email = userData["email"];
            user.name = userData["name"];
            user.password = userData["password"];
            user.role = userData["role"];
            user.status = userData["status"];

            return user;
        }
    }

    // Return an empty user if not found
    return User();
}

User User::findByEmail(std::string email)
{
    // Load existing answers from JSON
    json jsonData;
    std::ifstream inputFile(USERS_JSON);
    inputFile >> jsonData;
    inputFile.close();

    for (const auto &userData : jsonData["users"])
    {
        if (userData["email"] == email)
        {
            User user;
            user.id = userData["id"];
            user.email = userData["email"];
            user.name = userData["name"];
            user.password = userData["password"];
            user.role = userData["role"];
            user.status = userData["status"];

            return user;
        }
    }

    // Return an empty user if not found
    return User();
}

User User::edit(User &updatedUser)
{
    // Load existing users from JSON
    json jsonData;
    std::ifstream inputFile(USERS_JSON);
    inputFile >> jsonData;
    inputFile.close();

    // Find and update the user with matching id
    for (auto &user : jsonData["users"])
    {
        if (user["id"] == updatedUser.id)
        {
            user["name"] = updatedUser.name;
            user["email"] = updatedUser.email;
            user["password"] = updatedUser.password;
            user["status"] = updatedUser.status;
            user["role"] = updatedUser.role;
            break;
        }
    }

    // Write the updated data back to JSON file
    std::ofstream outputFile(USERS_JSON);
    outputFile << std::setw(4) << jsonData;
    outputFile.close();

    return updatedUser;
}

User User::create(const User &newUser)
{
    // Load existing users from JSON
    json jsonData;
    std::ifstream inputFile(USERS_JSON);
    inputFile >> jsonData;
    inputFile.close();

    // Add the new user to the JSON data with auto-incremented id
    json newUserJson;
    newUserJson["id"] = newUser.id;
    newUserJson["name"] = newUser.name;
    newUserJson["email"] = newUser.email;
    newUserJson["password"] = newUser.password;
    newUserJson["status"] = newUser.status;
    newUserJson["role"] = newUser.role;

    jsonData["users"].push_back(newUserJson);

    // Write the updated data back to JSON file
    std::ofstream outputFile(USERS_JSON);
    outputFile << std::setw(4) << jsonData;
    outputFile.close();

    return newUser;
}

void User::Delete(const User &userToDelete)
{
    // Load existing users from JSON
    json jsonData;
    std::ifstream inputFile(USERS_JSON);
    inputFile >> jsonData;
    inputFile.close();

    // Find and remove the user with matching id
    auto &usersArray = jsonData["users"];
    usersArray.erase(std::remove_if(usersArray.begin(), usersArray.end(),
                                    [&userToDelete](const auto &user)
                                    {
                                        return user["id"] == userToDelete.id;
                                    }),
                     usersArray.end());

    // Write the updated data back to JSON file
    std::ofstream outputFile(USERS_JSON);
    outputFile << std::setw(4) << jsonData;
    outputFile.close();
}
