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
        for (int i = 0; i < static_cast<int>(books.size()); ++i) {
            if (books[i]->getTitle() == title) {
                return books[i];
            }
        }
        return nullptr;
    }

    std::vector<Book*> find(const std::string& mode, const std::string& value) const {
        std::vector<Book*> result;
        for (int i = 0; i < static_cast<int>(books.size()); ++i) {
            Book* current = books[i];
            if ((mode == "genre" && current->getGenre() == value) || (mode == "author" && current->getAuthor() == value) || (mode != "genre" && mode != "author" && current->getTitle() == value)) {
                result.push_back(current);
            }
        }
        return result;
    }

    void loadFromFile(const std::string& path) {
        std::ifstream input(path);
        if (!input.is_open()) {
            return;
        }
        std::string line;
        while (std::getline(input, line)) {
            if (line.empty()) {
                continue;
            }
            std::stringstream stream(line);
            std::string title;
            std::string genre;
            std::string yearText;
            std::string authorName;
            if (!std::getline(stream, title, ';')) {
                continue;
            }
            if (!std::getline(stream, genre, ';')) {
                continue;
            }
            if (!std::getline(stream, yearText, ';')) {
                continue;
            }
            if (!std::getline(stream, authorName, ';')) {
                continue;
            }
            int year = 0;
            try {
                year = std::stoi(yearText);
            } catch (...) {
                continue;
            }
            addBook(new Book(title, genre, year, authorName));
        }
    }

    void saveToFile(const std::string& path) const {
        std::ofstream output(path);
        if (!output.is_open()) {
            return;
        }
        for (int i = 0; i < static_cast<int>(books.size()); ++i) {
            output << books[i]->getTitle() << ';' << books[i]->getGenre() << ';' << books[i]->getYear() << ';' << books[i]->getAuthor() << "\n";
        }
    }
};

#endif
