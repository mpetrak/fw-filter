/*
 * File:   main.cpp
 * Author: petris
 *
 * Created on 19. listopad 2012, 14:51
 */

#include <QtGui/QApplication>
#include <QtGui/QMessageBox>

#include "../view/MainWindow.h"
#include "../model/FilterRulesModel.h"
#include "../lib/Logger.h"
#include "../lib/Configuration.h"

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);

    MainWindow main;

    Logger::getInstance()->clearLog();
    Configuration *config = new Configuration();
    if (!config->loadFromXML()) {
        QMessageBox::critical(NULL, QString::fromUtf8("Load error"),
                QString::fromUtf8("Error during loading configuration from XML file"),
                QMessageBox::Ok, QMessageBox::Ok);
    }
    main.setConfiguration(config);

    FilterRulesModel *rulesModel = new FilterRulesModel();
    main.setRulesViewModel(rulesModel);

    if (getuid() != 0) {
        QMessageBox::warning(NULL, QString::fromUtf8("Aditionals privileges needed"),
                QString::fromUtf8("It`s recommended to run application with root privileges."),
                QMessageBox::Ok, QMessageBox::Ok);
    }

    main.show();

    return app.exec();
}
