#ifndef SEARCHCRITERIA_H
#define SEARCHCRITERIA_H

#include <string>

class SearchCriteria {
private:
    std::string title;
    std::string genre;
    std::string author;
    int year;

public:
    SearchCriteria();
    void setTitle(const std::string& newTitle);
    void setGenre(const std::string& newGenre);
    void setAuthor(const std::string& newAuthor);
    void setYear(int newYear);
    void reset();
    bool isEmpty() const;

    std::string getTitle() const;
    std::string getGenre() const;
    std::string getAuthor() const;
    int getYear() const;
};

#endif
