/****************************************************************************
** Meta object code from reading C++ file 'NegationComboBox.h'
**
** Created: Fri Apr 26 19:56:52 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../view/NegationComboBox.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NegationComboBox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_NegationComboBox[] = {

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
      30,   18,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_NegationComboBox[] = {
    "NegationComboBox\0\0optionValue\0"
    "checkForDisable(QString)\0"
};

const QMetaObject NegationComboBox::staticMetaObject = {
    { &QComboBox::staticMetaObject, qt_meta_stringdata_NegationComboBox,
      qt_meta_data_NegationComboBox, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NegationComboBox::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NegationComboBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NegationComboBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NegationComboBox))
        return static_cast<void*>(const_cast< NegationComboBox*>(this));
    return QComboBox::qt_metacast(_clname);
}

int NegationComboBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QComboBox::qt_metacall(_c, _id, _a);
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