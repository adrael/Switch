/****************************************************************************
** Meta object code from reading C++ file 'switch.hpp'
**
** Created: Sat 21. Apr 21:43:05 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../switch.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'switch.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Switch[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x08,
      30,    7,    7,    7, 0x08,
      52,    7,    7,    7, 0x08,
      69,    7,    7,    7, 0x08,
      89,    7,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Switch[] = {
    "Switch\0\0switchWindow(QString)\0"
    "switchButton(QString)\0switchState(int)\0"
    "switchPresence(int)\0getHash()\0"
};

void Switch::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Switch *_t = static_cast<Switch *>(_o);
        switch (_id) {
        case 0: _t->switchWindow((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->switchButton((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->switchState((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 3: _t->switchPresence((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 4: _t->getHash(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Switch::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Switch::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Switch,
      qt_meta_data_Switch, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Switch::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Switch::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Switch::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Switch))
        return static_cast<void*>(const_cast< Switch*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Switch::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
