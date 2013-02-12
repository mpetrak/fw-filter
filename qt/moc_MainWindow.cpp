/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created: Tue Feb 12 19:46:59 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../view/MainWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   12,   11,   11, 0x05,
      34,   12,   11,   11, 0x05,
      56,   50,   11,   11, 0x05,
      82,   50,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     104,   11,   11,   11, 0x08,
     131,   11,   11,   11, 0x08,
     161,   11,   11,   11, 0x08,
     189,   11,   11,   11, 0x08,
     216,   11,   11,   11, 0x08,
     247,   11,   11,   11, 0x08,
     272,   11,   11,   11, 0x08,
     300,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0position\0newRule(int)\0"
    "deleteRule(int)\0index\0selectedRule(QModelIndex)\0"
    "saveRule(QModelIndex)\0on_newRuleButton_clicked()\0"
    "on_deleteRuleButton_clicked()\0"
    "on_saveEditButton_clicked()\0"
    "on_actionClose_triggered()\0"
    "on_actionSave_rule_triggered()\0"
    "on_actionNew_triggered()\0"
    "on_actionDelete_triggered()\0"
    "on_actionApply_modifications_triggered()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: newRule((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: deleteRule((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: selectedRule((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 3: saveRule((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 4: on_newRuleButton_clicked(); break;
        case 5: on_deleteRuleButton_clicked(); break;
        case 6: on_saveEditButton_clicked(); break;
        case 7: on_actionClose_triggered(); break;
        case 8: on_actionSave_rule_triggered(); break;
        case 9: on_actionNew_triggered(); break;
        case 10: on_actionDelete_triggered(); break;
        case 11: on_actionApply_modifications_triggered(); break;
        default: ;
        }
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::newRule(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::deleteRule(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainWindow::selectedRule(QModelIndex _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MainWindow::saveRule(QModelIndex _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
