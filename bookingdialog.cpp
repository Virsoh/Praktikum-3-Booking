#include "bookingdialog.h"
#include "flightbooking.h"
#include "hotelbooking.h"
#include "rentalcarreservation.h"
#include "trainticket.h"
#include "ui_bookingdialog.h"

#include <QDate>
#include <QDialogButtonBox>

BookingDetailDialog::BookingDetailDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::BookingDetailDialog)
{
    ui->setupUi(this);

    connect(ui->lineEditExtra1, &QLineEdit::textChanged, this, &BookingDetailDialog::onFieldModified);
    connect(ui->lineEditExtra2, &QLineEdit::textChanged, this, &BookingDetailDialog::onFieldModified);
    connect(ui->dateEditFrom, &QDateEdit::dateChanged, this, &BookingDetailDialog::onFieldModified);
    connect(ui->dateEditTo, &QDateEdit::dateChanged, this, &BookingDetailDialog::onFieldModified);
    connect(ui->doubleSpinBoxPrice, qOverload<double>(&QDoubleSpinBox::valueChanged), this, &BookingDetailDialog::onFieldModified);
}

BookingDetailDialog::~BookingDetailDialog()
{
    delete ui;
}

void BookingDetailDialog::setBooking(Booking *booking)
{
    if (!booking)
        return;

    currentBooking = booking;
    changed = false;
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    ui->lineEditId->setText(booking->getId());
    ui->dateEditFrom->setDate(booking->getFromDate());
    ui->dateEditTo->setDate(booking->getToDate());
    ui->doubleSpinBoxPrice->setValue(booking->getPrice());

    if (auto *train = dynamic_cast<TrainTicket *>(booking)) {
        ui->lineEditExtra1->setPlaceholderText("Abfahrt von");
        ui->lineEditExtra1->setText(train->getFromStation());
        ui->lineEditExtra2->setPlaceholderText("Ankunft in");
        ui->lineEditExtra2->setText(train->getToStation());

        ui->listWidgetDetails->clear();

        // translate booking class codes to human readable form
        const QString &classCode = train->getBookingClass();
        QString classDesc;
        if (classCode == "SSP1")
            classDesc = "Supersparpreis 1. Klasse";
        else if (classCode == "SSP2")
            classDesc = "Supersparpreis 2. Klasse";
        else if (classCode == "SP1")
            classDesc = "Sparpreis 1. Klasse";
        else if (classCode == "SP2")
            classDesc = "Sparpreis 2. Klasse";
        else if (classCode == "FP1")
            classDesc = "Flexpreis 1. Klasse";
        else if (classCode == "FP2")
            classDesc = "Flexpreis 2. Klasse";
        else
            classDesc = classCode;

        ui->listWidgetDetails->addItem("Buchungsklasse: " + classDesc);

        for (const auto &stop : train->getStops()) {
            ui->listWidgetDetails->addItem(stop);
        }

    } else if (auto *flight = dynamic_cast<FlightBooking *>(booking)) {
        ui->lineEditExtra1->setPlaceholderText("Von Flughafen");
        ui->lineEditExtra1->setText(flight->getFromDest());
        ui->lineEditExtra2->setPlaceholderText("Nach Flughafen");
        ui->lineEditExtra2->setText(flight->getToDest());

        ui->listWidgetDetails->clear();
        ui->listWidgetDetails->addItem("Airline: " + flight->getAirline());

        QString classDesc;
        const QString &classCode = flight->getBookingClass();
        if (classCode == "Y")
            classDesc = "Economy";
        else if (classCode == "W")
            classDesc = "Premium Economy";
        else if (classCode == "J")
            classDesc = "Business";
        else if (classCode == "F")
            classDesc = "First";
        else
            classDesc = classCode;

        ui->listWidgetDetails->addItem("Buchungsklasse: " + classDesc);

    } else if (auto *hotel = dynamic_cast<HotelBooking *>(booking)) {
        ui->lineEditExtra1->setPlaceholderText("Hotel");
        ui->lineEditExtra1->setText(hotel->getHotel());
        ui->lineEditExtra2->setPlaceholderText("Ort");
        ui->lineEditExtra2->setText(hotel->getTown());

        ui->listWidgetDetails->clear();

        QString roomDesc;
        const QString &roomType = hotel->getRoomType();
        if (roomType == "EZ")
            roomDesc = "Einzelzimmer";
        else if (roomType == "DZ")
            roomDesc = "Doppelzimmer";
        else if (roomType == "SU")
            roomDesc = "Suite";
        else if (roomType == "AP")
            roomDesc = "Appartment";
        else
            roomDesc = roomType;

        ui->listWidgetDetails->addItem("Zimmerkategorie: " + roomDesc);

    } else if (auto *car = dynamic_cast<RentalCarReservation *>(booking)) {
        ui->lineEditExtra1->setPlaceholderText("Abholung");
        ui->lineEditExtra1->setText(car->getPickupLocation());
        ui->lineEditExtra2->setPlaceholderText("Rückgabe");
        ui->lineEditExtra2->setText(car->getReturnLocation());

        ui->listWidgetDetails->clear();
        ui->listWidgetDetails->addItem("Firma: " + car->getCompany());
    }
}

void BookingDetailDialog::onFieldModified()
{
    changed = true;
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}

void BookingDetailDialog::accept()
{
    if (changed && currentBooking) {
        currentBooking->setPrice(ui->doubleSpinBoxPrice->value());
        currentBooking->setFromDate(ui->dateEditFrom->date());
        currentBooking->setToDate(ui->dateEditTo->date());

        if (auto *train = dynamic_cast<TrainTicket *>(currentBooking)) {
            train->setFromStation(ui->lineEditExtra1->text());
            train->setToStation(ui->lineEditExtra2->text());
        } else if (auto *flight = dynamic_cast<FlightBooking *>(currentBooking)) {
            flight->setFromDest(ui->lineEditExtra1->text());
            flight->setToDest(ui->lineEditExtra2->text());
        } else if (auto *hotel = dynamic_cast<HotelBooking *>(currentBooking)) {
            hotel->setHotel(ui->lineEditExtra1->text());
            hotel->setTown(ui->lineEditExtra2->text());
        } else if (auto *car = dynamic_cast<RentalCarReservation *>(currentBooking)) {
            car->setPickupLocation(ui->lineEditExtra1->text());
            car->setReturnLocation(ui->lineEditExtra2->text());
        }
    }
    QDialog::accept();
}
