#ifndef RESERVATIONQUEUE_H
#define RESERVATIONQUEUE_H

#include <string>
#include <vector>

#include "Book.h"
#include "IObserver.h"

class ReservationQueue {
private:
    Book* book;
    std::vector<IObserver*> observers;

public:
    explicit ReservationQueue(Book* book);
    void add(IObserver* observer);
    void remove(IObserver* observer);
    void notifyAll();
    Book* getBook() const;
};

#endif
