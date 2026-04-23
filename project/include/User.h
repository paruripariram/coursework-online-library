#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

#include "IObserver.h"
#include "Subscription.h"

class Book;
class Loan;
class LoanFactory;
class SearchCriteria;

class User : public IObserver {
private:
    std::string name;
    std::string email;
    Subscription subscription;
    std::vector<Loan*> loans;

public:
    User(const std::string& name,
         const std::string& email,
         const Subscription& subscription);
    void notify(const std::string& message) override;
    Loan* borrowBookAndTrack(Book* book,
                             LoanFactory& factory,
                             const std::string& startDate,
                             const std::string& endDate);
    void borrowBook(Book* book,
                    LoanFactory& factory,
                    const std::string& startDate,
                    const std::string& endDate);
    void returnLoan(Loan* loan);
    void returnBookByTitle(const std::string& bookTitle, LoanFactory& factory);
    void leaveReview(Book* book,
                     const std::string& text,
                     int score,
                     const std::string& date);
    void setFilters(SearchCriteria& criteria);
    void printInfo() const;
    std::string getName() const;
    bool hasEmail(const std::string& value) const;
    int loanCount() const;
};

#endif
