/****************************************************************************
** Meta object code from reading C++ file 'MaskLineEdit.h'
**
** Created: Fri Apr 26 19:56:54 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../view/MaskLineEdit.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MaskLineEdit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MaskLineEdit[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   14,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MaskLineEdit[] = {
    "MaskLineEdit\0\0addrValue\0"
    "checkForDisable(QString)\0"
};

const QMetaObject MaskLineEdit::staticMetaObject = {
    { &QLineEdit::staticMetaObject, qt_meta_stringdata_MaskLineEdit,
      qt_meta_data_MaskLineEdit, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MaskLineEdit::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MaskLineEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MaskLineEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MaskLineEdit))
        return static_cast<void*>(const_cast< MaskLineEdit*>(this));
    return QLineEdit::qt_metacast(_clname);
}

int MaskLineEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLineEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: checkForDisable((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
