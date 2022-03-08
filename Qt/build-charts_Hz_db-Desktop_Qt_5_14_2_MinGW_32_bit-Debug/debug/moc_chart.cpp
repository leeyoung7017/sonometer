/****************************************************************************
** Meta object code from reading C++ file 'chart.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../charts_Hz_db/chart.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chart.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_chart_t {
    QByteArrayData data[13];
    char stringdata0[229];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_chart_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_chart_t qt_meta_stringdata_chart = {
    {
QT_MOC_LITERAL(0, 0, 5), // "chart"
QT_MOC_LITERAL(1, 6, 15), // "on_save_clicked"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 16), // "on_clear_clicked"
QT_MOC_LITERAL(4, 40, 22), // "on_test_botton_clicked"
QT_MOC_LITERAL(5, 63, 25), // "on_data_test_save_clicked"
QT_MOC_LITERAL(6, 89, 24), // "on_search_Button_clicked"
QT_MOC_LITERAL(7, 114, 23), // "on_clear_botton_clicked"
QT_MOC_LITERAL(8, 138, 9), // "onTimeout"
QT_MOC_LITERAL(9, 148, 14), // "ClientReadData"
QT_MOC_LITERAL(10, 163, 18), // "on_check_triggered"
QT_MOC_LITERAL(11, 182, 22), // "on_call_botton_pressed"
QT_MOC_LITERAL(12, 205, 23) // "on_call_botton_released"

    },
    "chart\0on_save_clicked\0\0on_clear_clicked\0"
    "on_test_botton_clicked\0on_data_test_save_clicked\0"
    "on_search_Button_clicked\0"
    "on_clear_botton_clicked\0onTimeout\0"
    "ClientReadData\0on_check_triggered\0"
    "on_call_botton_pressed\0on_call_botton_released"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_chart[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x08 /* Private */,
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    0,   73,    2, 0x08 /* Private */,
       7,    0,   74,    2, 0x08 /* Private */,
       8,    0,   75,    2, 0x08 /* Private */,
       9,    0,   76,    2, 0x08 /* Private */,
      10,    0,   77,    2, 0x08 /* Private */,
      11,    0,   78,    2, 0x08 /* Private */,
      12,    0,   79,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void chart::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<chart *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_save_clicked(); break;
        case 1: _t->on_clear_clicked(); break;
        case 2: { int _r = _t->on_test_botton_clicked();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 3: _t->on_data_test_save_clicked(); break;
        case 4: _t->on_search_Button_clicked(); break;
        case 5: _t->on_clear_botton_clicked(); break;
        case 6: _t->onTimeout(); break;
        case 7: { int _r = _t->ClientReadData();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->on_check_triggered(); break;
        case 9: _t->on_call_botton_pressed(); break;
        case 10: _t->on_call_botton_released(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject chart::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_chart.data,
    qt_meta_data_chart,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *chart::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *chart::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_chart.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int chart::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
