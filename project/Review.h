#ifndef REVIEW_H
#define REVIEW_H

#include <string>

class Review {
private:
    std::string bookTitle;
    std::string text;
    int score;
    std::string userName;
    std::string date;

public:
    Review(const std::string& bookTitle,
           const std::string& text,
           int score,
           const std::string& userName,
           const std::string& date);
    int getScore() const;
    void update(const std::string& newText, int newScore);
    void printInfo() const;
};

#endif
