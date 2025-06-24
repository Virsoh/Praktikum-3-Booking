#include <QApplication>
#include "travelagency.h"
#include "travelagencyui.h"
#include <memory>

// Einstiegspunkt, startet die GUI
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    auto agency = std::make_shared<TravelAgency>();
    TravelAgencyUI ui(agency);
    ui.show();

    return app.exec();
}
