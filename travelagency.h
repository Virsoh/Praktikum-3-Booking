#ifndef TRAVELAGENCY_H
#define TRAVELAGENCY_H

#include <QString>
#include "booking.h"
#include "customer.h"
#include "travel.h"
#include <vector>

class TravelAgency
{
private:
    std::vector<Booking *> bookings;
    QVector<Travel *> allTravels;
    QVector<Customer *> allCustomers;

public:
    TravelAgency() = default;
    ~TravelAgency();

    void printAllBookings() const;
    void readFile(const std::string &filename);
    void readBinaryFile();
    void writeFile(const std::string &filename) const;
    void printStatistics() const;
    void reset();
    void editBooking(const QString &id);
    const std::vector<Booking *> &getBookings() const;
    QVector<Travel *> getAllTravels() const { return allTravels; };
    QVector<Customer *> getAllCustomers() const { return allCustomers; };
};

#endif // TRAVELAGENCY_H
