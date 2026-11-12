#pragma once
#include <string>

class Message {
private:
    std::string sender;
    std::string receiver;
    std::string text;

public:
    Message(std::string messageSender,
        std::string messageReceiver,
        std::string messageText);

    std::string getSender() const;
    std::string getReceiver() const;
    std::string getText() const;
};
#pragma once
