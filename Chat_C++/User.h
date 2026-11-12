#pragma once
#include <string>

class User {
private:
    std::string login;
    std::string password;
    std::string name;

public:
    User(std::string userLogin,
        std::string userPassword,
        std::string userName);

    std::string getLogin() const;
    std::string getName() const;
    bool checkPassword(const std::string& enteredPassword) const;
};
