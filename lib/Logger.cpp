
#include "Logger.h"

const char* Logger::LOGFILE = "data/debug.log";

void Logger::debug(string message) {
    Logger::message((char *)"Debug", message.c_str());
}

void Logger::clearLog() {
    static ofstream logfile;
    logfile.open(LOGFILE, fstream::trunc);
    logfile.close();
}

void Logger::message(char *type, const char *message) {
    static ofstream logfile;
    logfile.open(LOGFILE, fstream::app);
    
    logfile << endl << ">>" << type << ": " << message;
    
    logfile.close();
}
