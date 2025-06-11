#ifndef TRAINTICKET_H
#define TRAINTICKET_H

#include <QString>
#include <QVector>
#include "booking.h"

class TrainTicket : public Booking
{
private:
    QString fromStation;
    QString toStation;
    QString departureTime;
    QString arrivalTime;
    QString bookingClass;
    QVector<QString> stops;

public:
    TrainTicket(QString id,
                double price,
                QDate fromDate,
                QDate toDate,
                const QString &fromStation,
                const QString &toStation,
                const QString &departureTime,
                const QString &arrivalTime,
                const QString &bookingClass,
                const QVector<QString> &stops);

    QString getFromStation() const;
    QString getToStation() const;
    QString getDepartureTime() const;
    QString getArrivalTime() const;
    QString getBookingClass() const;
    QVector<QString> getStops() const;
    void setFromStation(const QString &from);
    void setToStation(const QString &to);
    void setDepartureTime(const QString &t);
    void setArrivalTime(const QString &t);
    void setBookingClass(const QString &cls);
    void setStops(const QVector<QString> &s);

    QString showDetails() const override;
};

#endif // TRAINTICKET_H
