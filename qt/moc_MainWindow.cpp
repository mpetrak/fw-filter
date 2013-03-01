/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created: Fri Mar 1 14:32:35 2013
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
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   12,   11,   11, 0x05,
      34,   12,   11,   11, 0x05,
      50,   12,   11,   11, 0x05,
      75,   69,   11,   11, 0x05,
     101,   69,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     123,   11,   11,   11, 0x08,
     150,   11,   11,   11, 0x08,
     180,   11,   11,   11, 0x08,
     213,   11,   11,   11, 0x08,
     241,   11,   11,   11, 0x08,
     268,   11,   11,   11, 0x08,
     299,   11,   11,   11, 0x08,
     324,   11,   11,   11, 0x08,
     352,   11,   11,   11, 0x08,
     383,   11,   11,   11, 0x08,
     424,   11,   11,   11, 0x08,
     451,   11,   11,   11, 0x08,
     481,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0position\0newRule(int)\0"
    "deleteRule(int)\0duplicateRule(int)\0"
    "index\0selectedRule(QModelIndex)\0"
    "saveRule(QModelIndex)\0on_newRuleButton_clicked()\0"
    "on_deleteRuleButton_clicked()\0"
    "on_duplicateRuleButton_clicked()\0"
    "on_saveEditButton_clicked()\0"
    "on_actionClose_triggered()\0"
    "on_actionSave_rule_triggered()\0"
    "on_actionNew_triggered()\0"
    "on_actionDelete_triggered()\0"
    "on_actionDuplicate_triggered()\0"
    "on_actionApply_modifications_triggered()\0"
    "on_actionReset_triggered()\0"
    "on_actionSettings_triggered()\0"
    "newSettings()\0"
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
        case 2: duplicateRule((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: selectedRule((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 4: saveRule((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 5: on_newRuleButton_clicked(); break;
        case 6: on_deleteRuleButton_clicked(); break;
        case 7: on_duplicateRuleButton_clicked(); break;
        case 8: on_saveEditButton_clicked(); break;
        case 9: on_actionClose_triggered(); break;
        case 10: on_actionSave_rule_triggered(); break;
        case 11: on_actionNew_triggered(); break;
        case 12: on_actionDelete_triggered(); break;
        case 13: on_actionDuplicate_triggered(); break;
        case 14: on_actionApply_modifications_triggered(); break;
        case 15: on_actionReset_triggered(); break;
        case 16: on_actionSettings_triggered(); break;
        case 17: newSettings(); break;
        default: ;
        }
        _id -= 18;
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
void MainWindow::duplicateRule(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MainWindow::selectedRule(QModelIndex _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MainWindow::saveRule(QModelIndex _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
