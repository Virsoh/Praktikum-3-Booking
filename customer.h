#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "travel.h"
#include <string>
#include <vector>
class Customer
{
private:
    QString id;
    QString lastName;
    QString firstName;
    std::vector<Travel *> travelList;

public:
    Customer(const QString &id, const QString &firstName, const QString &lastName);
    void addTravel(Travel *Travel);
    QString getId() const;
    bool containsTravel(const Travel *travel) const;
    QString getFirstName() const;
    QString getLastName() const;
    const std::vector<Travel *> &getTravelList() const;
};

#endif // CUSTOMER_H
