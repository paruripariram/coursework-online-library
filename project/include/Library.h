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

    User* findUserByName(const std::string& name) const {
        for (int i = 0; i < static_cast<int>(users.size()); ++i) {
            if (users[i]->hasName(name)) {
                return users[i];
            }
        }
        return nullptr;
    }

    Catalog& getCatalog() { return catalog; }
    LoanFactory& getFactory() { return factory; }
};

#endif
