#include "check.h"
#include "travelagency.h"
#include <QDebug>

Check::Check(std::shared_ptr<TravelAgency> agency)
    : agency(std::move(agency))
{
}

void Check::performChecks() const
{
    if (!agency)
        return;
    qDebug() << "Loaded bookings:" << agency->getBookings().size();
}
