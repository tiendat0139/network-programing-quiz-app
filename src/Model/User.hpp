// User.hpp

#ifndef USER_HPP
#define USER_HPP

#include <vector>
#include "../../library/json.hpp"
#pragma once
using json = nlohmann::json;
extern std::string source;
class User
{
public:
    int id;
    std::string name;
    std::string email;
    std::string password;
    int status;
    std::string role;

    User();
    User(std::string n, std::string e, std::string p, int s, std::string r);
    User(int i, std::string n, std::string e, std::string p, int s, std::string r);
    User(std::string n, std::string e, std::string p);

    static std::vector<User> getAll();
    static User findById(int id);
    static User findByEmail(std::string email);
    static User edit(User &updatedUser);
    static User create(const User &newUser);
    static void Delete(const User &userToDelete);
    json toJson()
    {
        return json{
            {"id", id},
            {"name", name},
            {"email", email},
            // {"password", password},
            {"status", status},
            {"role", role},
        };
    }
};

#endif // USER_HPP
