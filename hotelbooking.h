#ifndef HOTELBOOKING_H
#define HOTELBOOKING_H
#include <QDate>
#include <QString>
#include "booking.h"
class HotelBooking : public Booking
{
private:
    QString hotel;
    QString town;
    QString roomType;
    double latitude = 0.0;
    double longitude = 0.0;

public:
    HotelBooking(const QString &id,
                 double price,
                 const QDate &fromDate,
                 const QDate &toDate,
                 const QString &hotel,
                 const QString &town,
                 const QString &roomType,
                 double latitude = 0.0,
                 double longitude = 0.0);

    QString getHotel() const;
    QString getTown() const;
    QString getRoomType() const;
    double getLatitude() const { return latitude; }
    double getLongitude() const { return longitude; }
    void setHotel(const QString &h);
    void setTown(const QString &t);
    void setRoomType(const QString &rt);
    QString showDetails() const override;
};

#endif // HOTELBOOKING_H
