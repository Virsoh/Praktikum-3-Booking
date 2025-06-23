#include "flightbooking.h"

// Konstruktor für eine Flugbuchung
FlightBooking::FlightBooking(QString id,
                             double price,
                             QDate fromDate,
                             QDate toDate,
                             QString fromDest,
                             QString toDest,
                             QString airline,
                             QString bookingClass,
                             double fromLatitude,
                             double fromLongitude,
                             double toLatitude,
                             double toLongitude)
    : Booking(id, price, fromDate, toDate)
    , fromDest(fromDest)
    , toDest(toDest)
    , airline(airline)
    , bookingClass(bookingClass)
    , fromLatitude(fromLatitude)
    , fromLongitude(fromLongitude)
    , toLatitude(toLatitude)
    , toLongitude(toLongitude)
{}

// Startflughafen
QString FlightBooking::getFromDest() const
{
    return fromDest;
}
// Zielflughafen
QString FlightBooking::getToDest() const
{
    return toDest;
}
// Airline auslesen
QString FlightBooking::getAirline() const
{
    return airline;
}
// Buchungsklasse liefern
QString FlightBooking::getBookingClass() const
{
    return bookingClass;
}


// Startflughafen setzen

void FlightBooking::setFromDest(const QString &dest)
{
    fromDest = dest;
}

// Zielflughafen setzen

void FlightBooking::setToDest(const QString &dest)
{
    toDest = dest;
}

// Airline setzen

void FlightBooking::setAirline(const QString &a)
{
    airline = a;
}

// Buchungsklasse setzen

void FlightBooking::setBookingClass(const QString &cls)
{
    bookingClass = cls;
}

// Text für die UI basteln

QString FlightBooking::showDetails() const
{
    return "Flugbuchung von " + fromDest + " nach " + toDest + " mit " + airline + " am "
           + fromDate.toString("dd.MM.yyyy") + ". Preis: " + QString::number(price, 'f', 2)
           + " Euro";
}
