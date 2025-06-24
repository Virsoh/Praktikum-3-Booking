#include "customer.h"
#include <algorithm>
#include <memory>

// Einfacher Konstruktor für Kund*innen
Customer::Customer(const QString &id, const QString &firstName, const QString &lastName)
    : id(id)
    , firstName(firstName)
    , lastName(lastName)
{}

// Reise zum Kunden hinzufügen
void Customer::addTravel(const std::shared_ptr<Travel> &travel)
{
    travelList.push_back(travel);
}
// Kundennummer holen
QString Customer::getId() const
{
    return id;
}
// Prüft ob Reise vorhanden ist
bool Customer::containsTravel(const std::shared_ptr<Travel> &travel) const
{
    return std::find(travelList.begin(), travelList.end(), travel) != travelList.end();
}

// Vorname holen
QString Customer::getFirstName() const
{
    return firstName;
}

// Nachname holen
QString Customer::getLastName() const
{
    return lastName;
}
// Alle Reisen liefern
const std::vector<std::shared_ptr<Travel>> &Customer::getTravelList() const
{
    return travelList;
}
