#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <string>

class Notification {
private:
    std::string message;
    std::string date;

public:
    Notification() = default;
    Notification(const std::string& message, const std::string& date)
        : message(message), date(date) {
    }

    std::string getMessage() const { return message; }
    std::string getDate() const { return date; }
};

#endif
