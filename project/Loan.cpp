#include "Loan.h"

#include <iostream>

Loan::Loan(Book* book,
           const std::string& userName,
           const std::string& startDate,
           const std::string& endDate)
    : book(book), userName(userName), startDate(startDate), endDate(endDate), status("active") {
}

void Loan::returnBook() {
    if (book != nullptr) {
        book->release();
    }
    status = "returned";
}

void Loan::extend(const std::string& newDate) {
    endDate = newDate;
}

bool Loan::isOverdue(const std::string& currentDate) const {
    if (status != "active") {
        return false;
    }
    return currentDate > endDate;
}

void Loan::printInfo() const {
    std::cout << "Book: " << (book != nullptr ? book->getTitle() : "none") << "\n";
    std::cout << "User: " << userName << "\n";
    std::cout << "Start date: " << startDate << "\n";
    std::cout << "End date: " << endDate << "\n";
    std::cout << "Status: " << status << "\n";
}
