#include "rentalcarreservation.h"

RentalCarReservation::RentalCarReservation(QString id,
                                           double price,
                                           QDate fromDate,
                                           QDate toDate,
                                           const QString &pickupLocation,
                                           const QString &returnLocation,
                                           const QString &company,
                                           const QString &carType)
    : Booking(id, price, fromDate, toDate)
    , pickupLocation(pickupLocation)
    , returnLocation(returnLocation)
    , company(company)
    , carType(carType)
{}

QString RentalCarReservation::getPickupLocation() const
{
    return pickupLocation;
}

QString RentalCarReservation::getReturnLocation() const
{
    return returnLocation;
}

QString RentalCarReservation::getCompany() const
{
    return company;
}

QString RentalCarReservation::getCarType() const
{
    return carType;
}

void RentalCarReservation::setPickupLocation(const QString &loc)
{
    pickupLocation = loc;
}

void RentalCarReservation::setReturnLocation(const QString &loc)
{
    returnLocation = loc;
}

void RentalCarReservation::setCompany(const QString &c)
{
    company = c;
}

void RentalCarReservation::setCarType(const QString &t)
{
    carType = t;
}

QString RentalCarReservation::showDetails() const
{
    return "Mietwagenreservierung mit " + company + ". Abholung am "
           + fromDate.toString("dd.MM.yyyy") + " in " + pickupLocation + ", Rückgabe am "
           + toDate.toString("dd.MM.yyyy") + " in " + returnLocation
           + ". Preis: " + QString::number(price, 'f', 2) + " Euro";
}
