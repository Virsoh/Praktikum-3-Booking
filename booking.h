#ifndef BOOKING_H
#define BOOKING_H
#include <QDate>
#include <QString>

class Booking {
public:
    Booking(QString id, double price, QDate fromDate, QDate toDate);
    virtual ~Booking();

    QString getId() const;
    double getPrice() const;
    QDate getFromDate() const;
    QDate getToDate() const;

    virtual QString showDetails() const = 0;

protected:
    QString id;
    double price;
    QDate fromDate;
    QDate toDate;
};

#endif // BOOKING_H
