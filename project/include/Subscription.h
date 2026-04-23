#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

#include <string>

class Subscription {
private:
    std::string type;
    bool active;
    int bookLimit;
    std::string endDate;

public:
    Subscription(const std::string& type, int bookLimit, const std::string& endDate);
    bool isActive() const;
    int getLimit() const;
    void changeType(const std::string& newType);
};

#endif
