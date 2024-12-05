/****************************************************************************
** Meta object code from reading C++ file 'Cronometre.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "Cronometre.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Cronometre.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Cronometre_t {
    QByteArrayData data[8];
    char stringdata0[84];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Cronometre_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Cronometre_t qt_meta_stringdata_Cronometre = {
    {
QT_MOC_LITERAL(0, 0, 10), // "Cronometre"
QT_MOC_LITERAL(1, 11, 9), // "emitStart"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 8), // "emitStop"
QT_MOC_LITERAL(4, 31, 11), // "emitRestart"
QT_MOC_LITERAL(5, 43, 8), // "emitQuit"
QT_MOC_LITERAL(6, 52, 18), // "changeRunningState"
QT_MOC_LITERAL(7, 71, 12) // "runningState"

    },
    "Cronometre\0emitStart\0\0emitStop\0"
    "emitRestart\0emitQuit\0changeRunningState\0"
    "runningState"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Cronometre[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    0,   40,    2, 0x06 /* Public */,
       4,    0,   41,    2, 0x06 /* Public */,
       5,    0,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    7,

       0        // eod
};

void Cronometre::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Cronometre *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->emitStart(); break;
        case 1: _t->emitStop(); break;
        case 2: _t->emitRestart(); break;
        case 3: _t->emitQuit(); break;
        case 4: _t->changeRunningState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Cronometre::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Cronometre::emitStart)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Cronometre::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Cronometre::emitStop)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Cronometre::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Cronometre::emitRestart)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Cronometre::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Cronometre::emitQuit)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Cronometre::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Cronometre.data,
    qt_meta_data_Cronometre,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Cronometre::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Cronometre::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Cronometre.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Cronometre::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void Cronometre::emitStart()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Cronometre::emitStop()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Cronometre::emitRestart()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Cronometre::emitQuit()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
