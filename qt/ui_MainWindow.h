/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created: Fri Feb 15 11:53:51 2013
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
#include <QtGui/QHeaderView>
#include <QtGui/QListView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
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
    QWidget *centralwidget;
    QListView *rulesView;
    QPushButton *newRuleButton;
    QPushButton *deleteRuleButton;
    QPushButton *saveEditButton;
    QMenuBar *menubar;
    QMenu *menuTools;
    QMenu *menuApplication;
    QMenu *menuRule;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(750, 644);
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
        newRuleButton->setGeometry(QRect(10, 550, 92, 27));
        newRuleButton->setFlat(false);
        deleteRuleButton = new QPushButton(centralwidget);
        deleteRuleButton->setObjectName(QString::fromUtf8("deleteRuleButton"));
        deleteRuleButton->setGeometry(QRect(110, 550, 92, 27));
        saveEditButton = new QPushButton(centralwidget);
        saveEditButton->setObjectName(QString::fromUtf8("saveEditButton"));
        saveEditButton->setGeometry(QRect(650, 550, 92, 27));
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
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuApplication->menuAction());
        menubar->addAction(menuRule->menuAction());
        menubar->addAction(menuTools->menuAction());
        menuTools->addAction(actionSettings);
        menuApplication->addAction(actionApply_modifications);
        menuApplication->addAction(actionReset);
        menuApplication->addSeparator();
        menuApplication->addAction(actionClose);
        menuRule->addAction(actionNew);
        menuRule->addAction(actionDelete);
        menuRule->addAction(actionSave_rule);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Packet Filter", 0, QApplication::UnicodeUTF8));
        actionClose->setText(QApplication::translate("MainWindow", "Close", 0, QApplication::UnicodeUTF8));
        actionClose->setShortcut(QApplication::translate("MainWindow", "Ctrl+X", 0, QApplication::UnicodeUTF8));
        actionApply_modifications->setText(QApplication::translate("MainWindow", "Apply modifications", 0, QApplication::UnicodeUTF8));
        actionApply_modifications->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+S", 0, QApplication::UnicodeUTF8));
        actionReset->setText(QApplication::translate("MainWindow", "Reset", 0, QApplication::UnicodeUTF8));
        actionSettings->setText(QApplication::translate("MainWindow", "Settings", 0, QApplication::UnicodeUTF8));
        actionSave_rule->setText(QApplication::translate("MainWindow", "Save rule", 0, QApplication::UnicodeUTF8));
        actionSave_rule->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionNew->setText(QApplication::translate("MainWindow", "New", 0, QApplication::UnicodeUTF8));
        actionNew->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0, QApplication::UnicodeUTF8));
        actionDelete->setText(QApplication::translate("MainWindow", "Delete", 0, QApplication::UnicodeUTF8));
        newRuleButton->setText(QApplication::translate("MainWindow", "New", 0, QApplication::UnicodeUTF8));
        deleteRuleButton->setText(QApplication::translate("MainWindow", "Delete", 0, QApplication::UnicodeUTF8));
        saveEditButton->setText(QApplication::translate("MainWindow", "Save", 0, QApplication::UnicodeUTF8));
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
