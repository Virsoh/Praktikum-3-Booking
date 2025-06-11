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

public:
    HotelBooking(const QString &id,
                 double price,
                 const QDate &fromDate,
                 const QDate &toDate,
                 const QString &hotel,
                 const QString &town,
                 const QString &roomType);

    QString getHotel() const;
    QString getTown() const;
    QString getRoomType() const;
    void setHotel(const QString &h);
    void setTown(const QString &t);
    void setRoomType(const QString &rt);
    QString showDetails() const override;
};

#endif // HOTELBOOKING_H
