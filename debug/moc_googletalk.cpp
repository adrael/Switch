/****************************************************************************
** Meta object code from reading C++ file 'googletalk.hpp'
**
** Created: Sat 21. Apr 21:43:08 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../googletalk.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'googletalk.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GoogleTalk[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      21,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GoogleTalk[] = {
    "GoogleTalk\0\0signIn()\0cancelSignIn()\0"
};

void GoogleTalk::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GoogleTalk *_t = static_cast<GoogleTalk *>(_o);
        switch (_id) {
        case 0: _t->signIn(); break;
        case 1: _t->cancelSignIn(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData GoogleTalk::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GoogleTalk::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_GoogleTalk,
      qt_meta_data_GoogleTalk, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GoogleTalk::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GoogleTalk::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GoogleTalk::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GoogleTalk))
        return static_cast<void*>(const_cast< GoogleTalk*>(this));
    return QWidget::qt_metacast(_clname);
}

int GoogleTalk::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
