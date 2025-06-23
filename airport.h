#ifndef AIRPORT_H
#define AIRPORT_H

#include <QString>

class Airport
{
private:
    QString iataCode;
    QString name;
    QString city;
    double latitude = 0.0;
    double longitude = 0.0;

public:
    Airport() = default;
    Airport(const QString &iataCode,
            const QString &name,
            const QString &city,
            double latitude = 0.0,
            double longitude = 0.0);

    QString getIataCode() const;
    QString getName() const;
    QString getCity() const;
    double getLatitude() const;
    double getLongitude() const;
};

#endif // AIRPORT_H
