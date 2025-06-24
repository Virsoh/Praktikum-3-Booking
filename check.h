#ifndef CHECK_H
#define CHECK_H

#include <memory>
#include <QString>
class TravelAgency;

class Check
{
private:
    std::shared_ptr<TravelAgency> agency;
    mutable QString lastError;

public:
    explicit Check(std::shared_ptr<TravelAgency> agency);
    void performChecks() const;
    bool checkTravelsDisjunct() const;
    QString getLastError() const { return lastError; }
};

#endif // CHECK_H
