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

void Booking::setPrice(double p)
{
    price = p;
}

void Booking::setFromDate(const QDate &d)
{
    fromDate = d;
}

void Booking::setToDate(const QDate &d)
{
    toDate = d;
}
