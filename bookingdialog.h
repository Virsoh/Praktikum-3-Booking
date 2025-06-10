#ifndef BOOKINGDETAILDIALOG_H
#define BOOKINGDETAILDIALOG_H

#include <QDialog>
#include "booking.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class BookingDetailDialog;
}
QT_END_NAMESPACE

class BookingDetailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BookingDetailDialog(QWidget *parent = nullptr);
    ~BookingDetailDialog();

    void setBooking(Booking *booking);

private:
    Ui::BookingDetailDialog *ui;
};

#endif // BOOKINGDETAILDIALOG_H
