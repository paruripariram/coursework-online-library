#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <vector>

#include "Catalog.h"
#include "LoanFactory.h"

class User;

class Library {
private:
    std::string name;
    Catalog catalog;
    std::vector<User*> users;
    LoanFactory factory;

public:
    explicit Library(const std::string& name);
    void registerUser(User* user);
    void removeUser(User* user);
    User* findUserByEmail(const std::string& email) const;
    User* findUserByName(const std::string& name) const;
    Catalog& getCatalog();
    LoanFactory& getFactory();
    void printStatistics() const;
};

#endif
