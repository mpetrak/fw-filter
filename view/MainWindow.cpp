
#include <linux/stddef.h>
#include <qt4/QtGui/qmessagebox.h>

#include "MainWindow.h"

MainWindow::MainWindow() {
    widget.setupUi(this);
    this->setFixedSize(750, 712);

    /* enable drag and drop for rules view */
    widget.rulesView->setSelectionMode(QAbstractItemView::SingleSelection);
    widget.rulesView->setDragEnabled(true);
    widget.rulesView->setAcceptDrops(true);
    widget.rulesView->setDropIndicatorShown(true);
    widget.rulesView->setDragDropMode(QAbstractItemView::InternalMove);

    ruleEditWidget = new RuleEditWidget(widget.centralwidget);
    ruleEditWidget->setObjectName(QString::fromUtf8("ruleEditWidget"));
    ruleEditWidget->setGeometry(QRect(230, 10, 511, 531));
    /* connecting rule edit widget slot to clicke signal from rules view in setupActions method */

    logView = new LogView(widget.centralwidget);
    logView->setObjectName(QString::fromUtf8("logView"));
    logView->setGeometry(QRect(10, 590, 731, 84));

    /** 
     * Connect signal from editing widget that rule is changed to class slot.
     * Used for control GUI reaction (warning on unsave changes etc).
     */
    QObject::connect(ruleEditWidget, SIGNAL(ruleChanged()),
            this, SLOT(actualRuleChanged()));

    /* after start disable some action - no change made */
    ruleChanged = false;
    unsavedChanges = false;
    setupActions(); // must be called after initilization of ruleEditWidget
}

MainWindow::~MainWindow() {
    free(this->configuration);
}

void MainWindow::setRulesViewModel(QAbstractItemModel* model) {
    this->rulesModel = (FilterRulesModel *) model;

    widget.rulesView->setModel(model);
    ruleEditWidget->setRulesModel((FilterRulesModel *) model);

    /* connect dropped signal from model to slot, that clear rule selection */
    connect(rulesModel, SIGNAL(droppedItem()), this, SLOT(clearRuleSelection()));
}

void MainWindow::setConfiguration(Configuration* configuration) {
    this->configuration = configuration;

    logView->setEnabled(configuration->isDebugMode());

    /* reaction of GUI onto new configuration */
    oldDefaultAction = configuration->getDefaultAction();
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
        rulesModel->newRule(index.row() + 1);
    } else {

        /* if no index is selected, insert new rule to the top */
        Logger::getInstance()->debug(QString::fromUtf8(
                "New rule on position: 0").toAscii().data());
        rulesModel->newRule(0);
    }

    unsavedChanges = true;
    setupActions();
}

void MainWindow::on_deleteRuleButton_clicked() {
    QItemSelectionModel *selection = widget.rulesView->selectionModel();
    QModelIndexList indexes = selection->selectedIndexes();
    QModelIndex index;

    /* delete rule on each selected index */
    foreach(index, indexes) {
        Logger::getInstance()->debug(QString::fromUtf8(
                "Deleting rule on position: %1").arg(index.row()).toAscii().data());
        rulesModel->deleteRule(index.row());
    }

    /* Reload edit widget with new rule on deleted position */
    ruleEditWidget->ruleSelected(index);

    unsavedChanges = true;
    ruleChanged = false;
    setupActions();
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
            rulesModel->duplicateRule(index.row());
        }

        unsavedChanges = true;
        setupActions();
    }
}

void MainWindow::on_saveApplyButton_clicked() {
    /* same as action aplly */
    this->on_actionApply_modifications_triggered();
}

