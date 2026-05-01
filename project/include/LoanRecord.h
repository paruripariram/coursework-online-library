#ifndef LOANRECORD_H
#define LOANRECORD_H

#include <iostream>
#include <string>

#include "Book.h"

class LoanRecord {
private:
    Book* book;
    std::string userName;
    std::string startDate;
    std::string endDate;
    std::string status;

public:
    LoanRecord(Book* book,
               const std::string& userName,
               const std::string& startDate,
               const std::string& endDate)
        : book(book), userName(userName), startDate(startDate), endDate(endDate), status("active") {
    }

    void returnBook() {
        if (book != nullptr) {
            book->release();
        }
        status = "returned";
    }

    std::string getStatus() const { return status; }
    std::string getEndDate() const { return endDate; }
    
    std::string titleForListing() const {
        return (book != nullptr) ? book->getTitle() : "";
    }

    void printInfo() const {
        std::cout << "Book: " << titleForListing() << "\n";
        std::cout << "User: " << userName << "\n";
        std::cout << "Dates: " << startDate << " to " << endDate << "\n";
        std::cout << "Status: " << status << "\n";
    }
};

#endif