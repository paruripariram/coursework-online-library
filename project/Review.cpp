#include "Review.h"

#include <iostream>

Review::Review(const std::string& bookTitle,
               const std::string& text,
               int score,
               const std::string& userName,
               const std::string& date)
    : bookTitle(bookTitle), text(text), score(score), userName(userName), date(date) {
}

int Review::getScore() const {
    return score;
}

void Review::update(const std::string& newText, int newScore) {
    text = newText;
    score = newScore;
}

void Review::printInfo() const {
    std::cout << "Book: " << bookTitle << "\n";
    std::cout << "User: " << userName << "\n";
    std::cout << "Date: " << date << "\n";
    std::cout << "Score: " << score << "\n";
    std::cout << "Text: " << text << "\n";
}
