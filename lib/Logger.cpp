
#include "Logger.h"

const char* Logger::LOGFILE = "data/debug.log";

/* initial singleton class at start */
Logger* Logger::logger = 0;

Logger *Logger::getInstance() {

    /* is class initialized or no */
    if (!logger) {
        logger = new Logger(Logger::LOGFILE);
    }

    /* return singleton class instance */
    return logger;
}

Logger::Logger(const char *logfile) {
    this->logfile = logfile;
}

Logger::~Logger() {
}

void Logger::debug(string message) {
    Logger::message((char *) "Debug", message.c_str());
}

void Logger::clearLog() {
    static ofstream log;
    /* open file in truncate mode */
    log.open(this->logfile, fstream::trunc);
    log << ">" << "Log cleared";
    log.close();
}

void Logger::message(char *type, const char *message) {
    static ofstream log;
    time_t rawtime;
    struct tm * timeinfo;
    char timeBuffer [10];

    /* get system time */
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(timeBuffer, 10, "%R:%S", timeinfo);

    /* create log message */
    string inputMessage = ">" + string(timeBuffer) + ">" + string(type) + ": " + string(message);

    /* write message to file */
    log.open(this->logfile, fstream::app);
    log << endl << inputMessage;
    log.close();

    /* emit singal */
    emit newMessage(inputMessage.c_str());
}
