/********************************************************************************
** Form generated from reading UI file 'bookingdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOOKINGDIALOG_H
#define UI_BOOKINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>

QT_BEGIN_NAMESPACE

class Ui_BookingDetailDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEditId;
    QDateEdit *dateEditFrom;
    QListWidget *listWidgetDetails;
    QDateEdit *dateEditTo;
    QDoubleSpinBox *doubleSpinBoxPrice;
    QLineEdit *lineEditExtra1;
    QLineEdit *lineEditExtra2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;

    void setupUi(QDialog *BookingDetailDialog)
    {
        if (BookingDetailDialog->objectName().isEmpty())
            BookingDetailDialog->setObjectName("BookingDetailDialog");
        BookingDetailDialog->resize(524, 485);
        buttonBox = new QDialogButtonBox(BookingDetailDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(40, 430, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        lineEditId = new QLineEdit(BookingDetailDialog);
        lineEditId->setObjectName("lineEditId");
        lineEditId->setGeometry(QRect(170, 20, 251, 28));
        dateEditFrom = new QDateEdit(BookingDetailDialog);
        dateEditFrom->setObjectName("dateEditFrom");
        dateEditFrom->setGeometry(QRect(170, 70, 110, 29));
        listWidgetDetails = new QListWidget(BookingDetailDialog);
        listWidgetDetails->setObjectName("listWidgetDetails");
        listWidgetDetails->setGeometry(QRect(170, 220, 256, 192));
        dateEditTo = new QDateEdit(BookingDetailDialog);
        dateEditTo->setObjectName("dateEditTo");
        dateEditTo->setGeometry(QRect(170, 100, 110, 29));
        doubleSpinBoxPrice = new QDoubleSpinBox(BookingDetailDialog);
        doubleSpinBoxPrice->setObjectName("doubleSpinBoxPrice");
        doubleSpinBoxPrice->setGeometry(QRect(170, 130, 111, 31));
        doubleSpinBoxPrice->setMaximum(99999.990000000005239);
        lineEditExtra1 = new QLineEdit(BookingDetailDialog);
        lineEditExtra1->setObjectName("lineEditExtra1");
        lineEditExtra1->setGeometry(QRect(170, 180, 113, 28));
        lineEditExtra2 = new QLineEdit(BookingDetailDialog);
        lineEditExtra2->setObjectName("lineEditExtra2");
        lineEditExtra2->setGeometry(QRect(310, 180, 113, 28));
        label = new QLabel(BookingDetailDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(130, 20, 63, 20));
        label_2 = new QLabel(BookingDetailDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(120, 80, 63, 20));
        label_3 = new QLabel(BookingDetailDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(130, 110, 63, 20));
        label_4 = new QLabel(BookingDetailDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(120, 140, 63, 20));
        label_5 = new QLabel(BookingDetailDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(50, 180, 121, 20));
        label_6 = new QLabel(BookingDetailDialog);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(80, 220, 91, 20));

        retranslateUi(BookingDetailDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, BookingDetailDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, BookingDetailDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(BookingDetailDialog);
    } // setupUi

    void retranslateUi(QDialog *BookingDetailDialog)
    {
        BookingDetailDialog->setWindowTitle(QCoreApplication::translate("BookingDetailDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("BookingDetailDialog", "ID", nullptr));
        label_2->setText(QCoreApplication::translate("BookingDetailDialog", "From", nullptr));
        label_3->setText(QCoreApplication::translate("BookingDetailDialog", "To", nullptr));
        label_4->setText(QCoreApplication::translate("BookingDetailDialog", "Price", nullptr));
        label_5->setText(QCoreApplication::translate("BookingDetailDialog", "Start - Destination", nullptr));
        label_6->setText(QCoreApplication::translate("BookingDetailDialog", "Infos / Stops", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BookingDetailDialog: public Ui_BookingDetailDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOOKINGDIALOG_H
