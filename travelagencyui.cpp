#include "travelagencyui.h"
#include <QFileDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QIcon>
#include <QTableWidgetItem>
#include "bookingdialog.h"
#include "customer.h"
#include "flightbooking.h"
#include "hotelbooking.h"
#include "rentalcarreservation.h"
#include "trainticket.h"
#include "travel.h"
#include "check.h"
#include "ui_travelagencyui.h"
#include <memory>
#include <QDesktopServices>
#include <QUrl>
#include <QCoreApplication>
#include "json.hpp"

// Hauptfenster einrichten
TravelAgencyUI::TravelAgencyUI(std::shared_ptr<TravelAgency> agency,
                               std::shared_ptr<Check> checker,
                               QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TravelAgencyUI)
    , agency(std::move(agency))
    , checker(std::move(checker))

{
    ui->setupUi(this);
    setupUI();

    connect(ui->actionDateiOeffnen,
            &QAction::triggered,
            this,
            &TravelAgencyUI::on_actionDateiOeffnenClicked);
    connect(ui->actionEintragssuche,
            &QAction::triggered,
            this,
            &TravelAgencyUI::on_actionEintragssucheClicked);

    connect(ui->actionSpeichern,
            &QAction::triggered,
            this,
            &TravelAgencyUI::on_actionSpeichernTriggered);

    ui->actionSpeichern->setEnabled(false);

    connect(ui->reiseTable,
            &QTableWidget::itemDoubleClicked,
            this,
            &TravelAgencyUI::onTravelTableDoubleClicked);

    connect(ui->customerTable,
            &QTableWidget::itemDoubleClicked,
            this,
            &TravelAgencyUI::onCustomerTableDoubleClicked);

    connect(this, &TravelAgencyUI::bookingsChanged, this, &TravelAgencyUI::onBookingsChanged);

    connect(ui->loadBookingsButton,
            &QPushButton::clicked,
            this,
            &TravelAgencyUI::on_loadBookingsButton_clicked);

    connect(ui->loadIataButton,
            &QPushButton::clicked,
            this,
            &TravelAgencyUI::on_loadIataButton_clicked);
}


TravelAgencyUI::~TravelAgencyUI()
{
    delete ui;
}

// JSON laden
void TravelAgencyUI::on_actionDateiOeffnenClicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Datei öffnen", "", "Alle Dateien (*.*)");
    if (filename.isEmpty())
        return;

    agency->reset();
    agency->loadAirports("data/iatacodes.json");

    try {
        agency->readFile(filename.toStdString());
        if (checker)
            checker->performChecks();
        QMessageBox::information(this,
                                 "Datei geladen",
                                 QString("%1 Buchungen, %2 Reisen, %3 Kunden eingelesen.")
                                     .arg(agency->getBookings().size())
                                     .arg(agency->getAllTravels().size())
                                     .arg(agency->getAllCustomers().size()));
        unsavedChanges = false;
        ui->actionSpeichern->setEnabled(false);
        currentTravel = nullptr;
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Fehler", QString::fromStdString(e.what()));
    }
}

// Kunden suchen und Reisen zeigen
void TravelAgencyUI::on_actionEintragssucheClicked()
{
    QString customerId;
    if (!showCustomerIdDialog(customerId))
        return;

    auto customer = agency->findCustomerById(customerId);
    if (!customer) {
        QMessageBox::warning(this, "Nicht gefunden", "Kein Kunde mit dieser ID gefunden.");
        return;
    }

    ui->lineEditCustomerId->setText(customer->getId());
    ui->lineEditFirstName->setText(customer->getFirstName());
    ui->lineEditLastName->setText(customer->getLastName());

    zeigeReisenDesKunden(customer);
}

// Dialogfeld für ID
bool TravelAgencyUI::showCustomerIdDialog(QString &idOut)
{
    QDialog dialog(this);
    dialog.setWindowTitle("Kund*innensuche");

    QFormLayout layout(&dialog);
    QLineEdit *input = new QLineEdit;
    layout.addRow("ID:", input);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout.addRow(buttonBox);
    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        idOut = input->text().trimmed();
        return !idOut.isEmpty();
    }
    return false;
}

