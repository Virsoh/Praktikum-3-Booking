#include "travel.h"

// Konstruktor einer Reise
Travel::Travel(const QString &id)
    : id(id)
{}
// Fügt eine Buchung hinzu
void Travel::addBooking(Booking *Booking)
{
    travelBookings.push_back(Booking);
}
// Reise-ID liefern
QString Travel::getId() const
{
    return id;
}
// Prüft ob Buchung drin ist
bool Travel::containsBooking(const Booking *booking) const
{
    return std::find(travelBookings.begin(), travelBookings.end(), booking) != travelBookings.end();
}
// Gibt alle Buchungen zurück
const std::vector<Booking *> &Travel::getTravelBookings() const
{
    return travelBookings;
}
