#ifndef LOANFACTORY_H
#define LOANFACTORY_H

#include <string>
#include <vector>

#include "Loan.h"
#include "ReservationQueue.h"

class User;

class LoanFactory {
private:
    std::vector<ReservationQueue*> queues;

public:
    LoanFactory();
    ~LoanFactory();
    Loan* create(Book* book,
                 User* user,
                 const std::string& startDate,
                 const std::string& endDate);
    void notifyBookReleased(Book* book);
};

#endif