// füllt die Tabelle mit den Reisen
void TravelAgencyUI::zeigeReisenDesKunden(std::shared_ptr<Customer> kunde)
{
    ui->reiseTable->clear();
    ui->reiseTable->setRowCount(0);
    ui->reiseTable->setColumnCount(3);
    ui->reiseTable->setHorizontalHeaderLabels({"Reise-ID", "Beginn der Reise", "Ende der Reise"});

    for (const auto &travel : kunde->getTravelList()) {
        QDate start = QDate::fromString("99991231", "yyyyMMdd");
        QDate end = QDate::fromString("00010101", "yyyyMMdd");

        for (const auto &b : travel->getTravelBookings()) {
            if (b->getFromDate() < start)
                start = b->getFromDate();
            if (b->getToDate() > end)
                end = b->getToDate();
        }

        int row = ui->reiseTable->rowCount();
        ui->reiseTable->insertRow(row);
        ui->reiseTable->setItem(row, 0, new QTableWidgetItem(travel->getId()));
        ui->reiseTable->setItem(row, 1, new QTableWidgetItem(start.toString("dddd, d. MMMM yyyy")));
        ui->reiseTable->setItem(row, 2, new QTableWidgetItem(end.toString("dddd, d. MMMM yyyy")));
    }

    ui->reiseTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}


// zeigt alle Buchungen einer Reise an
void TravelAgencyUI::zeigeBuchungenZurReise(std::shared_ptr<Travel> reise)
{
    if (!reise || !ui->customerTable)
        return;

    currentTravel = reise;

    ui->customerTable->clear();
    ui->customerTable->setRowCount(0);
    ui->customerTable->setColumnCount(4);
    ui->customerTable->setHorizontalHeaderLabels({"Buchung", "Start", "Ende", "Preis"});

    const auto &buchungen = reise->getTravelBookings();
    for (const auto &b : buchungen) {
        int row = ui->customerTable->rowCount();
        ui->customerTable->insertRow(row);

        QIcon icon;
        if (dynamic_cast<FlightBooking *>(b.get()))
            icon = QIcon(":/icons/icons/flug.png");
        else if (dynamic_cast<HotelBooking *>(b.get()))
            icon = QIcon(":/icons/icons/hotel.png");
        else if (dynamic_cast<RentalCarReservation *>(b.get()))
            icon = QIcon(":/icons/icons/auto.png");
        else if (dynamic_cast<TrainTicket *>(b.get()))
            icon = QIcon(":/icons/icons/zug.png");



        QTableWidgetItem *iconItem = new QTableWidgetItem;
        iconItem->setIcon(icon);
        iconItem->setData(Qt::UserRole, b->getId());
        ui->customerTable->setItem(row, 0, iconItem);
        ui->customerTable->setItem(
            row, 1, new QTableWidgetItem(b->getFromDate().toString("dd.MM.yyyy")));
        ui->customerTable->setItem(
            row, 2, new QTableWidgetItem(b->getToDate().toString("dd.MM.yyyy")));
        ui->customerTable->setItem(
            row,
            3,
            new QTableWidgetItem(QString::number(b->getPrice(), 'f', 2)));
    }

    ui->customerTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    updateMapForTravel(reise);
}

// Detaildialog für eine Buchung öffnen
void TravelAgencyUI::onCustomerTableDoubleClicked(QTableWidgetItem *item)
{
    if (!item)
        return;

    int row = item->row();
    QTableWidgetItem *idItem = ui->customerTable->item(row, 0);
    if (!idItem)
        return;

    QString bookingId = idItem->data(Qt::UserRole).toString();
    auto booking = agency->findBookingById(bookingId);
    if (!booking)
        return;

    showBookingMap(booking.get());

    BookingDetailDialog dlg(agency, this);
    dlg.setBooking(booking);
    if (dlg.exec() == QDialog::Accepted) {
        unsavedChanges = true;
        ui->actionSpeichern->setEnabled(true);
        if (currentTravel)
            zeigeBuchungenZurReise(currentTravel);
        emit bookingsChanged();
    }

}
void TravelAgencyUI::onTravelTableDoubleClicked(QTableWidgetItem *item)
{
    if (!item)
        return;
    int row = item->row();
    QString travelId = ui->reiseTable->item(row, 0)->text();


    auto travel = agency->findTravelById(travelId);
    if (!travel)
        return;


    zeigeBuchungenZurReise(travel);

}

