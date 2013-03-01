
#ifndef SETTINGSDIALOG_H
#define	SETTINGSDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QCheckBox>

#include "../lib/RulesPusher.h"
#include "../lib/Configuration.h"

class SettingsDialog : public QDialog {
public:
    SettingsDialog(QWidget *parent, Configuration *configuration);
    virtual ~SettingsDialog();

private:

    Configuration *configuration;

    QCheckBox *debugBox;
    QDialogButtonBox *buttons;

private slots:
    void accept();
};

#endif	/* SETTINGSDIALOG_H */

