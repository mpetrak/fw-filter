/*
 * File:   MainWindow.cpp
 * Author: petris
 *
 * Created on 28. listopad 2012, 11:34
 */

#include "MainWindow.h"

MainWindow::MainWindow() {
    widget.setupUi(this);
    /* after start disable some action - no change made */
    widget.actionApply_modifications->setEnabled(false);
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
}

MainWindow::~MainWindow() {
}

void MainWindow::setRulesViewModel(QAbstractItemModel* model) {
    widget.rulesView->setModel(model);
    ruleEditWidget->setRulesModel((FilterRulesModel *) model);
}

void MainWindow::on_actionClose_triggered() {
    close();
}
