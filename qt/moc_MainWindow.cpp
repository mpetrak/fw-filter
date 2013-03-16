/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created: Sat Mar 16 13:25:22 2013
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
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      39,   11,   11,   11, 0x08,
      69,   11,   11,   11, 0x08,
     102,   11,   11,   11, 0x08,
     131,   11,   11,   11, 0x08,
     163,   11,   11,   11, 0x08,
     195,   11,   11,   11, 0x08,
     222,   11,   11,   11, 0x08,
     253,   11,   11,   11, 0x08,
     289,   11,   11,   11, 0x08,
     314,   11,   11,   11, 0x08,
     342,   11,   11,   11, 0x08,
     373,   11,   11,   11, 0x08,
     414,   11,   11,   11, 0x08,
     441,   11,   11,   11, 0x08,
     471,   11,   11,   11, 0x08,
     503,   11,   11,   11, 0x08,
     541,   11,   11,   11, 0x08,
     555,   11,   11,   11, 0x08,
     575,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0on_newRuleButton_clicked()\0"
    "on_deleteRuleButton_clicked()\0"
    "on_duplicateRuleButton_clicked()\0"
    "on_saveApplyButton_clicked()\0"
    "on_ruleEditButtonBox_accepted()\0"
    "on_ruleEditButtonBox_rejected()\0"
    "on_actionClose_triggered()\0"
    "on_actionSave_rule_triggered()\0"
    "on_actionCancel_changes_triggered()\0"
    "on_actionNew_triggered()\0"
    "on_actionDelete_triggered()\0"
    "on_actionDuplicate_triggered()\0"
    "on_actionApply_modifications_triggered()\0"
    "on_actionReset_triggered()\0"
    "on_actionSettings_triggered()\0"
    "on_actionStatistics_triggered()\0"
    "on_actionNetfilter_output_triggered()\0"
    "newSettings()\0actualRuleChanged()\0"
    "clearRuleSelection()\0"
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
        case 0: on_newRuleButton_clicked(); break;
        case 1: on_deleteRuleButton_clicked(); break;
        case 2: on_duplicateRuleButton_clicked(); break;
        case 3: on_saveApplyButton_clicked(); break;
        case 4: on_ruleEditButtonBox_accepted(); break;
        case 5: on_ruleEditButtonBox_rejected(); break;
        case 6: on_actionClose_triggered(); break;
        case 7: on_actionSave_rule_triggered(); break;
        case 8: on_actionCancel_changes_triggered(); break;
        case 9: on_actionNew_triggered(); break;
        case 10: on_actionDelete_triggered(); break;
        case 11: on_actionDuplicate_triggered(); break;
        case 12: on_actionApply_modifications_triggered(); break;
        case 13: on_actionReset_triggered(); break;
        case 14: on_actionSettings_triggered(); break;
        case 15: on_actionStatistics_triggered(); break;
        case 16: on_actionNetfilter_output_triggered(); break;
        case 17: newSettings(); break;
        case 18: actualRuleChanged(); break;
        case 19: clearRuleSelection(); break;
        default: ;
        }
        _id -= 20;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
