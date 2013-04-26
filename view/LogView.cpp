
#include "LogView.h"

LogView::LogView(QWidget *parent) : QTextEdit(parent) {
    this->setReadOnly(true);

    /* connect signals from logger to the slot */
    QObject::connect(Logger::getInstance(), SIGNAL(newMessage(const char*)),
            this, SLOT(addMessage(const char*)));
}

LogView::~LogView() {
}

void LogView::addMessage(const char* message) {
    if (this->isEnabled()) {
        this->append(QString::fromUtf8(message));

        /* scroll to the end of view */
        QScrollBar *scroll = this->verticalScrollBar();
        scroll->setValue(scroll->maximum());
    }
}
