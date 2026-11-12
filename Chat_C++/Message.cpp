#include "Message.h"

Message::Message(std::string messageSender,
    std::string messageReceiver,
    std::string messageText) {
    sender = messageSender;
    receiver = messageReceiver;
    text = messageText;
}

std::string Message::getSender() const {
    return sender;
}

std::string Message::getReceiver() const {
    return receiver;
}

std::string Message::getText() const {
    return text;
}
