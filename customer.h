#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "travel.h"
#include <memory>
#include <string>
#include <vector>
class Customer
{
private:
    QString id;
    QString lastName;
    QString firstName;
    std::vector<std::shared_ptr<Travel>> travelList;

public:
    Customer(const QString &id, const QString &firstName, const QString &lastName);
    void addTravel(const std::shared_ptr<Travel> &travel);
    QString getId() const;
    bool containsTravel(const std::shared_ptr<Travel> &travel) const;
    QString getFirstName() const;
    QString getLastName() const;
    const std::vector<std::shared_ptr<Travel>> &getTravelList() const;
};

#endif // CUSTOMER_H
