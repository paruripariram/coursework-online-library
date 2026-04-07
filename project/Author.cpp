#include "Author.h"

#include <iostream>

Author::Author(const std::string& name, const std::string& biography)
    : name(name), biography(biography) {
}

void Author::printInfo() const {
    std::cout << "Author: " << name << "\n";
    std::cout << "Biography: " << biography << "\n";
}
