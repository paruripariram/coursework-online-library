#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

#include <string>

class Subscription {
private:
    std::string type;
    int bookLimit;
    std::string endDate;

public:
    Subscription(const std::string& type = "standard",
                 int bookLimit = 0,
                 const std::string& endDate = "")
        : type(type), bookLimit(bookLimit), endDate(endDate) {
    }

    int getBookLimit() const { return bookLimit; }
};

#endif