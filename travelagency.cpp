#include "travelagency.h"
#include <QAbstractButton>
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QPushButton>
#include "flightbooking.h"
#include "hotelbooking.h"
#include "json.hpp"
#include "rentalcarreservation.h"
#include "trainticket.h"
#include "airport.h"
#include <memory>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>

using json = nlohmann::json;
using namespace std;

// gibt alle Buchungen frei
TravelAgency::~TravelAgency()
{
    bookings.clear();
    allTravels.clear();
    allCustomers.clear();
    airports.clear();
}

// leert die internen Listen
void TravelAgency::reset()
{
    bookings.clear();
    allTravels.clear();
    allCustomers.clear();
    airports.clear();
}

// liest die JSON-Datei ein
void TravelAgency::readFile(const std::string &filename)
{
    bookings.clear();
    allTravels.clear();
    allCustomers.clear();

    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Datei konnte nicht geöffnet werden: " + filename);
    }

    json j;
    file >> j;

    std::set<QString> seenBookingIds;

    for (const auto &entry : j) {
        try {
            if (!entry.contains("id") || !entry.contains("price") || !entry.contains("fromDate")
                || !entry.contains("toDate") || !entry.contains("type")
                || !entry.contains("customerId") || !entry.contains("travelId")) {
                throw std::runtime_error("Fehlende Pflichtfelder.");
            }

            // Namen können in den Dateien unterschiedlich bezeichnet sein
            if (!entry.contains("firstName") && !entry.contains("customerFirstname"))
                throw std::runtime_error("Fehlender Vorname.");
            if (!entry.contains("lastName") && !entry.contains("customerLastname"))
                throw std::runtime_error("Fehlender Nachname.");

            QString bookingId = QString::fromStdString(entry["id"]);
            if (seenBookingIds.find(bookingId) != seenBookingIds.end()) {
                throw std::runtime_error("Doppelte Buchungs-ID: " + bookingId.toStdString());
            }
            seenBookingIds.insert(bookingId);

            double price = entry["price"];
            QDate fromDate = QDate::fromString(QString::fromStdString(entry["fromDate"]),
                                               "yyyyMMdd");
            QDate toDate = QDate::fromString(QString::fromStdString(entry["toDate"]), "yyyyMMdd");
            QString type = QString::fromStdString(entry["type"]);

            QString travelId;
            if (entry["travelId"].is_string())
                travelId = QString::fromStdString(entry["travelId"]);
            else
                travelId = QString::number(entry["travelId"].get<int>());

            QString customerId;
            if (entry["customerId"].is_string())
                customerId = QString::fromStdString(entry["customerId"]);
            else
                customerId = QString::number(entry["customerId"].get<int>());

            QString firstName;
            if (entry.contains("firstName"))
                firstName = QString::fromStdString(entry["firstName"]);
            else
                firstName = QString::fromStdString(entry["customerFirstname"]);

            QString lastName;
            if (entry.contains("lastName"))
                lastName = QString::fromStdString(entry["lastName"]);
            else
                lastName = QString::fromStdString(entry["customerLastname"]);

            // Kunde suchen oder anlegen
            std::shared_ptr<Customer> customer;
            for (const auto &c : allCustomers) {
                if (c->getId() == customerId) {
                    customer = c;
                    break;
                }
            }
            if (!customer) {
                customer = std::make_shared<Customer>(customerId, firstName, lastName);
                allCustomers.append(customer);
            }

            // Reise suchen oder anlegen
            std::shared_ptr<Travel> travel;
            for (const auto &t : allTravels) {
                if (t->getId() == travelId) {
                    travel = t;
                    break;
                }
            }
            if (!travel) {
                travel = std::make_shared<Travel>(travelId);
                allTravels.append(travel);
                customer->addTravel(travel);
            }

            // Buchung erzeugen
            std::shared_ptr<Booking> booking;

            if (type == "Flight") {
                QString fromDest = QString::fromStdString(entry["fromDest"]);
                QString toDest = QString::fromStdString(entry["toDest"]);
                QString airline = QString::fromStdString(entry["airline"]);
                QString bookingClass = entry.contains("bookingClass")
                                           ? QString::fromStdString(entry["bookingClass"])
                                           : "Y";
                double fromLat = entry.contains("fromDestLatitude") ? entry["fromDestLatitude"].get<double>() : 0.0;
                double fromLon = entry.contains("fromDestLongitude") ? entry["fromDestLongitude"].get<double>() : 0.0;
                double toLat = entry.contains("toDestLatitude") ? entry["toDestLatitude"].get<double>() : 0.0;
                double toLon = entry.contains("toDestLongitude") ? entry["toDestLongitude"].get<double>() : 0.0;
                booking = std::make_shared<FlightBooking>(bookingId,
                                                        price,
                                                        fromDate,
                                                        toDate,
                                                        fromDest,
                                                        toDest,
                                                        airline,
                                                        bookingClass,
                                                        fromLat,
                                                        fromLon,
                                                        toLat,
                                                        toLon);

            } else if (type == "Hotel") {
                QString hotel = QString::fromStdString(entry["hotel"]);
                QString town = QString::fromStdString(entry["town"]);
                QString roomType = entry.contains("roomType")
                                       ? QString::fromStdString(entry["roomType"])
                                       : "Standard";
                double lat = entry.contains("latitude") ? entry["latitude"].get<double>() : 0.0;
                double lon = entry.contains("longitude") ? entry["longitude"].get<double>() : 0.0;
                booking = std::make_shared<HotelBooking>(bookingId,
                                                        price,
                                                        fromDate,
                                                        toDate,
                                                        hotel,
                                                        town,
                                                        roomType,
                                                        lat,
                                                        lon);

            } else if (type == "Rental" || type == "RentalCar") {
                QString pickup = QString::fromStdString(entry["pickupLocation"]);
                QString retLoc = QString::fromStdString(entry["returnLocation"]);
                QString company = QString::fromStdString(entry["company"]);
                QString carType;
                if (entry.contains("carType"))
                    carType = QString::fromStdString(entry["carType"]);
                else if (entry.contains("vehicleClass"))
                    carType = QString::fromStdString(entry["vehicleClass"]);
                else
                    carType = "Standard";
                double pickupLat = entry.contains("pickupLatitude") ? entry["pickupLatitude"].get<double>() : 0.0;
                double pickupLon = entry.contains("pickupLongitude") ? entry["pickupLongitude"].get<double>() : 0.0;
                double returnLat = entry.contains("returnLatitude") ? entry["returnLatitude"].get<double>() : 0.0;
                double returnLon = entry.contains("returnLongitude") ? entry["returnLongitude"].get<double>() : 0.0;
                booking = std::make_shared<RentalCarReservation>(bookingId,
                                                               price,
                                                               fromDate,
                                                               toDate,
                                                               pickup,
                                                               retLoc,
                                                               company,
                                                               carType,
                                                               pickupLat,
                                                               pickupLon,
                                                               returnLat,
                                                               returnLon);

            } else if (type == "Train") {
                QString fromStation = QString::fromStdString(entry["fromStation"]);
                QString toStation = QString::fromStdString(entry["toStation"]);
                QString depTime = QString::fromStdString(entry["departureTime"]);
                QString arrTime = QString::fromStdString(entry["arrivalTime"]);
                QString bookingClass;
                if (entry.contains("bookingClass"))
                    bookingClass = QString::fromStdString(entry["bookingClass"]);
                else if (entry.contains("ticketType"))
                    bookingClass = QString::fromStdString(entry["ticketType"]);
                else
                    bookingClass = "";

                QVector<QString> stops;
                if (entry.contains("stops")) {
                    for (const auto &s : entry["stops"]) {
                        stops.append(QString::fromStdString(s));
                    }
                } else if (entry.contains("connectingStations")) {
                    for (const auto &s : entry["connectingStations"]) {
                        stops.append(QString::fromStdString(s));
                    }
                }
                double fromLat = entry.contains("fromStationLatitude") ? entry["fromStationLatitude"].get<double>() : 0.0;
                double fromLon = entry.contains("fromStationLongitude") ? entry["fromStationLongitude"].get<double>() : 0.0;
                double toLat = entry.contains("toStationLatitude") ? entry["toStationLatitude"].get<double>() : 0.0;
                double toLon = entry.contains("toStationLongitude") ? entry["toStationLongitude"].get<double>() : 0.0;
                booking = std::make_shared<TrainTicket>(bookingId,
                                                      price,
                                                      fromDate,
                                                      toDate,
                                                      fromStation,
                                                      toStation,
                                                      depTime,
                                                      arrTime,
                                                      bookingClass,
                                                      stops,
                                                      fromLat,
                                                      fromLon,
                                                      toLat,
                                                      toLon);
            }

            if (booking) {
                bookings.push_back(booking);
                travel->addBooking(booking);
            }

        } catch (const std::exception &e) {
            qDebug() << "Fehler beim Einlesen:" << e.what();
        }
    }
}

