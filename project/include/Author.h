#ifndef AUTHOR_H
#define AUTHOR_H

#include <string>

class Author {
private:
    std::string name;
    std::string biography;

public:
    Author(const std::string& name, const std::string& biography)
        : name(name), biography(biography) {
    }

    std::string getName() const {
        return name;
    }
};

#endif
