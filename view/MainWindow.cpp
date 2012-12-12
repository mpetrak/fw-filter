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
}

MainWindow::~MainWindow() {
}

void MainWindow::setRulesViewModel(QAbstractItemModel* model) {
    widget.rulesView->setModel(model);
}

void MainWindow::on_actionClose_triggered() {
    close();
}
