/****************************************************************************
** Meta object code from reading C++ file 'YJParallelCoordinates.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../YJParallelCoordinates.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'YJParallelCoordinates.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_YJParallelCoordinates_t {
    QByteArrayData data[10];
    char stringdata0[180];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_YJParallelCoordinates_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_YJParallelCoordinates_t qt_meta_stringdata_YJParallelCoordinates = {
    {
QT_MOC_LITERAL(0, 0, 21), // "YJParallelCoordinates"
QT_MOC_LITERAL(1, 22, 17), // "updateSmoothValue"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 5), // "value"
QT_MOC_LITERAL(4, 47, 22), // "updateCorrelationValue"
QT_MOC_LITERAL(5, 70, 16), // "loadDataFromFile"
QT_MOC_LITERAL(6, 87, 23), // "loadFeatureNameFromFile"
QT_MOC_LITERAL(7, 111, 32), // "loadkMeansClassificationFromFile"
QT_MOC_LITERAL(8, 144, 11), // "drawSliders"
QT_MOC_LITERAL(9, 156, 23) // "drawParallelCoordinates"

    },
    "YJParallelCoordinates\0updateSmoothValue\0"
    "\0value\0updateCorrelationValue\0"
    "loadDataFromFile\0loadFeatureNameFromFile\0"
    "loadkMeansClassificationFromFile\0"
    "drawSliders\0drawParallelCoordinates"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_YJParallelCoordinates[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x0a /* Public */,
       4,    1,   52,    2, 0x0a /* Public */,
       5,    0,   55,    2, 0x08 /* Private */,
       6,    0,   56,    2, 0x08 /* Private */,
       7,    0,   57,    2, 0x08 /* Private */,
       8,    0,   58,    2, 0x08 /* Private */,
       9,    0,   59,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void YJParallelCoordinates::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<YJParallelCoordinates *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateSmoothValue((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->updateCorrelationValue((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->loadDataFromFile(); break;
        case 3: _t->loadFeatureNameFromFile(); break;
        case 4: _t->loadkMeansClassificationFromFile(); break;
        case 5: _t->drawSliders(); break;
        case 6: _t->drawParallelCoordinates(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject YJParallelCoordinates::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_YJParallelCoordinates.data,
    qt_meta_data_YJParallelCoordinates,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *YJParallelCoordinates::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *YJParallelCoordinates::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_YJParallelCoordinates.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int YJParallelCoordinates::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
