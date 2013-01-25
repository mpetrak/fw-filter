/*
 * File:   main.cpp
 * Author: petris
 *
 * Created on 19. listopad 2012, 14:51
 */

#include <QtGui/QApplication>

#include "../view/MainWindow.h"
#include "../model/FilterRulesModel.h"

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);

    MainWindow main;
    
    FilterRulesModel *rulesModel = new FilterRulesModel();
    
    main.setRulesViewModel(rulesModel);
    
    //TODO control superuser
    //TODO load configuration (interfaces aliases)
    
    main.show();
    

    return app.exec();
}
