
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

    Configuration *configuration;
    QStringList actions;

    QCheckBox *debugBox;
    QComboBox *defaultActionSelect;
    QComboBox *forwardActionSelect;
    QComboBox *outputActionSelect;
    
    QDialogButtonBox *buttons;

private slots:
    void accept();
};

#endif	/* SETTINGSDIALOG_H */

