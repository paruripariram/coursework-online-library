#include "Library.h"

#include <iostream>

#include "User.h"

Library::Library(const std::string& name)
    : name(name) {
}

void Library::registerUser(User* user) {
    if (user == nullptr) {
        return;
    }

    for (int i = 0; i < static_cast<int>(users.size()); ++i) {
        if (users[i] == user) {
            return;
        }
    }

    users.push_back(user);
}

void Library::removeUser(User* user) {
    for (int i = 0; i < static_cast<int>(users.size()); ++i) {
        if (users[i] == user) {
            users.erase(users.begin() + i);
            return;
        }
    }
}

User* Library::findUserByEmail(const std::string& email) const {
    for (int i = 0; i < static_cast<int>(users.size()); ++i) {
        if (users[i]->hasEmail(email)) {
            return users[i];
        }
    }
    return nullptr;
}

Catalog& Library::getCatalog() {
    return catalog;
}

LoanFactory& Library::getFactory() {
    return factory;
}

void Library::printStatistics() const {
    std::cout << "Library: " << name << "\n";
    std::cout << "Users: " << users.size() << "\n";
    std::cout << "Books: " << catalog.allBooks().size() << "\n";

    int totalLoans = 0;
    for (int i = 0; i < static_cast<int>(users.size()); ++i) {
        totalLoans += users[i]->loanCount();
    }
    std::cout << "Active loans: " << totalLoans << "\n";
}
