#ifndef LOAN_H
#define LOAN_H

#include <string>

#include "Book.h"

class Loan {
private:
    Book* book;
    std::string userName;
    std::string startDate;
    std::string endDate;
    std::string status;

public:
    Loan(Book* book,
         const std::string& userName,
         const std::string& startDate,
         const std::string& endDate);
    void returnBook();
    void extend(const std::string& newDate);
    bool isOverdue(const std::string& currentDate) const;
    bool isForBook(const std::string& bookTitle) const;
    std::string titleForListing() const;
    void printInfo() const;
};

#endif
