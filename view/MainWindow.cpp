/*
 * File:   MainWindow.cpp
 * Author: petris
 *
 * Created on 28. listopad 2012, 11:34
 */

#include "MainWindow.h"

MainWindow::MainWindow() {
    widget.setupUi(this);
}

MainWindow::~MainWindow() {
}

void MainWindow::on_actionClose_triggered() {
    close();
}
