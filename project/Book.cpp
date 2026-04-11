#include "Book.h"

#include <iostream>

Book::Book(const std::string& title,
           const std::string& genre,
           int year,
           const Author& author)
    : title(title), genre(genre), year(year), author(author), available(true), rating(0.0f) {
}

void Book::lock() {
    available = false;
}

void Book::release() {
    available = true;
}

bool Book::isAvailable() const {
    return available;
}

void Book::addReview(const Review& review) {
    reviews.push_back(review);
    int totalScore = 0;
    for (int i = 0; i < static_cast<int>(reviews.size()); ++i) {
        totalScore += reviews[i].getScore();
    }
    rating = static_cast<float>(totalScore) / static_cast<float>(reviews.size());
}

void Book::printInfo() const {
    std::cout << "Title: " << title << "\n";
    std::cout << "Genre: " << genre << "\n";
    std::cout << "Year: " << year << "\n";
    author.printInfo();
    std::cout << "Available: " << (available ? "yes" : "no") << "\n";
    std::cout << "Rating: " << rating << "\n";
    std::cout << "Reviews count: " << reviews.size() << "\n";
}

std::string Book::getTitle() const {
    return title;
}

std::string Book::getGenre() const {
    return genre;
}

std::string Book::getAuthor() const {
    return author.asCatalogText();
}

int Book::getYear() const {
    return year;
}
