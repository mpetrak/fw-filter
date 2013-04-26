
#ifndef STATISTICSDIALOG_H
#define	STATISTICSDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QList>
#include <QLabel>
#include <QGridLayout>
#include <QScrollArea>
#include <QMessageBox>
#include <QTimer>
#include <QCloseEvent>
#include "../model/FilterRule.h"
#include "../lib/RulesStatsLoader.h"

class StatisticsDialog : public QDialog {
    Q_OBJECT

public:
    StatisticsDialog(QWidget *parent, QList<FilterRule> rules);
    virtual ~StatisticsDialog();
private:
    static int COL_DESC;
    static int COL_PACKETS;
    static int COL_BYTES;
    static int REFRESH;

    void closeEvent(QCloseEvent* event);

    /** List of filter rules */
    QList<FilterRule> rules;

    /** List of labels for rules descriptions */
    QList<QLabel *> ruleLabelList;
    /** List of widgets to print number of packets */
    QList<QLabel *> packetsList;
    /** List of widgets to print number of bytes */
    QList<QLabel *> bytesList;

    /** Central widget */
    QWidget *centralWidget;

    /** Statistics loader */
    RulesStatsLoader *loader;

    /** Internal timer for reloading statistics */
    QTimer *timer;

    /**
     * Formating given bytes to KB, MB, TB if possible
     * @param bytes
     * @return fromated string
     */
    QString formatBytes(long bytes);

private slots:
    /**
     * Loading statistics and fill them to GUI
     */
    void loadStatistics();

};

#endif	/* STATISTICSDIALOG_H */

