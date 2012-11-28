/* 
 * File:   MainWindow.h
 * Author: petris
 *
 * Created on 28. listopad 2012, 11:34
 */

#ifndef _MAINWINDOW_H
#define	_MAINWINDOW_H

#include "ui_MainWindow.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow();
    virtual ~MainWindow();
private:
    Ui::MainWindow widget;
    
private slots:
    void on_actionClose_triggered();
        
};

#endif	/* _MAINWINDOW_H */
