#include "SearchCriteria.h"

SearchCriteria::SearchCriteria()
    : title(""), genre(""), author(""), year(0) {
}

void SearchCriteria::setTitle(const std::string& newTitle) {
    title = newTitle;
}

void SearchCriteria::setGenre(const std::string& newGenre) {
    genre = newGenre;
}

void SearchCriteria::setAuthor(const std::string& newAuthor) {
    author = newAuthor;
}

void SearchCriteria::setYear(int newYear) {
    year = newYear;
}

void SearchCriteria::reset() {
    title.clear();
    genre.clear();
    author.clear();
    year = 0;
}

bool SearchCriteria::isEmpty() const {
    return title.empty() && genre.empty() && author.empty() && year == 0;
}

std::string SearchCriteria::getTitle() const {
    return title;
}

std::string SearchCriteria::getGenre() const {
    return genre;
}

std::string SearchCriteria::getAuthor() const {
    return author;
}

int SearchCriteria::getYear() const {
    return year;
}
