#include "trainticket.h"

TrainTicket::TrainTicket(QString id,
                         double price,
                         QDate fromDate,
                         QDate toDate,
                         const QString &fromStation,
                         const QString &toStation,
                         const QString &departureTime,
                         const QString &arrivalTime,
                         const QString &bookingClass,
                         const QVector<QString> &stops)
    : Booking(id, price, fromDate, toDate)
    , fromStation(fromStation)
    , toStation(toStation)
    , departureTime(departureTime)
    , arrivalTime(arrivalTime)
    , bookingClass(bookingClass)
    , stops(stops)
{}

QString TrainTicket::getFromStation() const
{
    return fromStation;
}
QString TrainTicket::getToStation() const
{
    return toStation;
}
QString TrainTicket::getDepartureTime() const
{
    return departureTime;
}
QString TrainTicket::getArrivalTime() const
{
    return arrivalTime;
}
QString TrainTicket::getBookingClass() const
{
    return bookingClass;
}
QVector<QString> TrainTicket::getStops() const
{
    return stops;
}

QString TrainTicket::showDetails() const
{
    QString details = "Zugbuchung von " + fromStation + " nach " + toStation + " am "
                      + fromDate.toString("dd.MM.yyyy") + ", Abfahrt: " + departureTime
                      + ", Ankunft: " + arrivalTime + ", Tarif: " + bookingClass
                      + ". Preis: " + QString::number(price, 'f', 2) + " Euro.";

    if (!stops.isEmpty()) {
        details += " Zwischenhalte: ";
        for (const QString &stop : stops) {
            details += stop + ", ";
        }
        details.chop(2); // letztes Komma entfernen
    }

    return details;
}
