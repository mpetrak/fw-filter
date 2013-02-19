/*
 * File:   MainWindow.cpp
 * Author: petris
 *
 * Created on 28. listopad 2012, 11:34
 */

#include <linux/stddef.h>
#include <qt4/QtGui/qmessagebox.h>

#include "MainWindow.h"

MainWindow::MainWindow() {
    widget.setupUi(this);
    /* after start disable some action - no change made */
    //TODO set enabled to false
    //widget.actionApply_modifications->setEnabled(false);
    widget.actionReset->setEnabled(false);

    /* enable drag and drop for rules view */
    widget.rulesView->setSelectionMode(QAbstractItemView::SingleSelection);
    widget.rulesView->setDragEnabled(true);
    widget.rulesView->setAcceptDrops(true);
    widget.rulesView->setDropIndicatorShown(true);
    widget.rulesView->setDragDropMode(QAbstractItemView::InternalMove);

    ruleEditWidget = new RuleEditWidget(widget.centralwidget);
    ruleEditWidget->setObjectName(QString::fromUtf8("ruleEditWidget"));

    /* Connect selection signal from rules view to widget for editing rule */
    QObject::connect(widget.rulesView, SIGNAL(clicked(QModelIndex)),
            ruleEditWidget, SLOT(ruleSelected(QModelIndex)));

    /* 
     * Connect selection signal from main window to widget for editing rule.
     * Used in case of deleting, then emit this signal to update editing widget
     * from deleted rule to another 
     */
    QObject::connect(this, SIGNAL(selectedRule(QModelIndex)),
            ruleEditWidget, SLOT(ruleSelected(QModelIndex)));

    QObject::connect(this, SIGNAL(saveRule(QModelIndex)),
            ruleEditWidget, SLOT(ruleSave(QModelIndex)));
}

MainWindow::~MainWindow() {
}

void MainWindow::setRulesViewModel(QAbstractItemModel* model) {
    this->rulesModel = (FilterRulesModel *) model;
    
    widget.rulesView->setModel(model);
    ruleEditWidget->setRulesModel((FilterRulesModel *) model);

    QObject::connect(this, SIGNAL(newRule(int)),
            model, SLOT(newRule(int)));

    QObject::connect(this, SIGNAL(deleteRule(int)),
            model, SLOT(deleteRule(int)));
}

void MainWindow::on_actionClose_triggered() {
    close();
}

void MainWindow::on_newRuleButton_clicked() {
    QItemSelectionModel *selection = widget.rulesView->selectionModel();
    QModelIndexList indexes = selection->selectedIndexes();

    if (indexes.count() > 0) {

        /* get last selected index and insert new rule below it */
        QModelIndex index = indexes.at(indexes.count() - 1);
        emit newRule(index.row() + 1);
    } else {

        /* if no index is selected, insert new rule to the top */
        emit newRule(0);
    }
}

void MainWindow::on_deleteRuleButton_clicked() {
    QItemSelectionModel *selection = widget.rulesView->selectionModel();
    QModelIndexList indexes = selection->selectedIndexes();
    QModelIndex index;

    /* delete rule on each selected index */
    foreach(index, indexes) {
        emit deleteRule(index.row());
    }

    /* Emit signal for edit widget about new rule is selected - not deleted one */
    indexes = widget.rulesView->selectionModel()->selectedIndexes();
    emit selectedRule(index);

}

void MainWindow::on_saveEditButton_clicked() {
    QItemSelectionModel *selection = widget.rulesView->selectionModel();
    QModelIndexList indexes = selection->selectedIndexes();

    if (indexes.count() > 0) {

        /* get last selected index and save rule on it */
        QModelIndex index = indexes.at(indexes.count() - 1);
        emit saveRule(index);
    } else {

        QMessageBox::critical(this, QString::fromUtf8("Save error"),
                QString::fromUtf8("Cannot save rule - no rule selected."), QMessageBox::Ok, QMessageBox::Ok);
    }
}

void MainWindow::on_actionApply_modifications_triggered() {
    
    if(this->rulesModel != NULL) {

        RulesPusher *pusher = new RulesPusher();

        if(!pusher->writeRules(this->rulesModel->getRulesList())) {
            QMessageBox::critical(this, QString::fromUtf8("Save error"),
                    QString::fromUtf8("Error during saving rules to system!"), QMessageBox::Ok, QMessageBox::Ok);
        }
        free(pusher);
        
        RulesXML *xml = new RulesXML();
        
        if(!xml->saveRules(this->rulesModel->getRulesList())) {
            QMessageBox::critical(this, QString::fromUtf8("Save error"),
                    QString::fromUtf8("Error during saving rules to XML file!"), QMessageBox::Ok, QMessageBox::Ok);
        }
        free(xml);
        
    } else {
        QMessageBox::critical(this, QString::fromUtf8("Internal error"),
                QString::fromUtf8("NULL rulesModel"), QMessageBox::Ok, QMessageBox::Ok);
    }
}

void MainWindow::on_actionSave_rule_triggered() {
    /* same as save button clicked */
    this->on_saveEditButton_clicked();
}

void MainWindow::on_actionNew_triggered() {
    /* same as new rule button clicked */
    this->on_newRuleButton_clicked();
}

void MainWindow::on_actionDelete_triggered() {
    /* same as delete rule button clicked */
    this->on_deleteRuleButton_clicked();
}
