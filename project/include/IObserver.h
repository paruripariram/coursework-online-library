#ifndef IOBSERVER_H
#define IOBSERVER_H

#include "Notification.h"

class IObserver {
public:
    virtual void notify(const Notification& notification) = 0;
    virtual ~IObserver() = default;
};

#endif
