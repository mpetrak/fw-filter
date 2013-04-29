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

    /* Write rules to system on start if option is set */
    if (config->isWriteOnStart()) {
        RulesPusher *pusher = new RulesPusher(config);
        bool systemSuccess = pusher->writeRules(rulesModel->getRulesList());
        if (!systemSuccess) {
            QMessageBox::critical(NULL, QString::fromUtf8("Save error"),
                    QString::fromUtf8("Error during saving rules to system!"), QMessageBox::Ok, QMessageBox::Ok);
        }
        free(pusher);
    }

    main.show();

    return app.exec();
}
