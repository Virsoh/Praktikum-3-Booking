#include "check.h"
#include "travelagency.h"
#include <QDebug>
#include "customer.h"
#include "travel.h"

Check::Check(std::shared_ptr<TravelAgency> agency)
    : agency(std::move(agency))
{
}

bool Check::checkTravelsDisjunct(QString &errorMsg) const
{
    if (!agency)
        return true;

    for (const auto &customer : agency->getAllCustomers()) {
        const auto &travels = customer->getTravelList();
        for (int i = 0; i < travels.size(); ++i) {
            const auto &t1 = travels[i];

            QDate start1 = QDate(9999, 12, 31);
            QDate end1 = QDate(1, 1, 1);
            for (const auto &b : t1->getTravelBookings()) {
                if (b->getFromDate() < start1)
                    start1 = b->getFromDate();
                if (b->getToDate() > end1)
                    end1 = b->getToDate();
            }

            for (int j = i + 1; j < travels.size(); ++j) {
                const auto &t2 = travels[j];

                QDate start2 = QDate(9999, 12, 31);
                QDate end2 = QDate(1, 1, 1);
                for (const auto &b : t2->getTravelBookings()) {
                    if (b->getFromDate() < start2)
                        start2 = b->getFromDate();
                    if (b->getToDate() > end2)
                        end2 = b->getToDate();
                }

                if (start1 <= end2 && start2 <= end1) {
                    errorMsg = QString("Reisen %1 und %2 von %3 %4 ueberschneiden sich")
                                   .arg(t1->getId())
                                   .arg(t2->getId())
                                   .arg(customer->getFirstName())
                                   .arg(customer->getLastName());
                    return false;
                }
            }
        }
    }

    return true;
}

void Check::performChecks() const
{
    if (!agency)
        return;

    QString error;
    if (!checkTravelsDisjunct(error)) {
        qWarning() << error;
    }

    qDebug() << "Loaded bookings:" << agency->getBookings().size();
}

void Check::operator()() const
{
    performChecks();
}
