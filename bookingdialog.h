#ifndef BOOKINGDETAILDIALOG_H
#define BOOKINGDETAILDIALOG_H

#include <QDialog>
#include "booking.h"
#include "travelagency.h"
#include <memory>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui {
class BookingDetailDialog;
}
QT_END_NAMESPACE

class BookingDetailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BookingDetailDialog(std::shared_ptr<TravelAgency> agency, QWidget *parent = nullptr);
    explicit BookingDetailDialog(TravelAgency *agency, QWidget *parent = nullptr);

    ~BookingDetailDialog();

    void setBooking(std::shared_ptr<Booking> booking);
    bool isModified() const { return changed; }

protected:
    void accept() override;

private:
    Ui::BookingDetailDialog *ui;
    std::shared_ptr<TravelAgency> agency = nullptr;
    std::shared_ptr<Booking> currentBooking;
    TravelAgency *agency = nullptr;
    Booking *currentBooking = nullptr;

    bool changed = false;

private slots:
    void onFieldModified();
    void onIataCodeChanged(const QString &);
};

#endif // BOOKINGDETAILDIALOG_H
