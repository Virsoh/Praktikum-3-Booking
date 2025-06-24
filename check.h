#ifndef CHECK_H
#define CHECK_H

#include <memory>
#include <QString>
class TravelAgency;

class Check
{
private:
    std::shared_ptr<TravelAgency> agency;

public:
    explicit Check(std::shared_ptr<TravelAgency> agency);
    bool checkTravelsDisjunct(QString &errorMsg) const;
    void performChecks() const;
};

#endif // CHECK_H
