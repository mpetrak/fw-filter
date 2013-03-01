
#ifndef LOGGERVIEW_H
#define	LOGGERVIEW_H

#include <QTextEdit>
#include <QThread>
#include <QFile>
#include <QTextStream>

#include "../lib/Logger.h"

class LogView : public QTextEdit {
    Q_OBJECT

public:
    LogView(QWidget *parent);
    virtual ~LogView();

public slots:
    /**
     * Add message to the log.
     * @param message message
     */
    void addMessage(const char *message);
};

#endif	/* LOGGERVIEW_H */

