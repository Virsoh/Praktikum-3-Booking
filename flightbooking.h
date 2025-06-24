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
    double fromLatitude = 0.0;
    double fromLongitude = 0.0;
    double toLatitude = 0.0;
    double toLongitude = 0.0;

public:
    FlightBooking(QString id,
                  double price,
                  QDate fromDate,
                  QDate toDate,
                  QString fromDest,
                  QString toDest,
                  QString airline,
                  QString bookingClass,
                  double fromLatitude = 0.0,
                  double fromLongitude = 0.0,
                  double toLatitude = 0.0,
                  double toLongitude = 0.0);

    QString getFromDest() const;
    QString getToDest() const;
    QString getAirline() const;
    QString getBookingClass() const;
    double getFromLatitude() const { return fromLatitude; }
    double getFromLongitude() const { return fromLongitude; }
    double getToLatitude() const { return toLatitude; }
    double getToLongitude() const { return toLongitude; }
    void setFromDest(const QString &dest);
    void setToDest(const QString &dest);
    void setAirline(const QString &airline);
    void setBookingClass(const QString &cls);
    QString showDetails() const override;
};

#endif // FLIGHTBOOKING_H
