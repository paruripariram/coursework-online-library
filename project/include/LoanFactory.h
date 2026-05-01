#ifndef LOANFACTORY_H
#define LOANFACTORY_H

#include <string>
#include <utility>
#include <vector>
#include <iostream>

#include "Book.h"
#include "IObserver.h"
#include "LoanRecord.h"

class LoanFactory {
private:
    std::vector<std::pair<Book*, std::vector<IObserver*>>> queues;

public:
    LoanFactory() {
    }

    ~LoanFactory() {
    }

    LoanRecord* create(Book* book,
                       const std::string& userName,
                       IObserver* observer,
                       const std::string& startDate,
                       const std::string& endDate) {
        if (book == nullptr || observer == nullptr) {
            return nullptr;
        }
        if (book->isAvailable()) {
            book->lock();
            return new LoanRecord(book, userName, startDate, endDate);
        }
        std::pair<Book*, std::vector<IObserver*>>* queue = nullptr;
        for (int i = 0; i < static_cast<int>(queues.size()); ++i) {
            if (queues[i].first == book) {
                queue = &queues[i];
                break;
            }
        }
        if (queue == nullptr) {
            queues.push_back(std::make_pair(book, std::vector<IObserver*>()));
            queue = &queues.back();
        }
        queue->second.push_back(observer);
        std::cout << "Book is busy. You are added to the queue." << "\n";
        return nullptr;
    }

    void notifyBookReleasedByTitle(const std::string& bookTitle) {
        for (int i = 0; i < static_cast<int>(queues.size()); ++i) {
            if (queues[i].first != nullptr && queues[i].first->getTitle() == bookTitle) {
                std::string message = "Book is available: " + bookTitle;
                for (int j = 0; j < static_cast<int>(queues[i].second.size()); ++j) {
                    queues[i].second[j]->notify(message);
                }
                return;
            }
        }
    }
};

#endif
