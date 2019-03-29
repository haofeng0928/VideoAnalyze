/****************************************************************************
** Meta object code from reading C++ file 'graphlistwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../graphlistwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'graphlistwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GraphListWidget_t {
    QByteArrayData data[12];
    char stringdata0[138];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GraphListWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GraphListWidget_t qt_meta_stringdata_GraphListWidget = {
    {
QT_MOC_LITERAL(0, 0, 15), // "GraphListWidget"
QT_MOC_LITERAL(1, 16, 8), // "resetCPs"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 8), // "selectCP"
QT_MOC_LITERAL(4, 35, 13), // "MyCustomPlot*"
QT_MOC_LITERAL(5, 49, 8), // "fullSlot"
QT_MOC_LITERAL(6, 58, 13), // "realTimeGraph"
QT_MOC_LITERAL(7, 72, 9), // "TreeData*"
QT_MOC_LITERAL(8, 82, 5), // "pNode"
QT_MOC_LITERAL(9, 88, 11), // "updateGraph"
QT_MOC_LITERAL(10, 100, 20), // "drawHistoryGraphSlot"
QT_MOC_LITERAL(11, 121, 16) // "QListWidgetItem*"

    },
    "GraphListWidget\0resetCPs\0\0selectCP\0"
    "MyCustomPlot*\0fullSlot\0realTimeGraph\0"
    "TreeData*\0pNode\0updateGraph\0"
    "drawHistoryGraphSlot\0QListWidgetItem*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GraphListWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x0a /* Public */,
       3,    1,   47,    2, 0x0a /* Public */,
       5,    1,   50,    2, 0x0a /* Public */,
       6,    1,   53,    2, 0x0a /* Public */,
       9,    0,   56,    2, 0x0a /* Public */,
      10,    1,   57,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,    2,

       0        // eod
};

void GraphListWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GraphListWidget *_t = static_cast<GraphListWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->resetCPs((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->selectCP((*reinterpret_cast< MyCustomPlot*(*)>(_a[1]))); break;
        case 2: _t->fullSlot((*reinterpret_cast< MyCustomPlot*(*)>(_a[1]))); break;
        case 3: _t->realTimeGraph((*reinterpret_cast< TreeData*(*)>(_a[1]))); break;
        case 4: _t->updateGraph(); break;
        case 5: _t->drawHistoryGraphSlot((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
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
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< TreeData* >(); break;
            }
            break;
        }
    }
}

const QMetaObject GraphListWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_GraphListWidget.data,
      qt_meta_data_GraphListWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GraphListWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GraphListWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GraphListWidget.stringdata0))
        return static_cast<void*>(const_cast< GraphListWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int GraphListWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
