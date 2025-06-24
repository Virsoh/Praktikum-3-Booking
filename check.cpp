#include "check.h"
#include "travelagency.h"
#include <QDebug>
#include "customer.h"
#include "travel.h"
#include "booking.h"

Check::Check(std::shared_ptr<TravelAgency> agency)
    : agency(std::move(agency))
{
}

void Check::performChecks() const
{
    if (!agency)
        return;

    if (!checkTravelsDisjunct())
        qWarning() << lastError;
    else
        qDebug() << "Loaded bookings:" << agency->getBookings().size();
}

bool Check::checkTravelsDisjunct() const
{
    lastError.clear();
    if (!agency)
        return true;

    for (const auto &customer : agency->getAllCustomers()) {
        const auto &travels = customer->getTravelList();
        for (size_t i = 0; i < travels.size(); ++i) {
            QDate start1 = QDate::fromString("99991231", "yyyyMMdd");
            QDate end1 = QDate::fromString("00010101", "yyyyMMdd");
            for (const auto &b : travels[i]->getTravelBookings()) {
                if (b->getFromDate() < start1)
                    start1 = b->getFromDate();
                if (b->getToDate() > end1)
                    end1 = b->getToDate();
            }

            for (size_t j = i + 1; j < travels.size(); ++j) {
                QDate start2 = QDate::fromString("99991231", "yyyyMMdd");
                QDate end2 = QDate::fromString("00010101", "yyyyMMdd");
                for (const auto &b : travels[j]->getTravelBookings()) {
                    if (b->getFromDate() < start2)
                        start2 = b->getFromDate();
                    if (b->getToDate() > end2)
                        end2 = b->getToDate();
                }

                if (start1 <= end2 && start2 <= end1) {
                    lastError = QStringLiteral("Reiseueberschneidung bei %1 %2: %3 und %4")
                                    .arg(customer->getFirstName())
                                    .arg(customer->getLastName())
                                    .arg(travels[i]->getId())
                                    .arg(travels[j]->getId());
                    return false;
                }
            }
        }
    }

    return true;
}
