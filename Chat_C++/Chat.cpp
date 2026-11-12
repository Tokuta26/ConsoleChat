#include "Chat.h"
#include <iostream>
#include <limits>

using namespace std;

int Chat::findUser(const string& login) const {
    for (int i = 0; i < static_cast<int>(users.size()); i++) {
        if (users[i].getLogin() == login) {
            return i;
        }
    }
    return -1;
}

void Chat::registerUser() {
    string login, password, name;

    cout << "\n=== Registration ===\n";
    cout << "Enter login: ";
    cin >> login;

    if (login == "ALL") {
        cout << "This login is reserved!\n";
        return;
    }

    if (findUser(login) != -1) {
        cout << "This login already exists!\n";
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    cout << "Enter name: ";
    cin >> name;

    users.emplace_back(login, password, name);
    cout << "Registration successful!\n";
}

void Chat::loginUser() {
    string login, password;

    cout << "\n=== Login ===\n";
    cout << "Enter login: ";
    cin >> login;

    cout << "Enter password: ";
    cin >> password;

    int index = findUser(login);

    if (index == -1) {
        cout << "User not found!\n";
        return;
    }

    if (!users[index].checkPassword(password)) {
        cout << "Incorrect password!\n";
        return;
    }

    currentUser = index;

    cout << "Welcome, "
        << users[currentUser].getName()
        << "!\n";
}

void Chat::logoutUser() {
    currentUser = -1;
    cout << "You have logged out.\n";
}

void Chat::sendPrivateMessage() {
    if (currentUser == -1) {
        cout << "Please login first!\n";
        return;
    }

    string receiver, text;

    cout << "\n=== Send Private Message ===\n";
    cout << "Enter receiver login: ";
    cin >> receiver;

    if (findUser(receiver) == -1) {
        cout << "User not found!\n";
        return;
    }

    if (receiver == users[currentUser].getLogin()) {
        cout << "You cannot send a message to yourself!\n";
        return;
    }

    cout << "Enter message: ";
    getline(cin >> ws, text);

    if (text.empty()) {
        cout << "Message cannot be empty!\n";
        return;
    }

    string sender = users[currentUser].getLogin();
    messages.emplace_back(sender, receiver, text);

    cout << "Message sent successfully!\n";
}

void Chat::showPrivateMessages() {
    if (currentUser == -1) {
        cout << "Please login first!\n";
        return;
    }

    string login = users[currentUser].getLogin();
    bool found = false;

    cout << "\n=== Private Messages ===\n";

    for (const Message& message : messages) {
        if (message.getReceiver() == login ||
            (message.getSender() == login &&
                message.getReceiver() != "ALL")) {

            cout << message.getSender()
                << " -> "
                << message.getReceiver()
                << ": "
                << message.getText()
                << "\n";

            found = true;
        }
    }

    if (!found) {
        cout << "No private messages yet.\n";
    }
}

void Chat::sendPublicMessage() {
    if (currentUser == -1) {
        cout << "Please login first!\n";
        return;
    }

    string text;

    cout << "\n=== Public Chat ===\n";
    cout << "Enter message: ";
    getline(cin >> ws, text);

    if (text.empty()) {
        cout << "Message cannot be empty!\n";
        return;
    }

    string sender = users[currentUser].getLogin();
    messages.emplace_back(sender, "ALL", text);

    cout << "Public message sent!\n";
}

void Chat::showPublicMessages() {
    if (currentUser == -1) {
        cout << "Please login first!\n";
        return;
    }

    bool found = false;

    cout << "\n=== Public Chat Messages ===\n";

    for (const Message& message : messages) {
        if (message.getReceiver() == "ALL") {
            cout << message.getSender()
                << ": "
                << message.getText()
                << "\n";

            found = true;
        }
    }

    if (!found) {
        cout << "No public messages yet.\n";
    }
}

void Chat::showMenu() {
    int choice;

    while (true) {
        cout << "\n===== CONSOLE CHAT =====\n";

        if (currentUser == -1) {
            cout << "1. Register\n";
            cout << "2. Login\n";
            cout << "0. Exit\n";
        }
        else {
            cout << "Logged in as: "
                << users[currentUser].getName()
                << "\n";

            cout << "1. Send private message\n";
            cout << "2. Show private messages\n";
            cout << "3. Send public message\n";
            cout << "4. Show public messages\n";
            cout << "5. Logout\n";
            cout << "0. Exit\n";
        }

        cout << "Choose: ";

        if (!(cin >> choice)) {
            if (cin.eof()) {
                return;
            }

            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(), '\n'
            );

            cout << "Invalid input!\n";
            continue;
        }

        if (currentUser == -1) {
            switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 0:
                return;
            default:
                cout << "Invalid choice!\n";
            }
        }
        else {
            switch (choice) {
            case 1:
                sendPrivateMessage();
                break;
            case 2:
                showPrivateMessages();
                break;
            case 3:
                sendPublicMessage();
                break;
            case 4:
                showPublicMessages();
                break;
            case 5:
                logoutUser();
                break;
            case 0:
                return;
            default:
                cout << "Invalid choice!\n";
            }
        }
    }
}
