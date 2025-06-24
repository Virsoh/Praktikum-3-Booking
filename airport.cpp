#include "airport.h"

Airport::Airport(const QString &iataCode,
                 const QString &name,
                 const QString &city,
                 double latitude,
                 double longitude)
    : iataCode(iataCode)
    , name(name)
    , city(city)
    , latitude(latitude)
    , longitude(longitude)
{
}

QString Airport::getIataCode() const { return iataCode; }
QString Airport::getName() const { return name; }
QString Airport::getCity() const { return city; }
double Airport::getLatitude() const { return latitude; }
double Airport::getLongitude() const { return longitude; }
