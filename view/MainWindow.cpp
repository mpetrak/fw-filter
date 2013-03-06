
#include <linux/stddef.h>
#include <qt4/QtGui/qmessagebox.h>

#include "MainWindow.h"
#include "SettingsDialog.h"

MainWindow::MainWindow() {
    widget.setupUi(this);

    /* after start disable some action - no change made */
    //TODO set enabled to false
    //widget.actionApply_modifications->setEnabled(false);
    //widget.actionReset->setEnabled(false);

    /* enable drag and drop for rules view */
    widget.rulesView->setSelectionMode(QAbstractItemView::SingleSelection);
    widget.rulesView->setDragEnabled(true);
    widget.rulesView->setAcceptDrops(true);
    widget.rulesView->setDropIndicatorShown(true);
    widget.rulesView->setDragDropMode(QAbstractItemView::InternalMove);

    ruleEditWidget = new RuleEditWidget(widget.centralwidget);
    ruleEditWidget->setObjectName(QString::fromUtf8("ruleEditWidget"));
    ruleEditWidget->setGeometry(QRect(230, 10, 511, 531));

    logView = new LogView(widget.centralwidget);
    logView->setObjectName(QString::fromUtf8("logView"));
    logView->setGeometry(QRect(10, 590, 731, 84));

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
    free(this->configuration);
}

void MainWindow::setRulesViewModel(QAbstractItemModel* model) {
    this->rulesModel = (FilterRulesModel *) model;

    widget.rulesView->setModel(model);
    ruleEditWidget->setRulesModel((FilterRulesModel *) model);

    /* connect signals to model slots */
    QObject::connect(this, SIGNAL(newRule(int)),
            model, SLOT(newRule(int)));

    QObject::connect(this, SIGNAL(deleteRule(int)),
            model, SLOT(deleteRule(int)));

    QObject::connect(this, SIGNAL(duplicateRule(int)),
            model, SLOT(duplicateRule(int)));
}

void MainWindow::setConfiguration(Configuration* configuration) {
    this->configuration = configuration;

    logView->setEnabled(configuration->isDebugMode());

    /* reaction of GUI onto new configuration */
    newSettings();
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
        Logger::getInstance()->debug(QString::fromUtf8(
                "New rule on position: %1").arg(index.row() + 1).toAscii().data());
        emit newRule(index.row() + 1);
    } else {

        /* if no index is selected, insert new rule to the top */
        Logger::getInstance()->debug(QString::fromUtf8(
                "New rule on position: 0").toAscii().data());
        emit newRule(0);
    }
}

void MainWindow::on_deleteRuleButton_clicked() {
    QItemSelectionModel *selection = widget.rulesView->selectionModel();
    QModelIndexList indexes = selection->selectedIndexes();
    QModelIndex index;

    /* delete rule on each selected index */
    foreach(index, indexes) {
        Logger::getInstance()->debug(QString::fromUtf8(
                "Deleting rule on position: %1").arg(index.row()).toAscii().data());
        emit deleteRule(index.row());
    }

    /* Emit signal for edit widget about new rule is selected - not deleted one */
    indexes = widget.rulesView->selectionModel()->selectedIndexes();
    emit selectedRule(index);

}

void MainWindow::on_duplicateRuleButton_clicked() {
    QItemSelectionModel *selection = widget.rulesView->selectionModel();
    QModelIndexList indexes = selection->selectedIndexes();
    QModelIndex index;

    if (indexes.count() > 0) {

        /* emit signal for each selected index */
        foreach(index, indexes) {
            Logger::getInstance()->debug(QString::fromUtf8(
                    "Duplicating rule on position: %1").arg(index.row()).toAscii().data());
            emit duplicateRule(index.row());
        }
    }
}

void MainWindow::on_saveEditButton_clicked() {
    QItemSelectionModel *selection = widget.rulesView->selectionModel();
    QModelIndexList indexes = selection->selectedIndexes();

    if (indexes.count() > 0) {

        /* get last selected index and save rule on it */
        QModelIndex index = indexes.at(indexes.count() - 1);
        emit saveRule(index);
        Logger::getInstance()->debug("Rule saved");
    } else {

        QMessageBox::critical(this, QString::fromUtf8("Save error"),
                QString::fromUtf8("Cannot save rule - no rule selected."), QMessageBox::Ok, QMessageBox::Ok);
    }
}

void MainWindow::on_actionApply_modifications_triggered() {

    if (this->rulesModel != NULL) {

        RulesPusher *pusher = new RulesPusher(configuration);

        if (!pusher->writeRules(this->rulesModel->getRulesList())) {
            QMessageBox::critical(this, QString::fromUtf8("Save error"),
                    QString::fromUtf8("Error during saving rules to system!"), QMessageBox::Ok, QMessageBox::Ok);
        }
        free(pusher);

        RulesXML *xml = new RulesXML();

        if (!xml->saveRules(this->rulesModel->getRulesList())) {
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

void MainWindow::on_actionDuplicate_triggered() {
    /* same as duplicate rule button clicked */
    this->on_duplicateRuleButton_clicked();
}

void MainWindow::on_actionReset_triggered() {
    this->rulesModel->reloadRules();
}

void MainWindow::on_actionSettings_triggered() {
    SettingsDialog *settings = new SettingsDialog(this, this->configuration);
    QObject::connect(settings, SIGNAL(accepted()), this, SLOT(newSettings()));
    settings->show();
}

void MainWindow::newSettings() {

    if (this->configuration->isDebugMode()) {
        this->logView->setEnabled(true);
        this->logView->setVisible(true);
        this->resize(750, 712);
    } else {
        this->logView->setEnabled(false);
        this->logView->setVisible(false);
        this->resize(750, 628);
    }

    this->repaint();
    Logger::getInstance()->debug("New settings accepted");
}