void MainWindow::on_ruleEditButtonBox_accepted() {
    QItemSelectionModel *selection = widget.rulesView->selectionModel();
    QModelIndexList indexes = selection->selectedIndexes();

    if (indexes.count() > 0) {

        /* get last selected index and save rule on it */
        QModelIndex index = indexes.at(indexes.count() - 1);
        if (!this->ruleEditWidget->ruleSave(index)) {

            Logger::getInstance()->debug("Rule saving fault");
        } else {

            Logger::getInstance()->debug("Rule saved");

            /* enable / disable GUI actions */
            ruleChanged = false;
            unsavedChanges = true;
            setupActions();
        }
    } else {

        QMessageBox::critical(this, QString::fromUtf8("Save error"),
                QString::fromUtf8("Cannot save rule - no rule selected."), QMessageBox::Ok, QMessageBox::Ok);
    }
}

void MainWindow::on_ruleEditButtonBox_rejected() {
    QItemSelectionModel *selection = widget.rulesView->selectionModel();
    QModelIndexList indexes = selection->selectedIndexes();

    if (indexes.count() > 0) {
        /* due to selection model only one index is possible to select */
        ruleEditWidget->ruleSelected(indexes.first());

        ruleChanged = false;
        setupActions();

        Logger::getInstance()->debug("Rule reloaded");

    } else {
        QMessageBox::critical(this, QString::fromUtf8("Internal error"),
                QString::fromUtf8("No index selected"));
    }
}

void MainWindow::on_actionApply_modifications_triggered() {

    if (this->rulesModel != NULL) {
        bool systemSuccess, XMLSuccess;

        RulesPusher *pusher = new RulesPusher(configuration);
        systemSuccess = pusher->writeRules(this->rulesModel->getRulesList());
        if (!systemSuccess) {
            QMessageBox::critical(this, QString::fromUtf8("Save error"),
                    QString::fromUtf8("Error during saving rules to system!"), QMessageBox::Ok, QMessageBox::Ok);
        }
        free(pusher);

        RulesXML *xml = new RulesXML();
        XMLSuccess = xml->saveRules(this->rulesModel->getRulesList());
        if (!XMLSuccess) {
            QMessageBox::critical(this, QString::fromUtf8("Save error"),
                    QString::fromUtf8("Error during saving rules to XML file!"), QMessageBox::Ok, QMessageBox::Ok);
        }
        free(xml);

        /* write to state variable, if there is unsave changes */
        unsavedChanges = !(XMLSuccess && systemSuccess);
        setupActions();
    } else {
        QMessageBox::critical(this, QString::fromUtf8("Internal error"),
                QString::fromUtf8("NULL rulesModel"), QMessageBox::Ok, QMessageBox::Ok);
    }
}

void MainWindow::on_actionSave_rule_triggered() {
    /* same as save button clicked */
    this->on_ruleEditButtonBox_accepted();
}

void MainWindow::on_actionCancel_changes_triggered() {
    /* smae as cancel button clicked */
    this->on_ruleEditButtonBox_rejected();
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

    /* ask for confirmation */
    if (QMessageBox::question(this, QString::fromUtf8("Are you sure?"),
            QString::fromUtf8("All unsaved changes will be lost.\n"
            "Really reset all modifications?"),
            QMessageBox::Yes, QMessageBox::No,
            QMessageBox::NoButton) == QMessageBox::Yes) {

        /* reload rules model */
        this->rulesModel->reloadRules();

        /* change state variables and setup actions in GUI */
        unsavedChanges = false;
        ruleChanged = false;
        setupActions();

        /* call edit widget with invalid index to clean it */
        ruleEditWidget->ruleSelected(QModelIndex());
    }
}

void MainWindow::on_actionSettings_triggered() {
    /* save default action to compare in new settings method */
    oldDefaultAction = this->configuration->getDefaultAction();
    SettingsDialog *settings = new SettingsDialog(this, this->configuration);
    QObject::connect(settings, SIGNAL(accepted()), this, SLOT(newSettings()));
    settings->show();
}

void MainWindow::on_actionStatistics_triggered() {
    StatisticsDialog *stats = new StatisticsDialog(this, rulesModel->getRulesList());
    stats->show();
}

