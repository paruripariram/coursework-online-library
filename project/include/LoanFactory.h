#ifndef LOANFACTORY_H
#define LOANFACTORY_H

#include <string>
#include <utility>
#include <vector>
#include <iostream>

#include "Book.h"
#include "IObserver.h"
#include "LoanRecord.h"
#include "Notification.h"

class LoanFactory {
private:
    std::vector<std::pair<Book*, std::vector<IObserver*>>> queues;

public:
    
    LoanRecord* create(Book* book,
                       const std::string& userName,
                       IObserver* observer,
                       const std::string& startDate,
                       const std::string& endDate) {
        LoanRecord* createdLoan = nullptr;
        bool validInput = (book != nullptr && observer != nullptr);

        if (validInput) {
            if (book->isAvailable()) {
                book->lock();
                createdLoan = new LoanRecord(book, userName, startDate, endDate);
            } else {
                std::pair<Book*, std::vector<IObserver*>>* queue = nullptr;
                int i = 0;
                while (i < static_cast<int>(queues.size()) && queue == nullptr) {
                    if (queues[i].first == book) {
                        queue = &queues[i];
                    }
                    ++i;
                }
                if (queue == nullptr) {
                    queues.push_back(std::make_pair(book, std::vector<IObserver*>()));
                    queue = &queues.back();
                }
                queue->second.push_back(observer);
                std::cout << "Book is busy. You are added to the queue." << "\n";
            }
        }

        return createdLoan;
    }

    void notifyBookReleasedByTitle(const std::string& bookTitle) {
        bool notified = false;
        int i = 0;
        while (i < static_cast<int>(queues.size()) && !notified) {
            if (queues[i].first != nullptr && queues[i].first->getTitle() == bookTitle) {
                std::string message = "Book is available: " + bookTitle;
                // simplified: no timestamp formatting — use empty date
                std::string dateStr("");
                Notification notif(message, dateStr);
                for (int j = 0; j < static_cast<int>(queues[i].second.size()); ++j) {
                    queues[i].second[j]->notify(notif);
                }
                notified = true;
            }
            ++i;
        }
    }
};

#endif
