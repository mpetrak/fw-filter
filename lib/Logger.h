
#ifndef LOGGER_H
#define	LOGGER_H

#include <stdlib.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

class Logger {
public:
    static const char* LOGFILE;
    
    static void debug(string message);
    static void clearLog();
private:
    static void message(char *type, const char *message);

};

#endif	/* LOGGER_H */

