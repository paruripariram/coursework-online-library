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
         const Author& author);
    void lock();
    void release();
    bool isAvailable() const;
    void addReview(const Review& review);
    void printInfo() const;
    std::string getTitle() const;
    std::string getGenre() const;
    std::string getAuthor() const;
    int getYear() const;
};

#endif
