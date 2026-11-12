#pragma once
#include <string>
#include <vector>
#include "User.h"
#include "Message.h"

class Chat {
private:
    std::vector<User> users;
    std::vector<Message> messages;
    int currentUser = -1;

    int findUser(const std::string& login) const;

public:
    void registerUser();
    void loginUser();
    void logoutUser();

    void sendPrivateMessage();
    void showPrivateMessages();

    void sendPublicMessage();
    void showPublicMessages();

    void showMenu();
};
