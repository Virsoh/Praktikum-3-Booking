#ifndef BOOKINGDETAILDIALOG_H
#define BOOKINGDETAILDIALOG_H

#include <QDialog>
#include <memory>

#include "booking.h"
#include "travelagency.h"

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
    ~BookingDetailDialog();

    void setBooking(std::shared_ptr<Booking> booking);
    bool isModified() const { return changed; }

protected:
    void accept() override;

private:
    Ui::BookingDetailDialog *ui;
    std::shared_ptr<TravelAgency> agency;
    std::shared_ptr<Booking> currentBooking;
    bool changed = false;

private slots:
    void onFieldModified();
    void onIataCodeChanged(const QString &);
};

#endif // BOOKINGDETAILDIALOG_H
