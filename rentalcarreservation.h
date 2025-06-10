#ifndef RENTALCARRESERVATION_H
#define RENTALCARRESERVATION_H

#include <QString>
#include "booking.h"

class RentalCarReservation : public Booking
{
private:
    QString pickupLocation;
    QString returnLocation;
    QString company;
    QString carType;

public:
    RentalCarReservation(QString id,
                         double price,
                         QDate fromDate,
                         QDate toDate,
                         const QString &pickupLocation,
                         const QString &returnLocation,
                         const QString &company,
                         const QString &carType);

    QString getPickupLocation() const;
    QString getReturnLocation() const;
    QString getCompany() const;
    QString getCarType() const;
    QString showDetails() const override;
};

#endif // RENTALCARRESERVATION_H
