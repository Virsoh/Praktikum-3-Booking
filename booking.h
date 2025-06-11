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

    void setPrice(double p);
    void setFromDate(const QDate &d);
    void setToDate(const QDate &d);

    virtual QString showDetails() const = 0;

protected:
    QString id;
    double price;
    QDate fromDate;
    QDate toDate;
};

#endif // BOOKING_H
