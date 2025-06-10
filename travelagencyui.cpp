#include "travelagencyui.h"
#include <QDebug>
#include <QFileDialog>
#include <QFormLayout>
#include <QInputDialog>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QTableWidgetItem>
#include "bookingdialog.h"
#include "customer.h"
#include "travel.h"
#include "ui_travelagencyui.h"

TravelAgencyUI::TravelAgencyUI(TravelAgency *agency, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TravelAgencyUI)
    , agency(agency)
{
    ui->setupUi(this);

    connect(ui->actionDateiOeffnen,
            &QAction::triggered,
            this,
            &TravelAgencyUI::on_actionDateiOeffnenClicked);
    connect(ui->actionEintragssuche,
            &QAction::triggered,
            this,
            &TravelAgencyUI::on_actionEintragssucheClicked);
}

TravelAgencyUI::~TravelAgencyUI()
{
    delete ui;
}

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
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Fehler", QString::fromStdString(e.what()));
    }
}

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
