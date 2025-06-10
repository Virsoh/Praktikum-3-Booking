/********************************************************************************
** Form generated from reading UI file 'travelagencyui.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRAVELAGENCYUI_H
#define UI_TRAVELAGENCYUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TravelAgencyUI
{
public:
    QAction *actionDateiOeffnen;
    QAction *actionEintragssuche;
    QWidget *centralwidget;
    QTableWidget *customerTable;
    QTableWidget *reiseTable;
    QLineEdit *lineEditCustomerId;
    QLineEdit *lineEditFirstName;
    QLineEdit *lineEditLastName;
    QStatusBar *statusbar;
    QMenuBar *menuBar;
    QMenu *menuDatei;
    QMenu *menuEintragssuche;
    QToolBar *toolBar;

    void setupUi(QMainWindow *TravelAgencyUI)
    {
        if (TravelAgencyUI->objectName().isEmpty())
            TravelAgencyUI->setObjectName("TravelAgencyUI");
        TravelAgencyUI->resize(790, 600);
        actionDateiOeffnen = new QAction(TravelAgencyUI);
        actionDateiOeffnen->setObjectName("actionDateiOeffnen");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icons/open.png"), QSize(), QIcon::Selected, QIcon::Off);
        actionDateiOeffnen->setIcon(icon);
        actionEintragssuche = new QAction(TravelAgencyUI);
        actionEintragssuche->setObjectName("actionEintragssuche");
        QIcon icon1(QIcon::fromTheme(QString::fromUtf8("QIcon::ThemeIcon::SystemSearch")));
        actionEintragssuche->setIcon(icon1);
        actionEintragssuche->setMenuRole(QAction::NoRole);
        centralwidget = new QWidget(TravelAgencyUI);
        centralwidget->setObjectName("centralwidget");
        customerTable = new QTableWidget(centralwidget);
        customerTable->setObjectName("customerTable");
        customerTable->setGeometry(QRect(180, 50, 256, 192));
        reiseTable = new QTableWidget(centralwidget);
        reiseTable->setObjectName("reiseTable");
        reiseTable->setGeometry(QRect(170, 270, 256, 192));
        lineEditCustomerId = new QLineEdit(centralwidget);
        lineEditCustomerId->setObjectName("lineEditCustomerId");
        lineEditCustomerId->setGeometry(QRect(20, 20, 113, 28));
        lineEditFirstName = new QLineEdit(centralwidget);
        lineEditFirstName->setObjectName("lineEditFirstName");
        lineEditFirstName->setGeometry(QRect(150, 20, 113, 28));
        lineEditLastName = new QLineEdit(centralwidget);
        lineEditLastName->setObjectName("lineEditLastName");
        lineEditLastName->setGeometry(QRect(280, 20, 113, 28));
        TravelAgencyUI->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(TravelAgencyUI);
        statusbar->setObjectName("statusbar");
        TravelAgencyUI->setStatusBar(statusbar);
        menuBar = new QMenuBar(TravelAgencyUI);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 790, 25));
        menuDatei = new QMenu(menuBar);
        menuDatei->setObjectName("menuDatei");
        menuEintragssuche = new QMenu(menuBar);
        menuEintragssuche->setObjectName("menuEintragssuche");
        TravelAgencyUI->setMenuBar(menuBar);
        toolBar = new QToolBar(TravelAgencyUI);
        toolBar->setObjectName("toolBar");
        TravelAgencyUI->addToolBar(Qt::TopToolBarArea, toolBar);

        menuBar->addAction(menuDatei->menuAction());
        menuBar->addAction(menuEintragssuche->menuAction());
        menuDatei->addAction(actionDateiOeffnen);
        menuEintragssuche->addAction(actionEintragssuche);
        toolBar->addAction(actionDateiOeffnen);
        toolBar->addAction(actionEintragssuche);

        retranslateUi(TravelAgencyUI);

        QMetaObject::connectSlotsByName(TravelAgencyUI);
    } // setupUi

    void retranslateUi(QMainWindow *TravelAgencyUI)
    {
        TravelAgencyUI->setWindowTitle(QCoreApplication::translate("TravelAgencyUI", "TravelAgencyUI", nullptr));
        actionDateiOeffnen->setText(QCoreApplication::translate("TravelAgencyUI", "Datei \303\266ffnen", nullptr));
        actionEintragssuche->setText(QCoreApplication::translate("TravelAgencyUI", "Eintragssuche", nullptr));
        menuDatei->setTitle(QCoreApplication::translate("TravelAgencyUI", "Datei", nullptr));
        menuEintragssuche->setTitle(QCoreApplication::translate("TravelAgencyUI", "Eintragssuche", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("TravelAgencyUI", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TravelAgencyUI: public Ui_TravelAgencyUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRAVELAGENCYUI_H
