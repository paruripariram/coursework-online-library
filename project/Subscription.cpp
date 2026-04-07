#include "Subscription.h"

Subscription::Subscription(const std::string& type, int bookLimit, const std::string& endDate)
    : type(type), active(true), bookLimit(bookLimit), endDate(endDate) {
}

bool Subscription::isActive() const {
    return active;
}

int Subscription::getLimit() const {
    return bookLimit;
}

void Subscription::changeType(const std::string& newType) {
    type = newType;
    if (newType == "basic") {
        bookLimit = 1;
    } else if (newType == "standard") {
        bookLimit = 3;
    } else if (newType == "premium") {
        bookLimit = 10;
    }
}
