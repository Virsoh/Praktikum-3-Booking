#include "customer.h"

Customer::Customer(const QString &id, const QString &firstName, const QString &lastName)
    : id(id)
    , firstName(firstName)
    , lastName(lastName)
{}

void Customer::addTravel(Travel *Travel)
{
    travelList.push_back(Travel);
}
QString Customer::getId() const
{
    return id;
}
bool Customer::containsTravel(const Travel *travel) const
{
    return std::find(travelList.begin(), travelList.end(), travel) != travelList.end();
}

QString Customer::getFirstName() const
{
    return firstName;
}

QString Customer::getLastName() const
{
    return lastName;
}
const std::vector<Travel *> &Customer::getTravelList() const
{
    return travelList;
}