void MainWindow::on_actionNetfilter_output_triggered() {
    RulesPusher *pusher = new RulesPusher(configuration);
    /* turn out logging */
    pusher->setLog(false);
    QString out = QString::fromUtf8("---EBTABLES module-----------------------------\n");
    out.append(pusher->getEbOutput(rulesModel->getRulesList()));
    out.append(QString::fromUtf8("\n---IPTABLES module---------------------------\n"));
    out.append(pusher->getIpOutput(rulesModel->getRulesList(), FilterRule::EB_PROTO_VALUE_IPV4));
    out.append(QString::fromUtf8("\n---IP6TABLES module--------------------------\n"));
    out.append(pusher->getIpOutput(rulesModel->getRulesList(), FilterRule::EB_PROTO_VALUE_IPV6));
    free(pusher);

    NfOutputDialog *nfOutput = new NfOutputDialog(this, out);
    nfOutput->show();
}

void MainWindow::newSettings() {

    if (oldDefaultAction != this->configuration->getDefaultAction()) {
        this->unsavedChanges = true;
        setupActions();
    }

    if (this->configuration->isDebugMode()) {
        this->logView->setEnabled(true);
        this->logView->setVisible(true);
        this->setFixedSize(750, 712);
    } else {
        this->logView->setEnabled(false);
        this->logView->setVisible(false);
        this->setFixedSize(750, 628);
    }

    this->repaint();
    widget.centralwidget->repaint();
    Logger::getInstance()->debug("New settings accepted");
}

void MainWindow::actualRuleChanged() {
    ruleChanged = true;
    setupActions();
}

void MainWindow::clearRuleSelection() {
    /* clear edit widget */
    this->ruleEditWidget->ruleSelected(QModelIndex());

    /* change order - change state of unsaved changes */
    unsavedChanges = true;
    setupActions();
}

void MainWindow::setupActions() {
    widget.actionSave_rule->setEnabled(ruleChanged);
    widget.actionCancel_changes->setEnabled(ruleChanged);
    widget.ruleEditButtonBox->setEnabled(ruleChanged);
    widget.duplicateRuleButton->setEnabled(!ruleChanged);
    widget.actionDuplicate->setEnabled(!ruleChanged);
    widget.actionNew->setEnabled(!ruleChanged);
    widget.newRuleButton->setEnabled(!ruleChanged);

    widget.rulesView->setDragEnabled(!ruleChanged);
    widget.rulesView->setAcceptDrops(!ruleChanged);
    if (ruleChanged) {
        widget.rulesView->setSelectionMode(QAbstractItemView::NoSelection);
        QObject::disconnect(widget.rulesView, SIGNAL(clicked(QModelIndex)),
                ruleEditWidget, SLOT(ruleSelected(QModelIndex)));
    } else {
        widget.rulesView->setSelectionMode(QAbstractItemView::SingleSelection);
        /* Connect selection signal from rules view to widget for editing rule */
        QObject::connect(widget.rulesView, SIGNAL(clicked(QModelIndex)),
                ruleEditWidget, SLOT(ruleSelected(QModelIndex)));
    }


    widget.actionApply_modifications->setEnabled(unsavedChanges && !ruleChanged);
    widget.actionReset->setEnabled(unsavedChanges && !ruleChanged);
    widget.saveApplyButton->setEnabled(unsavedChanges && !ruleChanged);
}

void MainWindow::closeEvent(QCloseEvent* event) {
    /* on existing unsaved changes throw dialog to confirm exiting application */
    if (unsavedChanges || ruleChanged) {

        if (QMessageBox::question(this, QString::fromUtf8("Are you sure?"),
                QString::fromUtf8("There are unsaved changes, which will be lost after closing.\n"
                "Really quit application?"),
                QMessageBox::Yes, QMessageBox::No,
                QMessageBox::NoButton) == QMessageBox::Yes) {
            event->accept();
        } else {
            event->ignore();
        }

    } else {

        event->accept();
    }
}