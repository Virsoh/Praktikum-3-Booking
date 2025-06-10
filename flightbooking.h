#ifndef FLIGHTBOOKING_H
#define FLIGHTBOOKING_H
#include <QDate>
#include <QString>
#include "booking.h"

class FlightBooking : public Booking
{
private:
    QString fromDest;
    QString toDest;
    QString airline;
    QString bookingClass;

public:
    FlightBooking(QString id,
                  double price,
                  QDate fromDate,
                  QDate toDate,
                  QString fromDest,
                  QString toDest,
                  QString airline,
                  QString bookingClass);

    QString getFromDest() const;
    QString getToDest() const;
    QString getAirline() const;
    QString getBookingClass() const;
    QString showDetails() const override;
};

#endif // FLIGHTBOOKING_H
