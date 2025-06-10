/****************************************************************************
** Meta object code from reading C++ file 'travelagencyui.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../travelagencyui.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'travelagencyui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSTravelAgencyUIENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSTravelAgencyUIENDCLASS = QtMocHelpers::stringData(
    "TravelAgencyUI",
    "on_actionDateiOeffnenClicked",
    "",
    "on_actionEintragssucheClicked",
    "onCustomerTableDoubleClicked",
    "QTableWidgetItem*",
    "item",
    "onTravelTableDoubleClicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSTravelAgencyUIENDCLASS_t {
    uint offsetsAndSizes[16];
    char stringdata0[15];
    char stringdata1[29];
    char stringdata2[1];
    char stringdata3[30];
    char stringdata4[29];
    char stringdata5[18];
    char stringdata6[5];
    char stringdata7[27];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSTravelAgencyUIENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSTravelAgencyUIENDCLASS_t qt_meta_stringdata_CLASSTravelAgencyUIENDCLASS = {
    {
        QT_MOC_LITERAL(0, 14),  // "TravelAgencyUI"
        QT_MOC_LITERAL(15, 28),  // "on_actionDateiOeffnenClicked"
        QT_MOC_LITERAL(44, 0),  // ""
        QT_MOC_LITERAL(45, 29),  // "on_actionEintragssucheClicked"
        QT_MOC_LITERAL(75, 28),  // "onCustomerTableDoubleClicked"
        QT_MOC_LITERAL(104, 17),  // "QTableWidgetItem*"
        QT_MOC_LITERAL(122, 4),  // "item"
        QT_MOC_LITERAL(127, 26)   // "onTravelTableDoubleClicked"
    },
    "TravelAgencyUI",
    "on_actionDateiOeffnenClicked",
    "",
    "on_actionEintragssucheClicked",
    "onCustomerTableDoubleClicked",
    "QTableWidgetItem*",
    "item",
    "onTravelTableDoubleClicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSTravelAgencyUIENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   38,    2, 0x08,    1 /* Private */,
       3,    0,   39,    2, 0x08,    2 /* Private */,
       4,    1,   40,    2, 0x08,    3 /* Private */,
       7,    1,   43,    2, 0x08,    5 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 5,    6,

       0        // eod
};

Q_CONSTINIT const QMetaObject TravelAgencyUI::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSTravelAgencyUIENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSTravelAgencyUIENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSTravelAgencyUIENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<TravelAgencyUI, std::true_type>,
        // method 'on_actionDateiOeffnenClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionEintragssucheClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onCustomerTableDoubleClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QTableWidgetItem *, std::false_type>,
        // method 'onTravelTableDoubleClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QTableWidgetItem *, std::false_type>
    >,
    nullptr
} };

void TravelAgencyUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TravelAgencyUI *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_actionDateiOeffnenClicked(); break;
        case 1: _t->on_actionEintragssucheClicked(); break;
        case 2: _t->onCustomerTableDoubleClicked((*reinterpret_cast< std::add_pointer_t<QTableWidgetItem*>>(_a[1]))); break;
        case 3: _t->onTravelTableDoubleClicked((*reinterpret_cast< std::add_pointer_t<QTableWidgetItem*>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *TravelAgencyUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TravelAgencyUI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSTravelAgencyUIENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int TravelAgencyUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
