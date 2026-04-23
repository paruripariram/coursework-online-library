#include "Catalog.h"

#include <fstream>
#include <sstream>

void Catalog::addBook(Book* book) {
    if (book == nullptr) {
        return;
    }
    books.push_back(book);
}

void Catalog::removeBook(Book* book) {
    for (int i = 0; i < static_cast<int>(books.size()); ++i) {
        if (books[i] == book) {
            books.erase(books.begin() + i);
            return;
        }
    }
}

std::vector<Book*> Catalog::find(const SearchCriteria& criteria) const {
    std::vector<Book*> result;

    for (int i = 0; i < static_cast<int>(books.size()); ++i) {
        Book* current = books[i];
        bool match = true;

        if (!criteria.getTitle().empty() && current->getTitle() != criteria.getTitle()) {
            match = false;
        }
        if (!criteria.getGenre().empty() && current->getGenre() != criteria.getGenre()) {
            match = false;
        }
        if (!criteria.getAuthor().empty() && current->getAuthor() != criteria.getAuthor()) {
            match = false;
        }
        if (criteria.getYear() != 0 && current->getYear() != criteria.getYear()) {
            match = false;
        }

        if (match) {
            result.push_back(current);
        }
    }

    return result;
}

std::vector<Book*> Catalog::allBooks() const {
    return books;
}

void Catalog::loadFromFile(const std::string& path) {
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

        Author author(authorName, "");
        Book* book = new Book(title, genre, year, author);
        addBook(book);
    }
}

void Catalog::saveToFile(const std::string& path) const {
    std::ofstream output(path);
    if (!output.is_open()) {
        return;
    }

    for (int i = 0; i < static_cast<int>(books.size()); ++i) {
        output << books[i]->getTitle() << ';'
               << books[i]->getGenre() << ';'
               << books[i]->getYear() << ';'
               << books[i]->getAuthor() << "\n";
    }
}

Book* Catalog::findByTitle(const std::string& title) const {
    for (int i = 0; i < static_cast<int>(books.size()); ++i) {
        if (books[i]->getTitle() == title) {
            return books[i];
        }
    }
    return nullptr;
}
