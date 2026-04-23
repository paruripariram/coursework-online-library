#include "Catalog.h"

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
