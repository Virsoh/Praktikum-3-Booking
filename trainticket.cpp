#include "trainticket.h"

// Konstruktor für Zugtickets
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

// Startbahnhof
QString TrainTicket::getFromStation() const
{
    return fromStation;
}
// Zielbahnhof
QString TrainTicket::getToStation() const
{
    return toStation;
}
// Abfahrtszeit holen
QString TrainTicket::getDepartureTime() const
{
    return departureTime;
}
// Ankunftszeit holen
QString TrainTicket::getArrivalTime() const
{
    return arrivalTime;
}
// Tarifcode liefern
QString TrainTicket::getBookingClass() const
{
    return bookingClass;
}
// Liste der Stops
QVector<QString> TrainTicket::getStops() const
{
    return stops;
}

// Startbahnhof setzen
void TrainTicket::setFromStation(const QString &from)
{
    fromStation = from;
}

// Zielbahnhof setzen
void TrainTicket::setToStation(const QString &to)
{
    toStation = to;
}

// Abfahrtszeit setzen
void TrainTicket::setDepartureTime(const QString &t)
{
    departureTime = t;
}

// Ankunftszeit setzen
void TrainTicket::setArrivalTime(const QString &t)
{
    arrivalTime = t;
}

// Tarifcode setzen
void TrainTicket::setBookingClass(const QString &cls)
{
    bookingClass = cls;
}

// Haltepunkte setzen
void TrainTicket::setStops(const QVector<QString> &s)
{
    stops = s;
}

// Schöner Text für die Anzeige
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
