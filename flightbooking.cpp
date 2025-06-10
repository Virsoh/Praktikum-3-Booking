#include "flightbooking.h"

FlightBooking::FlightBooking(QString id,
                             double price,
                             QDate fromDate,
                             QDate toDate,
                             QString fromDest,
                             QString toDest,
                             QString airline,
                             QString bookingClass)
    : Booking(id, price, fromDate, toDate)
    , fromDest(fromDest)
    , toDest(toDest)
    , airline(airline)
{}

QString FlightBooking::getFromDest() const
{
    return fromDest;
}
QString FlightBooking::getToDest() const
{
    return toDest;
}
QString FlightBooking::getAirline() const
{
    return airline;
}
QString FlightBooking::getBookingClass() const
{
    return bookingClass;
}

QString FlightBooking::showDetails() const
{
    return "Flugbuchung von " + fromDest + " nach " + toDest + " mit " + airline + " am "
           + fromDate.toString("dd.MM.yyyy") + ". Preis: " + QString::number(price, 'f', 2)
           + " Euro";
}
