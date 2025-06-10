#include "hotelbooking.h"

HotelBooking::HotelBooking(const QString &id,
                           double price,
                           const QDate &fromDate,
                           const QDate &toDate,
                           const QString &hotel,
                           const QString &town,
                           const QString &roomType)
    : Booking(id, price, fromDate, toDate)
    , hotel(hotel)
    , town(town)
    , roomType(roomType)
{}

QString HotelBooking::getHotel() const
{
    return hotel;
}
QString HotelBooking::getTown() const
{
    return town;
}
QString HotelBooking::getRoomType() const
{
    return roomType;
}

QString HotelBooking::showDetails() const
{
    return "Hotelreservierung im " + hotel + " in " + town + " vom "
           + fromDate.toString("dd.MM.yyyy") + " bis zum " + toDate.toString("dd.MM.yyyy")
           + ". Preis: " + QString::number(price) + " Euro";
}
