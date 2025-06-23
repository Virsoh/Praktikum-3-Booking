#ifndef TRAVELAGENCY_H
#define TRAVELAGENCY_H

#include <QString>
#include "booking.h"
#include "customer.h"
#include "travel.h"
#include "airport.h"
#include <QMap>
#include <memory>
#include <vector>

class TravelAgency
{
private:
    std::vector<Booking *> bookings;
    QVector<Travel *> allTravels;
    QVector<Customer *> allCustomers;
    QMap<QString, std::shared_ptr<Airport>> airports;

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
    Customer *findCustomerById(const QString &id) const;
    Travel *findTravelById(const QString &id) const;
    void loadAirports(const QString &filename);
    const QMap<QString, std::shared_ptr<Airport>> &getAirports() const { return airports; }
    const std::vector<Booking *> &getBookings() const;
    QVector<Travel *> getAllTravels() const { return allTravels; };
    QVector<Customer *> getAllCustomers() const { return allCustomers; };
};

#endif // TRAVELAGENCY_H
