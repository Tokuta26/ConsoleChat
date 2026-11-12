#include "User.h"

User::User(std::string userLogin,
    std::string userPassword,
    std::string userName) {
    login = userLogin;
    password = userPassword;
    name = userName;
}

std::string User::getLogin() const {
    return login;
}

std::string User::getName() const {
    return name;
}

bool User::checkPassword(
    const std::string& enteredPassword) const {
    return password == enteredPassword;
}
