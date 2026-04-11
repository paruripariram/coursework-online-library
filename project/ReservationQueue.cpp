#include "ReservationQueue.h"

ReservationQueue::ReservationQueue(Book* book)
    : book(book) {
}

void ReservationQueue::add(IObserver* observer) {
    if (observer == nullptr) {
        return;
    }

    for (int i = 0; i < static_cast<int>(observers.size()); ++i) {
        if (observers[i] == observer) {
            return;
        }
    }

    observers.push_back(observer);
}

void ReservationQueue::remove(IObserver* observer) {
    for (int i = 0; i < static_cast<int>(observers.size()); ++i) {
        if (observers[i] == observer) {
            observers.erase(observers.begin() + i);
            return;
        }
    }
}

void ReservationQueue::notifyAll() {
    std::string message = "Book is available: " + book->getTitle();
    for (int i = 0; i < static_cast<int>(observers.size()); ++i) {
        observers[i]->notify(message);
    }
}

Book* ReservationQueue::getBook() const {
    return book;
}
