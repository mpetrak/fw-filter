
#ifndef SETTINGSDIALOG_H
#define	SETTINGSDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QCheckBox>
#include <QComboBox>

#include "../lib/Configuration.h"

class SettingsDialog : public QDialog {
public:
    SettingsDialog(QWidget *parent, Configuration *configuration);
    virtual ~SettingsDialog();

private:

    /** Configuration object reference */
    Configuration *configuration;

    /** List of possible default actions */
    QStringList actions;

    /** Debug mode */
    QCheckBox *debugBox;
    /** Write rules to system at start */
    QCheckBox *writeOnStartBox;
    /** Default action */
    QComboBox *defaultActionSelect;

    /** Dialog buttons */
    QDialogButtonBox *buttons;

    private 
slots:
    /** 
     * Slot for accepting dialog 
     */
    void accept();
};

#endif	/* SETTINGSDIALOG_H */

