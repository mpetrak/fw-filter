
#include "LogView.h"

LogView::LogView(QWidget *parent, const char *logfile) : QTextEdit(parent) {
    this->setReadOnly(true);
    this->file = new QFile(logfile);
    this->file->open(QIODevice::ReadOnly);
    this->stream = new QTextStream(this->file);

    read();
}

LogView::~LogView() {
    file->close();
    free(this->stream);
    free(this->file);
}

void LogView::read() {
    while (!stream->atEnd()) {
        QString line = stream->readLine();
        this->append(line);
    }
}

