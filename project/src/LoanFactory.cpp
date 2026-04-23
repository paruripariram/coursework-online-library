#include "LoanFactory.h"

#include <iostream>

#include "User.h"

LoanFactory::LoanFactory() {
}

LoanFactory::~LoanFactory() {
    for (int i = 0; i < static_cast<int>(queues.size()); ++i) {
        delete queues[i];
    }
}

Loan* LoanFactory::create(Book* book,
                          User* user,
                          const std::string& startDate,
                          const std::string& endDate) {
    if (book == nullptr || user == nullptr) {
        return nullptr;
    }

    if (book->isAvailable()) {
        book->lock();
        return new Loan(book, user->getName(), startDate, endDate);
    }

    ReservationQueue* queue = nullptr;
    for (int i = 0; i < static_cast<int>(queues.size()); ++i) {
        if (queues[i]->getBook() == book) {
            queue = queues[i];
            break;
        }
    }

    if (queue == nullptr) {
        queue = new ReservationQueue(book);
        queues.push_back(queue);
    }

    queue->add(user);
    std::cout << "Book is busy. You are added to the queue." << "\n";
    return nullptr;
}

void LoanFactory::notifyBookReleased(Book* book) {
    if (book == nullptr) {
        return;
    }

    for (int i = 0; i < static_cast<int>(queues.size()); ++i) {
        if (queues[i]->getBook() == book) {
            queues[i]->notifyAll();
            return;
        }
    }
}

void LoanFactory::notifyBookReleasedByTitle(const std::string& bookTitle) {
    for (int i = 0; i < static_cast<int>(queues.size()); ++i) {
        if (queues[i]->getBook() != nullptr && queues[i]->getBook()->getTitle() == bookTitle) {
            queues[i]->notifyAll();
            return;
        }
    }
}
