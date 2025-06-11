#include <QApplication>
#include "travelagency.h"
#include "travelagencyui.h"

// Einstiegspunkt, startet die GUI
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    TravelAgency agency;
    TravelAgencyUI ui(&agency);
    ui.show();

    return app.exec();
}
