
#ifndef _MAINWINDOW_H
#define	_MAINWINDOW_H

#include <QtGui/QMessageBox>
#include <QCloseEvent>

#include "../qt/ui_MainWindow.h"
#include "RuleEditWidget.h"
#include "LogView.h"
#include "SettingsDialog.h"
#include "NfOutputDialog.h"
#include "../lib/RulesPusher.h"
#include "../lib/RulesXML.h"
#include "../lib/Logger.h"
#include "../lib/Configuration.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow();
    virtual ~MainWindow();

    /**
     * Setter for list model of rules.
     * @param model rules list model
     */
    void setRulesViewModel(QAbstractItemModel *model);

    /**
     * Setter for configuration.
     * @param configuration configuration
     */
    void setConfiguration(Configuration *configuration);

private:

    /**
     * Setup GUI actions as enable or disable.
     * Depends on actual editing rule is changed or not.
     */
    void setupActions();\

    void closeEvent(QCloseEvent* event);

    Ui::MainWindow widget;

    /** Configuration */
    Configuration *configuration;

    /** Model of rules view */
    FilterRulesModel *rulesModel;

    /** Widget for rule editing */
    RuleEditWidget *ruleEditWidget;

    /** Log view */
    LogView *logView;

    /** Actualy editing rule is changed or not */
    bool ruleChanged;
    /** If some rule has been changed and changes have not been written to system yet */
    bool unsavedChanges;

private slots:
    void on_newRuleButton_clicked();
    void on_deleteRuleButton_clicked();
    void on_duplicateRuleButton_clicked();
    void on_saveApplyButton_clicked();
    void on_ruleEditButtonBox_accepted();
    void on_ruleEditButtonBox_rejected();
    void on_actionClose_triggered();
    void on_actionSave_rule_triggered();
    void on_actionCancel_changes_triggered();
    void on_actionNew_triggered();
    void on_actionDelete_triggered();
    void on_actionDuplicate_triggered();
    void on_actionApply_modifications_triggered();
    void on_actionReset_triggered();
    void on_actionSettings_triggered();
    void on_actionNetfilter_output_triggered();

    /**
     * Slot to call on settings is changed.
     */
    void newSettings();

    /**
     * Slot to call if actual editing rule is changed.
     */
    void actualRuleChanged();

    /**
     * Slot to clear selection of rules and rule edit widget.
     */
    void clearRuleSelection();
};

#endif	/* _MAINWINDOW_H */
