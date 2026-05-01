#ifndef REVIEW_H
#define REVIEW_H

#include <string>

class Review {
private:
    std::string bookTitle;
    std::string userName;
    std::string text;
    int score;
    std::string date;

public:
    Review(const std::string& bookTitle,
           const std::string& userName,
           const std::string& text,
           int score,
           const std::string& date)
        : bookTitle(bookTitle), userName(userName), text(text), score(score), date(date) {
    }

    int getScore() const { return score; }
};

#endif