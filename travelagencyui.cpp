#include "travelagencyui.h"
#include <QDebug>
#include <QFileDialog>
#include <QFormLayout>
#include <QInputDialog>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QIcon>
#include <QTableWidgetItem>
#include "bookingdialog.h"
#include "customer.h"
#include "flightbooking.h"
#include "hotelbooking.h"
#include "rentalcarreservation.h"
#include "trainticket.h"
#include "travel.h"
#include "ui_travelagencyui.h"

// Hauptfenster einrichten
TravelAgencyUI::TravelAgencyUI(TravelAgency *agency, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TravelAgencyUI)
    , agency(agency)
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

    try {
        agency->readFile(filename.toStdString());
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

    Customer *customer = agency->findCustomerById(customerId);
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

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout.addRow(&buttonBox);
    connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        idOut = input->text().trimmed();
        return !idOut.isEmpty();
    }
    return false;
}

// füllt die Tabelle mit den Reisen
void TravelAgencyUI::zeigeReisenDesKunden(Customer *kunde)
{
    ui->reiseTable->clear();
    ui->reiseTable->setRowCount(0);
    ui->reiseTable->setColumnCount(3);
    ui->reiseTable->setHorizontalHeaderLabels({"Reise-ID", "Beginn der Reise", "Ende der Reise"});

    for (Travel *travel : kunde->getTravelList()) {
        QDate start = QDate::fromString("99991231", "yyyyMMdd");
        QDate end = QDate::fromString("00010101", "yyyyMMdd");

        for (Booking *b : travel->getTravelBookings()) {
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
void TravelAgencyUI::zeigeBuchungenZurReise(Travel *reise)
{
    if (!reise || !ui->customerTable)
        return;

    currentTravel = reise;

    ui->customerTable->clear();
    ui->customerTable->setRowCount(0);
    ui->customerTable->setColumnCount(4);
    ui->customerTable->setHorizontalHeaderLabels({"Buchung", "Start", "Ende", "Preis"});

    const auto &buchungen = reise->getTravelBookings();
    for (Booking *b : buchungen) {
        int row = ui->customerTable->rowCount();
        ui->customerTable->insertRow(row);

        QIcon icon;
        if (dynamic_cast<FlightBooking *>(b))
            icon = QIcon(":/icons/icons/flug.png");
        else if (dynamic_cast<HotelBooking *>(b))
            icon = QIcon(":/icons/icons/hotel.png");
        else if (dynamic_cast<RentalCarReservation *>(b))
            icon = QIcon(":/icons/icons/auto.png");
        else if (dynamic_cast<TrainTicket *>(b))
            icon = QIcon(":/icons/icons/zug.png");

        else if (dynamic_cast<HotelBooking *>(b))
            icon = QIcon(":/icons/icons/hotel.png");
        else if (dynamic_cast<RentalCarReservation *>(b))
            icon = QIcon(":/icons/icons/auto.png");
        else if (dynamic_cast<TrainTicket *>(b))
            icon = QIcon(":/icons/icons/zug.png");
        else if (dynamic_cast<FlightBooking *>(b))
            icon = QIcon(":/icons/flug.png");
        else if (dynamic_cast<HotelBooking *>(b))
            icon = QIcon(":/icons/hotel.png");
        else if (dynamic_cast<RentalCarReservation *>(b))
            icon = QIcon(":/icons/auto.png");
        else if (dynamic_cast<TrainTicket *>(b))
            icon = QIcon(":/icons/zug.png");



        QTableWidgetItem *iconItem = new QTableWidgetItem;
        iconItem->setIcon(icon);
        iconItem->setData(Qt::UserRole, QVariant::fromValue(quintptr(b)));
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

    Booking *booking = reinterpret_cast<Booking *>(
        idItem->data(Qt::UserRole).value<quintptr>());
    if (!booking)
        return;

    BookingDetailDialog dlg(this);
    dlg.setBooking(booking);
    if (dlg.exec() == QDialog::Accepted) {
        unsavedChanges = true;
        ui->actionSpeichern->setEnabled(true);
        if (currentTravel)
            zeigeBuchungenZurReise(currentTravel);
    }
// Beim Klick auf eine Reise deren Buchungen laden


    dlg.exec();

}
void TravelAgencyUI::onTravelTableDoubleClicked(QTableWidgetItem *item)
{
    if (!item)
        return;
    int row = item->row();
    QString travelId = ui->reiseTable->item(row, 0)->text();


    Travel *travel = agency->findTravelById(travelId);
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
void TravelAgencyUI::showCustomerInfo(Customer *customer)
{
    if (!customer)
        return;
    ui->lineEditCustomerId->setText(customer->getId());
    ui->lineEditFirstName->setText(customer->getFirstName());
    ui->lineEditLastName->setText(customer->getLastName());
}

// zeigt Details einer Reise
void TravelAgencyUI::showTravelDetails(Travel *travel)
{
    if (!travel)
        return;
    BookingDetailDialog dlg(this);
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