// Grundeinstellungen für Tabellen
void TravelAgencyUI::setupUI()
{
    if (ui->customerTable)
        ui->customerTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    if (ui->reiseTable)
        ui->reiseTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

// Tabellen leeren
void TravelAgencyUI::clearTables()
{
    if (ui->customerTable)
        ui->customerTable->clearContents();
    if (ui->reiseTable)
        ui->reiseTable->clearContents();
}

// Kundendaten in die Felder schreiben
void TravelAgencyUI::showCustomerInfo(std::shared_ptr<Customer> customer)
{
    if (!customer)
        return;
    ui->lineEditCustomerId->setText(customer->getId());
    ui->lineEditFirstName->setText(customer->getFirstName());
    ui->lineEditLastName->setText(customer->getLastName());
}

// zeigt Details einer Reise
void TravelAgencyUI::showTravelDetails(std::shared_ptr<Travel> travel)
{
    if (!travel)
        return;
    BookingDetailDialog dlg(agency, this);
    if (!travel->getTravelBookings().empty())
        dlg.setBooking(travel->getTravelBookings().front());
    dlg.exec();
}

// Speichert alle Daten in eine Datei

void TravelAgencyUI::on_actionSpeichernTriggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Speichern", "", "JSON (*.json)");
    if (filename.isEmpty())
        return;
    try {
        agency->writeFile(filename.toStdString());
        unsavedChanges = false;
        ui->actionSpeichern->setEnabled(false);
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Fehler", QString::fromStdString(e.what()));
    }
}

void TravelAgencyUI::on_loadBookingsButton_clicked()
{
    QString filename
        = QFileDialog::getOpenFileName(this,
                                        tr("Buchungen laden"),
                                        QString(),
                                        tr("JSON (*.json);;Alle Dateien (*.*)"));
    if (filename.isEmpty())
        return;

    try {
        agency->readFile(filename.toStdString());
        if (checker)
            checker->performChecks();
        QMessageBox::information(this,
                                 tr("Buchungen geladen"),
                                 tr("Es wurden %1 Buchungen erfolgreich geladen.")
                                     .arg(agency->getBookings().size()));
        unsavedChanges = false;
        ui->actionSpeichern->setEnabled(false);
        emit bookingsChanged();
    } catch (const std::exception &e) {
        QMessageBox::critical(this, tr("Fehler"), QString::fromStdString(e.what()));
    }
}

void TravelAgencyUI::on_loadIataButton_clicked()
{
    QString filename
        = QFileDialog::getOpenFileName(this,
                                        tr("IATA-Codes laden"),
                                        QString(),
                                        tr("JSON (*.json);;Alle Dateien (*.*)"));
    if (filename.isEmpty())
        return;

    agency->loadAirports(filename);
}

void TravelAgencyUI::updateMapForTravel(std::shared_ptr<Travel> travel)
{
    if (!travel)
        return;

    using json = nlohmann::json;

    json featureCollection;
    featureCollection["type"] = "FeatureCollection";
    featureCollection["features"] = json::array();

    for (const auto &b : travel->getTravelBookings()) {
        if (auto *f = dynamic_cast<FlightBooking *>(b.get())) {
            if (f->getFromLatitude() || f->getFromLongitude() || f->getToLatitude()
                || f->getToLongitude()) {
                json feat;
                feat["type"] = "Feature";
                feat["geometry"] = {
                    {"type", "LineString"},
                    {"coordinates",
                     {{f->getFromLongitude(), f->getFromLatitude()},
                      {f->getToLongitude(), f->getToLatitude()}}}
                };
                feat["properties"] = { {"booking", "flight"} };
                featureCollection["features"].push_back(feat);
            }
        } else if (auto *h = dynamic_cast<HotelBooking *>(b.get())) {
            json feat;
            feat["type"] = "Feature";
            feat["geometry"]
                = { {"type", "Point"},
                    {"coordinates", {h->getLongitude(), h->getLatitude()}} };
            feat["properties"] = { {"booking", "hotel"} };
            featureCollection["features"].push_back(feat);
        } else if (auto *r = dynamic_cast<RentalCarReservation *>(b.get())) {
            json pick;
            pick["type"] = "Feature";
            pick["geometry"] = { {"type", "Point"},
                                 {"coordinates",
                                  {r->getPickupLongitude(), r->getPickupLatitude()}} };
            pick["properties"] = { {"booking", "rental"}, {"role", "pickup"} };
            featureCollection["features"].push_back(pick);
            json retF;
            retF["type"] = "Feature";
            retF["geometry"] = { {"type", "Point"},
                                  {"coordinates",
                                   {r->getReturnLongitude(), r->getReturnLatitude()}} };
            retF["properties"] = { {"booking", "rental"}, {"role", "return"} };
            featureCollection["features"].push_back(retF);
        } else if (auto *t = dynamic_cast<TrainTicket *>(b.get())) {
            json feat;
            feat["type"] = "Feature";
            feat["geometry"] = {
                {"type", "LineString"},
                {"coordinates",
                 {{t->getFromLongitude(), t->getFromLatitude()},
                  {t->getToLongitude(), t->getToLatitude()}}}
            };
            feat["properties"] = { {"booking", "train"} };
            featureCollection["features"].push_back(feat);
        }
    }

    QString geoJson = QString::fromStdString(featureCollection.dump());

    QUrl url = QUrl::fromLocalFile(QCoreApplication::applicationDirPath() +
                                   "/map.html");
    url.setQuery("data=" + QUrl::toPercentEncoding(geoJson));
    QDesktopServices::openUrl(url);


}

