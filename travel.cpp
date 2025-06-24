#include "travel.h"
#include <algorithm>

// Konstruktor einer Reise
Travel::Travel(const QString &id)
    : id(id)
{}
// Fügt eine Buchung hinzu
void Travel::addBooking(const std::shared_ptr<Booking> &booking)
{
    travelBookings.push_back(booking);
}
// Reise-ID liefern
QString Travel::getId() const
{
    return id;
}
// Prüft ob Buchung drin ist
bool Travel::containsBooking(const std::shared_ptr<Booking> &booking) const
{
    return std::find(travelBookings.begin(), travelBookings.end(), booking) != travelBookings.end();
}
// Gibt alle Buchungen zurück
const std::vector<std::shared_ptr<Booking>> &Travel::getTravelBookings() const
{
    return travelBookings;
}
