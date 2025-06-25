#ifndef TRAVELAGENCYUI_H
#define TRAVELAGENCYUI_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QString>
#include <memory>

#include "customer.h"
#include "travel.h"
#include "booking.h"
#include "travelagency.h"
#include "check.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class TravelAgencyUI;
}
QT_END_NAMESPACE

class TravelAgencyUI : public QMainWindow
{
    Q_OBJECT

public:
    TravelAgencyUI(std::shared_ptr<TravelAgency> agency,
                   std::shared_ptr<Check> checker,
                   QWidget *parent = nullptr);
    ~TravelAgencyUI();

    bool showCustomerIdDialog(QString &idOut);
    void zeigeReisenDesKunden(std::shared_ptr<Customer> kunde);
    void zeigeBuchungenZurReise(std::shared_ptr<Travel> reise);

private:
    Ui::TravelAgencyUI *ui;
    std::shared_ptr<TravelAgency> agency;
    std::shared_ptr<Check> checker;
    bool unsavedChanges = false;
    std::shared_ptr<Travel> currentTravel;

    void setupUI();
    void clearTables();
    void showCustomerInfo(std::shared_ptr<Customer> customer);
    void showTravelDetails(std::shared_ptr<Travel> travel);
    void updateMapForTravel(std::shared_ptr<Travel> travel);
    void updateMapForBooking(std::shared_ptr<Booking> booking);

signals:
    void bookingsChanged();

private slots:
    void on_actionDateiOeffnenClicked();
    void on_actionEintragssucheClicked();
    void on_actionSpeichernTriggered();
    void on_loadBookingsButton_clicked();
    void on_loadIataButton_clicked();
    void onCustomerTableDoubleClicked(QTableWidgetItem *item);
    void onTravelTableDoubleClicked(QTableWidgetItem *item);
    void onBookingsChanged();
};

#endif // TRAVELAGENCYUI_H
