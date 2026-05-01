#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector>

#include "Author.h"
#include "Review.h"

class Book {
private:
    std::string title;
    std::string genre;
    int year;
    Author author;
    bool available;
    float rating;
    std::vector<Review> reviews;

public:
    Book(const std::string& title,
         const std::string& genre,
         int year,
         const std::string& author)
        : title(title), 
        genre(genre), 
        year(year), 
        author(author, ""), 
        available(true), 
        rating(0.0f) {
    }

    void lock() {
        available = false;
    }

    void release() {
        available = true;
    }

    bool isAvailable() const {
        return available;
    }

    void addReview(const Review& review) {
        reviews.push_back(review);
        int totalScore = 0;
        for (int i = 0; i < static_cast<int>(reviews.size()); ++i) {
            totalScore += reviews[i].getScore();
        }
        rating = static_cast<float>(totalScore) / static_cast<float>(reviews.size());
    }

    std::string getTitle() const {
        return title;
    }

    std::string getGenre() const {
        return genre;
    }

    std::string getAuthor() const {
        return author.getName();
    }

    int getYear() const {
        return year;
    }
};

#endif
