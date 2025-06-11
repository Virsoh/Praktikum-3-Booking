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
#include "customer.h"
#include "travel.h"
#include "travelagency.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class TravelAgencyUI;
}
QT_END_NAMESPACE

class TravelAgencyUI : public QMainWindow
{
    Q_OBJECT

public:
    TravelAgencyUI(TravelAgency *agency, QWidget *parent = nullptr);
    ~TravelAgencyUI();
    bool showCustomerIdDialog(QString &idOut);
    void zeigeReisenDesKunden(Customer *kunde);
    void zeigeBuchungenZurReise(Travel *reise);

private:
    Ui::TravelAgencyUI *ui;
    TravelAgency *agency;

    // UI Components
    QTableWidget *customerTable;
    QTableWidget *travelTable;
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QLabel *customerInfoLabel;

    // Actions
    QAction *actionLoadData;
    QAction *actionSearchCustomer;
    QAction *actionSave;

    bool unsavedChanges = false;
    Travel *currentTravel = nullptr;

    // Helper methods
    void setupUI();
    void setupMenuAndToolbar();
    void clearTables();
    void showCustomerInfo(Customer *customer);
    void showTravelDetails(Travel *travel);

private slots:
    void on_actionDateiOeffnenClicked();
    void on_actionEintragssucheClicked();
    void on_actionSpeichernTriggered();
    void onCustomerTableDoubleClicked(QTableWidgetItem *item);
    void onTravelTableDoubleClicked(QTableWidgetItem *item);
};

#endif // TRAVELAGENCYUI_H
