#ifndef TRAVELAGENCYUI_H
#define TRAVELAGENCYUI_H

#include <QAbstractButton>
#include <QAction>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFileDialog>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QToolBar>
#include <QVBoxLayout>
#include <memory>

#include "customer.h"
#include "travel.h"
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

signals:
    void bookingsChanged();

private slots:
    void on_actionDateiOeffnenClicked();
    void on_actionEintragssucheClicked();
    void on_actionSpeichernTriggered();
    void onCustomerTableDoubleClicked(QTableWidgetItem *item);
    void onTravelTableDoubleClicked(QTableWidgetItem *item);
    void onBookingsChanged();
};

#endif // TRAVELAGENCYUI_H
