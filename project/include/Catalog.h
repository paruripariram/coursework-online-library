#ifndef CATALOG_H
#define CATALOG_H

#include <string>
#include <vector>

#include "Book.h"
#include "SearchCriteria.h"

class Catalog {
private:
    std::vector<Book*> books;

public:
    void addBook(Book* book);
    void removeBook(Book* book);
    std::vector<Book*> find(const SearchCriteria& criteria) const;
    std::vector<Book*> allBooks() const;
    void loadFromFile(const std::string& path);
    void saveToFile(const std::string& path) const;
    Book* findByTitle(const std::string& title) const;
};

#endif
