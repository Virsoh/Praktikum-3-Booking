#include "booking.h"


Booking::Booking(QString id, double price, QDate fromDate, QDate toDate)
    : id(id)
    , price(price)
    , fromDate(fromDate)
    , toDate(toDate)
{}


Booking::~Booking() {}

// ID zurückgeben
QString Booking::getId() const
{
    return id;
}

// Preis holen
double Booking::getPrice() const {
    return price;
}

// Startdatum holen
QDate Booking::getFromDate() const
{
    return fromDate;
}

// Enddatum holen
QDate Booking::getToDate() const
{
    return toDate;
}


// Preis setzen

void Booking::setPrice(double p)
{
    price = p;
}


// Startdatum setzen

void Booking::setFromDate(const QDate &d)
{
    fromDate = d;
}

// Enddatum setzen

void Booking::setToDate(const QDate &d)
{
    toDate = d;
}
