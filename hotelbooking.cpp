#include "hotelbooking.h"

// Baut eine Hotelbuchung
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

// Name des Hotels
QString HotelBooking::getHotel() const
{
    return hotel;
}
// Ort der Unterkunft
QString HotelBooking::getTown() const
{
    return town;
}
// Zimmerkategorie holen
QString HotelBooking::getRoomType() const
{
    return roomType;
}

// Hotelname setzen
void HotelBooking::setHotel(const QString &h)
{
    hotel = h;
}

// Ort setzen
void HotelBooking::setTown(const QString &t)
{
    town = t;
}

// Zimmerkategorie setzen
void HotelBooking::setRoomType(const QString &rt)
{
    roomType = rt;
}

// Gibt einen Beschreibungstext zurueck
QString HotelBooking::showDetails() const
{
    return "Hotelreservierung im " + hotel + " in " + town + " vom "
           + fromDate.toString("dd.MM.yyyy") + " bis zum " + toDate.toString("dd.MM.yyyy")
           + ". Preis: " + QString::number(price) + " Euro";
}
