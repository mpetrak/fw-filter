
#ifndef STATISTICSDIALOG_H
#define	STATISTICSDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QList>
#include <QSpinBox>
#include <QLabel>
#include <QGridLayout>
#include <QScrollArea>
#include "../model/FilterRule.h"

class StatisticsDialog : public QDialog {
public:
    StatisticsDialog(QWidget *parent, QList<FilterRule> rules);
    virtual ~StatisticsDialog();
private:
    static int COL_DESC;
    static int COL_PACKETS;
    static int COL_BYTES;

    /** List of filter rules */
    QList<FilterRule> rules;

    /** Central widget */
    QWidget *centralWidget;

};

#endif	/* STATISTICSDIALOG_H */

