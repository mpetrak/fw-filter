/* 
 * File:   MainWindow.h
 * Author: petris
 *
 * Created on 28. listopad 2012, 11:34
 */

#ifndef _MAINWINDOW_H
#define	_MAINWINDOW_H

#include "ui_MainWindow.h"
#include "RuleEditWidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow();
    virtual ~MainWindow();

    /**
     * Setter for list model of rules.
     * @param model rules list model
     */
    void setRulesViewModel(QAbstractItemModel *model);

private:
    Ui::MainWindow widget;

    /** Widget for rule editing */
    RuleEditWidget *ruleEditWidget;

private slots:
    void on_newRuleButton_clicked();
    void on_deleteRuleButton_clicked();
    void on_actionClose_triggered();

signals:
    void newRule(int position);
    void deleteRule(int position);
    void selectedRule(QModelIndex index);

};

#endif	/* _MAINWINDOW_H */
