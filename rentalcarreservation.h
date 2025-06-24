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
    double pickupLatitude = 0.0;
    double pickupLongitude = 0.0;
    double returnLatitude = 0.0;
    double returnLongitude = 0.0;

public:
    RentalCarReservation(QString id,
                         double price,
                         QDate fromDate,
                         QDate toDate,
                         const QString &pickupLocation,
                         const QString &returnLocation,
                         const QString &company,
                         const QString &carType,
                         double pickupLatitude = 0.0,
                         double pickupLongitude = 0.0,
                         double returnLatitude = 0.0,
                         double returnLongitude = 0.0);

    QString getPickupLocation() const;
    QString getReturnLocation() const;
    QString getCompany() const;
    QString getCarType() const;
    double getPickupLatitude() const { return pickupLatitude; }
    double getPickupLongitude() const { return pickupLongitude; }
    double getReturnLatitude() const { return returnLatitude; }
    double getReturnLongitude() const { return returnLongitude; }
    void setPickupLocation(const QString &loc);
    void setReturnLocation(const QString &loc);
    void setCompany(const QString &c);
    void setCarType(const QString &t);
    QString showDetails() const override;
};

#endif // RENTALCARRESERVATION_H
