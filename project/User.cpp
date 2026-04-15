#include "User.h"

#include <iostream>

#include "Book.h"
#include "Loan.h"
#include "LoanFactory.h"
#include "Review.h"
#include "SearchCriteria.h"

User::User(const std::string& name,
           const std::string& email,
           const Subscription& subscription)
    : name(name), email(email), subscription(subscription) {
}

void User::notify(const std::string& message) {
    std::cout << "[" << name << "]: " << message << "\n";
}

void User::borrowBook(Book* book,
                      LoanFactory& factory,
                      const std::string& startDate,
                      const std::string& endDate) {
    if (book == nullptr) {
        return;
    }

    if (!subscription.isActive()) {
        std::cout << "Subscription is inactive." << "\n";
        return;
    }

    if (static_cast<int>(loans.size()) >= subscription.getLimit()) {
        std::cout << "Loan limit reached." << "\n";
        return;
    }

    Loan* newLoan = factory.create(book, this, startDate, endDate);
    if (newLoan != nullptr) {
        loans.push_back(newLoan);
    }
}

void User::returnLoan(Loan* loan) {
    if (loan == nullptr) {
        return;
    }

    loan->returnBook();

    for (int i = 0; i < static_cast<int>(loans.size()); ++i) {
        if (loans[i] == loan) {
            loans.erase(loans.begin() + i);
            break;
        }
    }
}

void User::leaveReview(Book* book,
                       const std::string& text,
                       int score,
                       const std::string& date) {
    if (book == nullptr) {
        return;
    }

    Review review(book->getTitle(), text, score, name, date);
    book->addReview(review);
}

void User::setFilters(SearchCriteria& criteria) {
    criteria.reset();

    std::string input;
    std::cout << "Title filter: ";
    std::getline(std::cin, input);
    if (!input.empty()) {
        criteria.setTitle(input);
    }

    std::cout << "Genre filter: ";
    std::getline(std::cin, input);
    if (!input.empty()) {
        criteria.setGenre(input);
    }

    std::cout << "Author filter: ";
    std::getline(std::cin, input);
    if (!input.empty()) {
        criteria.setAuthor(input);
    }

    int yearValue = 0;
    std::cout << "Year filter (0 for any): ";
    std::cin >> yearValue;
    std::cin.ignore(10000, '\n');
    if (yearValue != 0) {
        criteria.setYear(yearValue);
    }
}

void User::printInfo() const {
    std::cout << "Name: " << name << "\n";
    std::cout << "Email: " << email << "\n";
    std::cout << "Current loans: " << loans.size() << "\n";
    std::cout << "Subscription limit: " << subscription.getLimit() << "\n";
}

std::string User::getName() const {
    return name;
}
