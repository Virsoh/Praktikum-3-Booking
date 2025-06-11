#include "rentalcarreservation.h"

// Erstellt eine Mietwagenreservierung
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

// Ort der Abholung
QString RentalCarReservation::getPickupLocation() const
{
    return pickupLocation;
}

// Ort der Rückgabe
QString RentalCarReservation::getReturnLocation() const
{
    return returnLocation;
}

// Vermieter auslesen
QString RentalCarReservation::getCompany() const
{
    return company;
}

// Fahrzeugklasse holen
QString RentalCarReservation::getCarType() const
{
    return carType;
}

// Abholort setzen
void RentalCarReservation::setPickupLocation(const QString &loc)
{
    pickupLocation = loc;
}

// Rückgabeort setzen
void RentalCarReservation::setReturnLocation(const QString &loc)
{
    returnLocation = loc;
}

// Vermieter setzen
void RentalCarReservation::setCompany(const QString &c)
{
    company = c;
}

// Fahrzeugklasse setzen
void RentalCarReservation::setCarType(const QString &t)
{
    carType = t;
}

// Kleinformatiger Beschreibungstext
QString RentalCarReservation::showDetails() const
{
    return "Mietwagenreservierung mit " + company + ". Abholung am "
           + fromDate.toString("dd.MM.yyyy") + " in " + pickupLocation + ", Rückgabe am "
           + toDate.toString("dd.MM.yyyy") + " in " + returnLocation
           + ". Preis: " + QString::number(price, 'f', 2) + " Euro";
}
