#ifndef TRAVELAGENCY_H
#define TRAVELAGENCY_H

#include <QString>
#include <QMap>
#include <memory>
#include <vector>

#include "booking.h"
#include "customer.h"
#include "travel.h"
#include "airport.h"

class TravelAgency
{
private:
    std::vector<std::shared_ptr<Booking>> bookings;
    QVector<std::shared_ptr<Travel>> allTravels;
    QVector<std::shared_ptr<Customer>> allCustomers;
    QMap<QString, std::shared_ptr<Airport>> airports;

public:
    TravelAgency() = default;
    ~TravelAgency();

    void readFile(const std::string &filename);
    void writeFile(const std::string &filename) const;
    void reset();
    void editBooking(const QString &id);

    std::shared_ptr<Booking> findBookingById(const QString &id) const;
    std::shared_ptr<Customer> findCustomerById(const QString &id) const;
    std::shared_ptr<Travel> findTravelById(const QString &id) const;

    void loadAirports(const QString &filename);
    const QMap<QString, std::shared_ptr<Airport>> &getAirports() const { return airports; }
    const std::vector<std::shared_ptr<Booking>> &getBookings() const;
    QVector<std::shared_ptr<Travel>> getAllTravels() const { return allTravels; }
    QVector<std::shared_ptr<Customer>> getAllCustomers() const { return allCustomers; }
};

#endif // TRAVELAGENCY_H
