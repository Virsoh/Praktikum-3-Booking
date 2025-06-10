#include "travel.h"

Travel::Travel(const QString &id)
    : id(id)
{}
void Travel::addBooking(Booking *Booking)
{
    travelBookings.push_back(Booking);
}
QString Travel::getId() const
{
    return id;
}
bool Travel::containsBooking(const Booking *booking) const
{
    return std::find(travelBookings.begin(), travelBookings.end(), booking) != travelBookings.end();
}
const std::vector<Booking *> &Travel::getTravelBookings() const
{
    return travelBookings;
}