// Liste aller Buchungen
const std::vector<std::shared_ptr<Booking>> &TravelAgency::getBookings() const
{
    return bookings;
}
// schreibt alle Daten wieder raus
void TravelAgency::writeFile(const std::string &filename) const
{
    json j;

    for (const auto &booking : bookings) {
        json entry;
        entry["id"] = booking->getId().toStdString();
        entry["price"] = booking->getPrice();
        entry["fromDate"] = booking->getFromDate().toString("yyyyMMdd").toStdString();
        entry["toDate"] = booking->getToDate().toString("yyyyMMdd").toStdString();

        // Buchungstyp-spezifisch ergänzen
        if (const FlightBooking *fb = dynamic_cast<const FlightBooking *>(booking)) {
            entry["type"] = "Flight";
            entry["fromDest"] = fb->getFromDest().toStdString();
            entry["toDest"] = fb->getToDest().toStdString();
            entry["airline"] = fb->getAirline().toStdString();
            entry["bookingClass"] = fb->getBookingClass().toStdString();
            entry["fromDestLatitude"] = fb->getFromLatitude();
            entry["fromDestLongitude"] = fb->getFromLongitude();
            entry["toDestLatitude"] = fb->getToLatitude();
            entry["toDestLongitude"] = fb->getToLongitude();

        } else if (const HotelBooking *hb = dynamic_cast<const HotelBooking *>(booking)) {
            entry["type"] = "Hotel";
            entry["hotel"] = hb->getHotel().toStdString();
            entry["town"] = hb->getTown().toStdString();
            entry["roomType"] = hb->getRoomType().toStdString();
            entry["latitude"] = hb->getLatitude();
            entry["longitude"] = hb->getLongitude();

        } else if (const RentalCarReservation *rc = dynamic_cast<const RentalCarReservation *>(
                       booking)) {
            entry["type"] = "Rental";
            entry["pickupLocation"] = rc->getPickupLocation().toStdString();
            entry["returnLocation"] = rc->getReturnLocation().toStdString();
            entry["company"] = rc->getCompany().toStdString();
            entry["carType"] = rc->getCarType().toStdString();
            entry["pickupLatitude"] = rc->getPickupLatitude();
            entry["pickupLongitude"] = rc->getPickupLongitude();
            entry["returnLatitude"] = rc->getReturnLatitude();
            entry["returnLongitude"] = rc->getReturnLongitude();

        } else if (const TrainTicket *tt = dynamic_cast<const TrainTicket *>(booking)) {
            entry["type"] = "Train";
            entry["fromStation"] = tt->getFromStation().toStdString();
            entry["toStation"] = tt->getToStation().toStdString();
            entry["departureTime"] = tt->getDepartureTime().toStdString();
            entry["arrivalTime"] = tt->getArrivalTime().toStdString();
            entry["bookingClass"] = tt->getBookingClass().toStdString();
            entry["fromStationLatitude"] = tt->getFromLatitude();
            entry["fromStationLongitude"] = tt->getFromLongitude();
            entry["toStationLatitude"] = tt->getToLatitude();
            entry["toStationLongitude"] = tt->getToLongitude();

            std::vector<std::string> stops;
            for (const QString &stop : tt->getStops()) {
                stops.push_back(stop.toStdString());
            }
            entry["stops"] = stops;
        }

        // Reise und Kunde suchen (für travelId + Kundendaten)
        for (const auto &travel : allTravels) {
            if (travel->containsBooking(booking)) {
                entry["travelId"] = travel->getId().toStdString();

                for (const auto &customer : allCustomers) {
                    if (customer->containsTravel(travel)) {
                        entry["customerId"] = customer->getId().toStdString();
                        entry["firstName"] = customer->getFirstName().toStdString();
                        entry["lastName"] = customer->getLastName().toStdString();
                        break;
                    }
                }
                break;
            }
        }

        j.push_back(entry);
    }

    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Datei konnte nicht geöffnet werden zum Schreiben: " + filename);
    }

    file << std::setw(4) << j << std::endl;

    int flightCount = 0;
    int hotelCount = 0;
    int rentalCount = 0;
    double totalValue = 0.0;

    for (const auto &b : bookings) {
        totalValue += b->getPrice();
        if (dynamic_cast<FlightBooking *>(b.get()))
            flightCount++;
        else if (dynamic_cast<HotelBooking *>(b.get()))
            hotelCount++;
        else if (dynamic_cast<RentalCarReservation *>(b.get()))
            rentalCount++;
    }

    // Reisen des Kunden mit ID 1
    int travelsOfCustomer1 = 0;
    for (const auto &c : allCustomers) {
        if (c->getId() == "1") {
            travelsOfCustomer1 = c->getTravelList().size();
            break;
        }
    }

    // Buchungen der Reise mit ID 17
    int bookingsOfTravel17 = 0;
    for (const auto &t : allTravels) {
        if (t->getId() == "17") {
            bookingsOfTravel17 = t->getTravelBookings().size();
            break;
        }
    }

    // Popup anzeigen
    QString message
        = QString(
              "Es wurden %1 Flugreservierungen, %2 Hotelbuchungen und %3 Mietwagenreservierungen "
              "im Gesamtwert von %4 Euro eingelesen.\n"
              "Es wurden %5 Reisen und %6 Kunden angelegt.\n"
              "Der Kunde mit der ID 1 hat %7 Reisen gebucht.\n"
              "Zur Reise mit der ID 17 gehören %8 Buchungen.")
              .arg(flightCount)
              .arg(hotelCount)
              .arg(rentalCount)
              .arg(QString::number(totalValue, 'f', 2))
              .arg(allTravels.size())
              .arg(allCustomers.size())
              .arg(travelsOfCustomer1)
              .arg(bookingsOfTravel17);

    QMessageBox::information(nullptr, "Statistik", message);
}

