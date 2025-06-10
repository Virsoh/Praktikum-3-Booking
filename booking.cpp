#include "booking.h"

Booking::Booking(QString id, double price, QDate fromDate, QDate toDate)
    : id(id)
    , price(price)
    , fromDate(fromDate)
    , toDate(toDate)
{}

Booking::~Booking() {}

QString Booking::getId() const
{
    return id;
}

double Booking::getPrice() const {
    return price;
}

QDate Booking::getFromDate() const
{
    return fromDate;
}

QDate Booking::getToDate() const
{
    return toDate;
}
