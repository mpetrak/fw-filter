
#ifndef LOGGERVIEW_H
#define	LOGGERVIEW_H

#include <QTextEdit>
#include <QThread>
#include <QFile>
#include <QTextStream>

class LogView : public QTextEdit {
public:
    LogView(QWidget *parent, const char *logfile);
    virtual ~LogView();

private:
    void read();
    QFile *file;
    QTextStream *stream;
};

#endif	/* LOGGERVIEW_H */

