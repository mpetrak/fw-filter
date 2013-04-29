/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created: Mon Apr 29 21:34:55 2013
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QListView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionClose;
    QAction *actionApply_modifications;
    QAction *actionReset;
    QAction *actionSettings;
    QAction *actionSave_rule;
    QAction *actionNew;
    QAction *actionDelete;
    QAction *actionDuplicate;
    QAction *actionNetfilter_output;
    QAction *actionCancel_changes;
    QAction *actionStatistics;
    QWidget *centralwidget;
    QListView *rulesView;
    QPushButton *newRuleButton;
    QPushButton *deleteRuleButton;
    QPushButton *saveApplyButton;
    QPushButton *duplicateRuleButton;
    QDialogButtonBox *ruleEditButtonBox;
    QMenuBar *menubar;
    QMenu *menuTools;
    QMenu *menuApplication;
    QMenu *menuRule;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(750, 712);
        MainWindow->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QString::fromUtf8("actionClose"));
        actionApply_modifications = new QAction(MainWindow);
        actionApply_modifications->setObjectName(QString::fromUtf8("actionApply_modifications"));
        actionReset = new QAction(MainWindow);
        actionReset->setObjectName(QString::fromUtf8("actionReset"));
        actionSettings = new QAction(MainWindow);
        actionSettings->setObjectName(QString::fromUtf8("actionSettings"));
        actionSave_rule = new QAction(MainWindow);
        actionSave_rule->setObjectName(QString::fromUtf8("actionSave_rule"));
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        actionDelete = new QAction(MainWindow);
        actionDelete->setObjectName(QString::fromUtf8("actionDelete"));
        actionDuplicate = new QAction(MainWindow);
        actionDuplicate->setObjectName(QString::fromUtf8("actionDuplicate"));
        actionNetfilter_output = new QAction(MainWindow);
        actionNetfilter_output->setObjectName(QString::fromUtf8("actionNetfilter_output"));
        actionCancel_changes = new QAction(MainWindow);
        actionCancel_changes->setObjectName(QString::fromUtf8("actionCancel_changes"));
        actionStatistics = new QAction(MainWindow);
        actionStatistics->setObjectName(QString::fromUtf8("actionStatistics"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        rulesView = new QListView(centralwidget);
        rulesView->setObjectName(QString::fromUtf8("rulesView"));
        rulesView->setGeometry(QRect(10, 10, 191, 531));
        rulesView->setAcceptDrops(true);
        rulesView->setDragEnabled(true);
        rulesView->setDragDropMode(QAbstractItemView::InternalMove);
        rulesView->setDefaultDropAction(Qt::MoveAction);
        rulesView->setMovement(QListView::Free);
        newRuleButton = new QPushButton(centralwidget);
        newRuleButton->setObjectName(QString::fromUtf8("newRuleButton"));
        newRuleButton->setGeometry(QRect(10, 550, 31, 27));
        newRuleButton->setFlat(false);
        deleteRuleButton = new QPushButton(centralwidget);
        deleteRuleButton->setObjectName(QString::fromUtf8("deleteRuleButton"));
        deleteRuleButton->setGeometry(QRect(50, 550, 31, 27));
        saveApplyButton = new QPushButton(centralwidget);
        saveApplyButton->setObjectName(QString::fromUtf8("saveApplyButton"));
        saveApplyButton->setGeometry(QRect(230, 550, 121, 27));
        duplicateRuleButton = new QPushButton(centralwidget);
        duplicateRuleButton->setObjectName(QString::fromUtf8("duplicateRuleButton"));
        duplicateRuleButton->setGeometry(QRect(110, 550, 92, 27));
        ruleEditButtonBox = new QDialogButtonBox(centralwidget);
        ruleEditButtonBox->setObjectName(QString::fromUtf8("ruleEditButtonBox"));
        ruleEditButtonBox->setGeometry(QRect(560, 550, 176, 27));
        ruleEditButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 750, 25));
        menuTools = new QMenu(menubar);
        menuTools->setObjectName(QString::fromUtf8("menuTools"));
        menuApplication = new QMenu(menubar);
        menuApplication->setObjectName(QString::fromUtf8("menuApplication"));
        menuRule = new QMenu(menubar);
        menuRule->setObjectName(QString::fromUtf8("menuRule"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuApplication->menuAction());
        menubar->addAction(menuRule->menuAction());
        menubar->addAction(menuTools->menuAction());
        menuTools->addAction(actionSettings);
        menuTools->addAction(actionStatistics);
        menuTools->addSeparator();
        menuTools->addAction(actionNetfilter_output);
        menuApplication->addAction(actionApply_modifications);
        menuApplication->addAction(actionReset);
        menuApplication->addSeparator();
        menuApplication->addAction(actionClose);
        menuRule->addAction(actionNew);
        menuRule->addAction(actionDuplicate);
        menuRule->addAction(actionDelete);
        menuRule->addSeparator();
        menuRule->addAction(actionSave_rule);
        menuRule->addAction(actionCancel_changes);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Packet Filter", 0, QApplication::UnicodeUTF8));
        actionClose->setText(QApplication::translate("MainWindow", "Close", 0, QApplication::UnicodeUTF8));
        actionClose->setShortcut(QApplication::translate("MainWindow", "Ctrl+X", 0, QApplication::UnicodeUTF8));
        actionApply_modifications->setText(QApplication::translate("MainWindow", "Save and apply modifications", 0, QApplication::UnicodeUTF8));
        actionApply_modifications->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+S", 0, QApplication::UnicodeUTF8));
        actionReset->setText(QApplication::translate("MainWindow", "Reset all modifications", 0, QApplication::UnicodeUTF8));
        actionReset->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+R", 0, QApplication::UnicodeUTF8));
        actionSettings->setText(QApplication::translate("MainWindow", "Settings", 0, QApplication::UnicodeUTF8));
        actionSave_rule->setText(QApplication::translate("MainWindow", "Save rule", 0, QApplication::UnicodeUTF8));
        actionSave_rule->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionNew->setText(QApplication::translate("MainWindow", "New", 0, QApplication::UnicodeUTF8));
        actionNew->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0, QApplication::UnicodeUTF8));
        actionDelete->setText(QApplication::translate("MainWindow", "Delete", 0, QApplication::UnicodeUTF8));
        actionDuplicate->setText(QApplication::translate("MainWindow", "Duplicate", 0, QApplication::UnicodeUTF8));
        actionNetfilter_output->setText(QApplication::translate("MainWindow", "Netfilter output", 0, QApplication::UnicodeUTF8));
        actionCancel_changes->setText(QApplication::translate("MainWindow", "Cancel changes", 0, QApplication::UnicodeUTF8));
        actionStatistics->setText(QApplication::translate("MainWindow", "Statistics", 0, QApplication::UnicodeUTF8));
        newRuleButton->setText(QApplication::translate("MainWindow", "+", 0, QApplication::UnicodeUTF8));
        deleteRuleButton->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        saveApplyButton->setText(QApplication::translate("MainWindow", "Save and apply", 0, QApplication::UnicodeUTF8));
        duplicateRuleButton->setText(QApplication::translate("MainWindow", "Duplicate", 0, QApplication::UnicodeUTF8));
        menuTools->setTitle(QApplication::translate("MainWindow", "Tools", 0, QApplication::UnicodeUTF8));
        menuApplication->setTitle(QApplication::translate("MainWindow", "Application", 0, QApplication::UnicodeUTF8));
        menuRule->setTitle(QApplication::translate("MainWindow", "Rule", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
