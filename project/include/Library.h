#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <vector>

#include "Catalog.h"
#include "LoanFactory.h"
#include "User.h"

class Library {
private:
    std::string name;
    Catalog catalog;
    std::vector<User*> users;
    LoanFactory factory;

public:
    explicit Library(const std::string& name)
        : name(name) {
    }

    void registerUser(User* user) {
        bool canAdd = (user != nullptr);
        int i = 0;
        while (canAdd && i < static_cast<int>(users.size())) {
            if (users[i] == user) {
                canAdd = false;
            }
            ++i;
        }
        if (canAdd) {
            users.push_back(user);
        }
    }

    User* findUserByName(const std::string& name) const {
        User* found = nullptr;
        int i = 0;
        while (i < static_cast<int>(users.size()) && found == nullptr) {
            if (users[i]->hasName(name)) {
                found = users[i];
            }
            ++i;
        }
        return found;
    }

    Catalog& getCatalog() { return catalog; }
    LoanFactory& getFactory() { return factory; }
};

#endif
