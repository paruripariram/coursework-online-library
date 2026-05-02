#ifndef CATALOG_H
#define CATALOG_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "Book.h"

class Catalog {
private:
    std::vector<Book*> books;

public:
    void addBook(Book* book) {
        if (book != nullptr) {
            books.push_back(book);
        }
    }

    std::vector<Book*> allBooks() const {
        return books;
    }

    Book* findByTitle(const std::string& title) const {
        Book* found = nullptr;
        int i = 0;
        while (i < static_cast<int>(books.size()) && found == nullptr) {
            if (books[i]->getTitle() == title) {
                found = books[i];
            }
            ++i;
        }
        return found;
    }

    std::vector<Book*> find(const std::string& mode, const std::string& value) const {
        std::vector<Book*> result;
        for (int i = 0; i < static_cast<int>(books.size()); ++i) {
            Book* current = books[i];
            if ((mode == "genre" && current->getGenre() == value) ||
             (mode == "author" && current->getAuthor() == value) ||
              (mode != "genre" && mode != "author" &&
                 current->getTitle() == value)) {
                result.push_back(current);
            }
        }
        return result;
    }

    void loadFromFile(const std::string& path) {
        std::ifstream input(path);
        if (input.is_open()) {
            std::string line;
            while (std::getline(input, line)) {
                bool validLine = !line.empty();
                std::stringstream stream(line);
                std::string title;
                std::string genre;
                std::string yearText;
                std::string authorName;

                if (validLine) {
                    validLine = static_cast<bool>(std::getline(stream, title, ';'));
                }
                if (validLine) {
                    validLine = static_cast<bool>(std::getline(stream, genre, ';'));
                }
                if (validLine) {
                    validLine = static_cast<bool>(std::getline(stream, yearText, ';'));
                }
                if (validLine) {
                    validLine = static_cast<bool>(std::getline(stream, authorName, ';'));
                }

                int year = 0;
                if (validLine) {
                    try {
                        year = std::stoi(yearText);
                    } catch (...) {
                        validLine = false;
                    }
                }
                if (validLine) {
                    addBook(new Book(title, genre, year, authorName));
                }
            }
        }
    }

};

#endif