void TravelAgencyUI::updateMapForBooking(std::shared_ptr<Booking> booking)
{
    if (!booking)
        return;

    using json = nlohmann::json;
    json featureCollection;
    featureCollection["type"] = "FeatureCollection";
    featureCollection["features"] = json::array();

    if (auto *f = dynamic_cast<FlightBooking *>(booking.get())) {
        json feat;
        feat["type"] = "Feature";
        feat["geometry"] = {
            {"type", "LineString"},
            {"coordinates",
             {{f->getFromLongitude(), f->getFromLatitude()},
              {f->getToLongitude(), f->getToLatitude()}}}
        };
        featureCollection["features"].push_back(feat);
    } else if (auto *t = dynamic_cast<TrainTicket *>(booking.get())) {
        json feat;
        feat["type"] = "Feature";
        feat["geometry"] = {
            {"type", "LineString"},
            {"coordinates",
             {{t->getFromLongitude(), t->getFromLatitude()},
              {t->getToLongitude(), t->getToLatitude()}}}
        };
        featureCollection["features"].push_back(feat);
    } else if (auto *h = dynamic_cast<HotelBooking *>(booking.get())) {
        json feat;
        feat["type"] = "Feature";
        feat["geometry"] = { {"type", "Point"},
                             {"coordinates", {h->getLongitude(), h->getLatitude()}} };
        featureCollection["features"].push_back(feat);
    } else if (auto *r = dynamic_cast<RentalCarReservation *>(booking.get())) {
        json pick;
        pick["type"] = "Feature";
        pick["geometry"] = { {"type", "Point"},
                              {"coordinates",
                               {r->getPickupLongitude(), r->getPickupLatitude()}} };
        featureCollection["features"].push_back(pick);
        json retF;
        retF["type"] = "Feature";
        retF["geometry"] = { {"type", "Point"},
                              {"coordinates",
                               {r->getReturnLongitude(), r->getReturnLatitude()}} };
        featureCollection["features"].push_back(retF);
    }

    QString geoJson = QString::fromStdString(featureCollection.dump());

    QUrl url = QUrl::fromLocalFile(QCoreApplication::applicationDirPath() +
                                   "/map.html");
    url.setQuery("data=" + QUrl::toPercentEncoding(geoJson));
    QDesktopServices::openUrl(url);
}

void TravelAgencyUI::showBookingMap(const Booking *booking)
{
    if (!booking)
        return;

    using json = nlohmann::json;
    json featureCollection;
    featureCollection["type"] = "FeatureCollection";
    featureCollection["features"] = json::array();

    auto addLine = [&](double lon1, double lat1, double lon2, double lat2) {
        json feat;
        feat["type"] = "Feature";
        feat["geometry"] = { {"type", "LineString"},
                             {"coordinates", {{lon1, lat1}, {lon2, lat2}}} };
        featureCollection["features"].push_back(feat);
    };

    auto addPoint = [&](double lon, double lat) {
        json feat;
        feat["type"] = "Feature";
        feat["geometry"] = { {"type", "Point"}, {"coordinates", {lon, lat}} };
        featureCollection["features"].push_back(feat);
    };

    if (const FlightBooking *f = dynamic_cast<const FlightBooking *>(booking)) {
        addLine(f->getFromLongitude(), f->getFromLatitude(), f->getToLongitude(), f->getToLatitude());
    } else if (const TrainTicket *t = dynamic_cast<const TrainTicket *>(booking)) {
        addLine(t->getFromLongitude(), t->getFromLatitude(), t->getToLongitude(), t->getToLatitude());
    } else if (const RentalCarReservation *r = dynamic_cast<const RentalCarReservation *>(booking)) {
        addLine(r->getPickupLongitude(), r->getPickupLatitude(), r->getReturnLongitude(), r->getReturnLatitude());
    } else if (const HotelBooking *h = dynamic_cast<const HotelBooking *>(booking)) {
        addPoint(h->getLongitude(), h->getLatitude());
    } else {
        return;
    }

    QString geoJson = QString::fromStdString(featureCollection.dump());

    QUrl url = QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/map.html");
    url.setQuery(QStringLiteral("data=") + QUrl::toPercentEncoding(geoJson));
    QDesktopServices::openUrl(url);
}

void TravelAgencyUI::onBookingsChanged()
{
    if (checker)
        (*checker)();
}
