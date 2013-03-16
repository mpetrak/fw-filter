
#include <stdlib.h>

#include "RulesStatsLoader.h"

const char* RulesStatsLoader::EB_COMMAND = "ebtalbes -L --Lc";
const char* RulesStatsLoader::EB_FILE = "data/ebstats";
const char* RulesStatsLoader::IP_COMMAND = "iptables -L -v";
const char* RulesStatsLoader::IP_FILE = "data/ipstats";

RulesStatsLoader::RulesStatsLoader() {
}

RulesStatsLoader::~RulesStatsLoader() {
}

bool RulesStatsLoader::loadStatistics(QList<FilterRule>* rules) {
    
    int ipReturn = -1;
    int ebReturn = -1;
    
    ipReturn = system(QString::fromUtf8("%1 > %2").arg(IP_COMMAND, IP_FILE).toAscii().data());
    
    if(ipReturn != 0) {
        Logger::getInstance()->debug("Error on system call");
        return false;
    } else {
        Logger::getInstance()->debug("system OK");
    }
 
    
}

