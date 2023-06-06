/****************************************************************************
** Meta object code from reading C++ file 'netting.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "E:/Desktop/cyx/qtpro/5.9_stage2(1)/new one/netting.h"
#include <QtNetwork/QSslPreSharedKeyAuthenticator>
#include <QtNetwork/QSslError>
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'netting.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_netting_t {
    uint offsetsAndSizes[34];
    char stringdata0[8];
    char stringdata1[13];
    char stringdata2[1];
    char stringdata3[12];
    char stringdata4[7];
    char stringdata5[12];
    char stringdata6[5];
    char stringdata7[23];
    char stringdata8[26];
    char stringdata9[26];
    char stringdata10[8];
    char stringdata11[10];
    char stringdata12[6];
    char stringdata13[15];
    char stringdata14[15];
    char stringdata15[12];
    char stringdata16[8];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_netting_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_netting_t qt_meta_stringdata_netting = {
    {
        QT_MOC_LITERAL(0, 7),  // "netting"
        QT_MOC_LITERAL(8, 12),  // "receieveData"
        QT_MOC_LITERAL(21, 0),  // ""
        QT_MOC_LITERAL(22, 11),  // "QTcpSocket*"
        QT_MOC_LITERAL(34, 6),  // "client"
        QT_MOC_LITERAL(41, 11),  // "NetworkData"
        QT_MOC_LITERAL(53, 4),  // "data"
        QT_MOC_LITERAL(58, 22),  // "receieveDataFromServer"
        QT_MOC_LITERAL(81, 25),  // "onClientSendButtonClicked"
        QT_MOC_LITERAL(107, 25),  // "onServerSendButtonClicked"
        QT_MOC_LITERAL(133, 7),  // "reStart"
        QT_MOC_LITERAL(141, 9),  // "reConnect"
        QT_MOC_LITERAL(151, 5),  // "reSet"
        QT_MOC_LITERAL(157, 14),  // "AsBlackClicked"
        QT_MOC_LITERAL(172, 14),  // "AsWhiteClicked"
        QT_MOC_LITERAL(187, 11),  // "namesetting"
        QT_MOC_LITERAL(199, 7)   // "send_OP"
    },
    "netting",
    "receieveData",
    "",
    "QTcpSocket*",
    "client",
    "NetworkData",
    "data",
    "receieveDataFromServer",
    "onClientSendButtonClicked",
    "onServerSendButtonClicked",
    "reStart",
    "reConnect",
    "reSet",
    "AsBlackClicked",
    "AsWhiteClicked",
    "namesetting",
    "send_OP"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_netting[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   80,    2, 0x08,    1 /* Private */,
       7,    1,   85,    2, 0x08,    4 /* Private */,
       8,    0,   88,    2, 0x08,    6 /* Private */,
       9,    0,   89,    2, 0x08,    7 /* Private */,
      10,    0,   90,    2, 0x08,    8 /* Private */,
      11,    0,   91,    2, 0x08,    9 /* Private */,
      12,    0,   92,    2, 0x08,   10 /* Private */,
      13,    0,   93,    2, 0x08,   11 /* Private */,
      14,    0,   94,    2, 0x08,   12 /* Private */,
      15,    0,   95,    2, 0x08,   13 /* Private */,
      16,    1,   96,    2, 0x08,   14 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

Q_CONSTINIT const QMetaObject netting::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_netting.offsetsAndSizes,
    qt_meta_data_netting,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_netting_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<netting, std::true_type>,
        // method 'receieveData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QTcpSocket *, std::false_type>,
        QtPrivate::TypeAndForceComplete<NetworkData, std::false_type>,
        // method 'receieveDataFromServer'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<NetworkData, std::false_type>,
        // method 'onClientSendButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onServerSendButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'reStart'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'reConnect'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'reSet'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'AsBlackClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'AsWhiteClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'namesetting'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'send_OP'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>
    >,
    nullptr
} };

void netting::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<netting *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->receieveData((*reinterpret_cast< std::add_pointer_t<QTcpSocket*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<NetworkData>>(_a[2]))); break;
        case 1: _t->receieveDataFromServer((*reinterpret_cast< std::add_pointer_t<NetworkData>>(_a[1]))); break;
        case 2: _t->onClientSendButtonClicked(); break;
        case 3: _t->onServerSendButtonClicked(); break;
        case 4: _t->reStart(); break;
        case 5: _t->reConnect(); break;
        case 6: _t->reSet(); break;
        case 7: _t->AsBlackClicked(); break;
        case 8: _t->AsWhiteClicked(); break;
        case 9: _t->namesetting(); break;
        case 10: _t->send_OP((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QTcpSocket* >(); break;
            }
            break;
        }
    }
}

const QMetaObject *netting::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *netting::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_netting.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int netting::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
