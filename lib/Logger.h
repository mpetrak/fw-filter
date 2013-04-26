
#ifndef LOGGER_H
#define	LOGGER_H

#include <stdlib.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <QObject>
#include <time.h>

using namespace std;

/**
 * This class is a singleton. Returning everytime the same instance.
 * Singleton because connecting QT signals from this class
 */
class Logger : public QObject {
    Q_OBJECT

public:
    static const char* LOGFILE;
    /**
     * Getting instance of logger.
     * @return logger instance
     */
    static Logger *getInstance();

    /**
     * Log debug message.
     * @param message message
     */
    void debug(string message);

    /**
     * Clearing log file.
     */
    void clearLog();
private:
    /* constuctors and destructors are private */
    Logger(const char* logfile);
    virtual ~Logger();

    /**
     * Process log message with given type.
     * Means log it to the file and emit signal to log view.
     * @param type type of message
     * @param message message
     */
    void message(char *type, const char *message);

    /** singleton logger class */
    static Logger *logger;
    /** log file name */
    const char *logfile;

signals:
    /**
     * Signals emmiting by new message in log.
     * @param message message
     */
    void newMessage(const char *message);

};

#endif	/* LOGGER_H */