// Platzhalter zum Bearbeiten einer Buchung
void TravelAgency::editBooking(const QString &id)
{
    for (const auto &b : bookings) {
        if (b->getId() == id) {
            qDebug() << "Bearbeiten von Buchung mit ID:" << id;
            // Hier könnte später ein Dialog geöffnet werden
            return;
        }
    }

    qDebug() << "Keine Buchung mit ID" << id << "gefunden.";
}

std::shared_ptr<Booking> TravelAgency::findBookingById(const QString &id) const
{
    for (const auto &b : bookings) {
        if (b->getId() == id)
            return b;
    }
    return nullptr;
}

// sucht einen Kunden nach ID
std::shared_ptr<Customer> TravelAgency::findCustomerById(const QString &id) const
{
    for (const auto &c : allCustomers) {
        if (c->getId() == id)
            return c;
    }
    return nullptr;
}

// sucht eine Reise nach ID
std::shared_ptr<Travel> TravelAgency::findTravelById(const QString &id) const
{
    for (const auto &t : allTravels) {
        if (t->getId() == id)
            return t;
    }
    return nullptr;
}

void TravelAgency::loadAirports(const QString &filename)
{
    airports.clear();

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Konnte Flughafen-Datei nicht öffnen:" << filename;
        return;
    }

    QByteArray data = file.readAll();
    try {
        json j = json::parse(data.constData());
        for (const auto &entry : j) {
            QString code;
            if (entry.contains("iata"))
                code = QString::fromStdString(entry["iata"]);
            else if (entry.contains("code"))
                code = QString::fromStdString(entry["code"]);
            else if (entry.contains("iata_code"))
                code = QString::fromStdString(entry["iata_code"]);
            else
                continue;

            QString name = entry.contains("name")
                                ? QString::fromStdString(entry["name"])
                                : "";
            QString city = entry.contains("city")
                                ? QString::fromStdString(entry["city"])
                                : "";
            double lat = entry.contains("latitude")
                            ? entry["latitude"].get<double>()
                            : (entry.contains("lat") ? entry["lat"].get<double>() : 0.0);
            double lon = entry.contains("longitude")
                            ? entry["longitude"].get<double>()
                            : (entry.contains("lon") ? entry["lon"].get<double>() : 0.0);

            auto ap = std::make_shared<Airport>(code, name, city, lat, lon);
            airports.insert(code, ap);
        }
    } catch (const std::exception &e) {
        qWarning() << "Fehler beim Einlesen der Flughafen-Daten:" << e.what();
    }
}
