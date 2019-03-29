/****************************************************************************
** Meta object code from reading C++ file 'mycustomplot.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mycustomplot.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mycustomplot.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyCustomPlot_t {
    QByteArrayData data[20];
    char stringdata0[268];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyCustomPlot_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyCustomPlot_t qt_meta_stringdata_MyCustomPlot = {
    {
QT_MOC_LITERAL(0, 0, 12), // "MyCustomPlot"
QT_MOC_LITERAL(1, 13, 8), // "resetCPs"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 4), // "rows"
QT_MOC_LITERAL(4, 28, 9), // "selecteCP"
QT_MOC_LITERAL(5, 38, 13), // "MyCustomPlot*"
QT_MOC_LITERAL(6, 52, 4), // "full"
QT_MOC_LITERAL(7, 57, 18), // "contextMenuRequest"
QT_MOC_LITERAL(8, 76, 3), // "pos"
QT_MOC_LITERAL(9, 80, 22), // "playVideoSlot_realTime"
QT_MOC_LITERAL(10, 103, 21), // "playVideoSlot_history"
QT_MOC_LITERAL(11, 125, 18), // "removeHistoryGraph"
QT_MOC_LITERAL(12, 144, 16), // "selectionChanged"
QT_MOC_LITERAL(13, 161, 12), // "generateTick"
QT_MOC_LITERAL(14, 174, 13), // "addDatePerSec"
QT_MOC_LITERAL(15, 188, 13), // "stopDrawGraph"
QT_MOC_LITERAL(16, 202, 14), // "pauseDrawGraph"
QT_MOC_LITERAL(17, 217, 17), // "realTimeVideoPlay"
QT_MOC_LITERAL(18, 235, 21), // "videoPlayWidgetClosed"
QT_MOC_LITERAL(19, 257, 10) // "VideoPlay*"

    },
    "MyCustomPlot\0resetCPs\0\0rows\0selecteCP\0"
    "MyCustomPlot*\0full\0contextMenuRequest\0"
    "pos\0playVideoSlot_realTime\0"
    "playVideoSlot_history\0removeHistoryGraph\0"
    "selectionChanged\0generateTick\0"
    "addDatePerSec\0stopDrawGraph\0pauseDrawGraph\0"
    "realTimeVideoPlay\0videoPlayWidgetClosed\0"
    "VideoPlay*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyCustomPlot[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,
       4,    1,   87,    2, 0x06 /* Public */,
       6,    1,   90,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   93,    2, 0x0a /* Public */,
       9,    0,   96,    2, 0x0a /* Public */,
      10,    0,   97,    2, 0x0a /* Public */,
      11,    0,   98,    2, 0x0a /* Public */,
      12,    0,   99,    2, 0x0a /* Public */,
      13,    0,  100,    2, 0x0a /* Public */,
      14,    0,  101,    2, 0x0a /* Public */,
      15,    0,  102,    2, 0x0a /* Public */,
      16,    0,  103,    2, 0x0a /* Public */,
      17,    0,  104,    2, 0x0a /* Public */,
      18,    1,  105,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 5,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QPoint,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 19,    2,

       0        // eod
};

void MyCustomPlot::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyCustomPlot *_t = static_cast<MyCustomPlot *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->resetCPs((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->selecteCP((*reinterpret_cast< MyCustomPlot*(*)>(_a[1]))); break;
        case 2: _t->full((*reinterpret_cast< MyCustomPlot*(*)>(_a[1]))); break;
        case 3: _t->contextMenuRequest((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 4: _t->playVideoSlot_realTime(); break;
        case 5: _t->playVideoSlot_history(); break;
        case 6: _t->removeHistoryGraph(); break;
        case 7: _t->selectionChanged(); break;
        case 8: _t->generateTick(); break;
        case 9: _t->addDatePerSec(); break;
        case 10: _t->stopDrawGraph(); break;
        case 11: _t->pauseDrawGraph(); break;
        case 12: _t->realTimeVideoPlay(); break;
        case 13: _t->videoPlayWidgetClosed((*reinterpret_cast< VideoPlay*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< MyCustomPlot* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< MyCustomPlot* >(); break;
            }
            break;
        case 13:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< VideoPlay* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MyCustomPlot::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyCustomPlot::resetCPs)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MyCustomPlot::*_t)(MyCustomPlot * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyCustomPlot::selecteCP)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MyCustomPlot::*_t)(MyCustomPlot * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyCustomPlot::full)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject MyCustomPlot::staticMetaObject = {
    { &QCustomPlot::staticMetaObject, qt_meta_stringdata_MyCustomPlot.data,
      qt_meta_data_MyCustomPlot,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MyCustomPlot::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyCustomPlot::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MyCustomPlot.stringdata0))
        return static_cast<void*>(const_cast< MyCustomPlot*>(this));
    return QCustomPlot::qt_metacast(_clname);
}

int MyCustomPlot::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCustomPlot::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void MyCustomPlot::resetCPs(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MyCustomPlot::selecteCP(MyCustomPlot * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MyCustomPlot::full(MyCustomPlot * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
