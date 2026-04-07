#ifndef AUTHOR_H
#define AUTHOR_H

#include <string>

class Author {
private:
    std::string name;
    std::string biography;

public:
    Author(const std::string& name, const std::string& biography);
    void printInfo() const;
};

#endif
