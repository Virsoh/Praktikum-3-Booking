#ifndef TRAVEL_H
#define TRAVEL_H
#include "booking.h"
#include <vector>
#include <memory>
class Travel
{
private:
    QString id;
    long customerId;
    std::vector<std::shared_ptr<Booking>> travelBookings;

public:
    Travel(const QString &id);
    void addBooking(const std::shared_ptr<Booking> &booking);
    QString getId() const;
    bool containsBooking(const std::shared_ptr<Booking> &booking) const;
    const std::vector<std::shared_ptr<Booking>> &getTravelBookings() const;
};

#endif // TRAVEL_H
