#ifndef TRAVEL_H
#define TRAVEL_H
#include "booking.h"
#include <vector>
class Travel
{
private:
    QString id;
    long customerId;
    std::vector<Booking *> travelBookings;

public:
    Travel(const QString &id);
    void addBooking(Booking *Booking);
    QString getId() const;
    bool containsBooking(const Booking *booking) const;
    const std::vector<Booking *> &getTravelBookings() const;
};

#endif // TRAVEL_H
