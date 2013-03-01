
#ifndef SETTINGSDIALOG_H
#define	SETTINGSDIALOG_H

#include <QDialog>
#include <QCheckBox>

#include "../lib/RulesPusher.h"

class SettingsDialog : public QDialog {
public:
    SettingsDialog(QWidget *parent);
    virtual ~SettingsDialog();
private:

    QWidget *widget;
    QCheckBox *debugBox;
};

#endif	/* SETTINGSDIALOG_H */

