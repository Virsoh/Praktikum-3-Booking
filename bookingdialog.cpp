#include "bookingdialog.h"
#include "flightbooking.h"
#include "hotelbooking.h"
#include "rentalcarreservation.h"
#include "trainticket.h"
#include "ui_bookingdialog.h"

#include <QDate>

BookingDetailDialog::BookingDetailDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::BookingDetailDialog)
{
    ui->setupUi(this);
}

BookingDetailDialog::~BookingDetailDialog()
{
    delete ui;
}

void BookingDetailDialog::setBooking(Booking *booking)
{
    if (!booking)
        return;

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

    } else if (auto *hotel = dynamic_cast<HotelBooking *>(booking)) {
        ui->lineEditExtra1->setPlaceholderText("Hotel");
        ui->lineEditExtra1->setText(hotel->getHotel());
        ui->lineEditExtra2->setPlaceholderText("Ort");
        ui->lineEditExtra2->setText(hotel->getTown());

        ui->listWidgetDetails->clear();

    } else if (auto *car = dynamic_cast<RentalCarReservation *>(booking)) {
        ui->lineEditExtra1->setPlaceholderText("Abholung");
        ui->lineEditExtra1->setText(car->getPickupLocation());
        ui->lineEditExtra2->setPlaceholderText("Rückgabe");
        ui->lineEditExtra2->setText(car->getReturnLocation());

        ui->listWidgetDetails->clear();
        ui->listWidgetDetails->addItem("Firma: " + car->getCompany());
    }
}
