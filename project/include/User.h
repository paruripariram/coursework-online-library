#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <iostream>

#include "Book.h"
#include "IObserver.h"
#include "Notification.h"
#include "LoanRecord.h"
#include "Review.h"
#include "Subscription.h"
#include "LoanFactory.h"

class User : public IObserver {
private:
    std::string name;
    std::string email;
    Subscription subscription;
    std::vector<LoanRecord> loans;
    std::vector<Notification> notifications;

public:
    User(const std::string& name,
         const std::string& email,
         int loanLimit)
        : name(name), email(email), subscription("standard", loanLimit, "") {
    }

    void notify(const Notification& notification) override {
        std::cout << "[" << name << "]: " << notification.getMessage() << " (" << notification.getDate() << ")\n";
        notifications.push_back(notification);
    }

    LoanRecord* borrowBookAndTrack(Book* book,
                                   LoanFactory& factory,
                                   const std::string& startDate,
                                   const std::string& endDate) {
        LoanRecord* newLoan = nullptr;
        bool canBorrow = (book != nullptr);

        if (canBorrow && static_cast<int>(loans.size()) >= subscription.getBookLimit()) {
            std::cout << "Loan limit reached." << "\n";
            canBorrow = false;
        }

        if (canBorrow) {
            newLoan = factory.create(book, name, this, startDate, endDate);
            if (newLoan != nullptr) {
                loans.push_back(*newLoan);
                delete newLoan;
            }
        }

        return newLoan;
    }

    void leaveReview(Book* book,
                     const std::string& text,
                     int score,
                     const std::string& date) {
        if (book != nullptr) {
            Review review(book->getTitle(), name, text, score, date);
            book->addReview(review);
        }
    }

    bool returnBookByIndex(int index, LoanFactory& factory) {
        bool returned = false;

        if (index >= 0 && index < static_cast<int>(loans.size())) {
            LoanRecord& loan = loans[index];
            std::string bookTitle = loan.titleForListing();
            loan.returnBook();
            loans.erase(loans.begin() + index);
            if (!bookTitle.empty()) {
                factory.notifyBookReleasedByTitle(bookTitle);
            }
            returned = true;
        }

        return returned;
    }

    bool hasName(const std::string& value) const {
        return name == value;
    }

    bool hasActiveLoans() const {
        return !loans.empty();
    }

    void printLoans() const {
        for (int i = 0; i < static_cast<int>(loans.size()); ++i) {
            std::cout << "[" << i + 1 << "]\n";
            loans[i].printInfo();
        }
    }

    std::string getName() const {
        return name;
    }

    bool hasEmail(const std::string& value) const {
        return email == value;
    }

    int loanCount() const {
        return static_cast<int>(loans.size());
    }
};

#endif
