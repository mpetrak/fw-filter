#include <stdlib.h>

#include "RulesStatsLoader.h"

const char* RulesStatsLoader::EB_COMMAND_INPUT = "ebtables -L INPUT --Lc --Ln";
const char* RulesStatsLoader::EB_FILE_INPUT = "data/ebstats_input";

const char* RulesStatsLoader::EB_COMMAND_FORWARD = "ebtables -L FORWARD --Lc --Ln";
const char* RulesStatsLoader::EB_FILE_FORWARD = "data/ebstats_forward";

const char* RulesStatsLoader::EB_COMMAND_OUTPUT = "ebtables -L OUTPUT --Lc --Ln";
const char* RulesStatsLoader::EB_FILE_OUTPUT = "data/ebstats_output";

const char* RulesStatsLoader::IP_COMMAND = "iptables -L -v";
const char* RulesStatsLoader::IP_FILE = "data/ipstats";

const char* RulesStatsLoader::IP6_COMMAND = "ip6tables -L -v";
const char* RulesStatsLoader::IP6_FILE = "data/ip6stats";

RulesStatsLoader::RulesStatsLoader() {
}

RulesStatsLoader::~RulesStatsLoader() {
}

bool RulesStatsLoader::loadStatistics(QList<FilterRule> *rules) {
    
    int ebInputCounter = 1;
    int ebForwardCounter = 1;
    int ebOutputCounter = 1;

    int ipReturn = -1;
    int ip6Return = -1;
    int ebReturn = -1;

    ipReturn = system(QString::fromUtf8("%1 > %2").arg(IP_COMMAND, IP_FILE).toAscii().data());
    ip6Return = system(QString::fromUtf8("%1 > %2").arg(IP6_COMMAND, IP6_FILE).toAscii().data());
    ebReturn = system(QString::fromUtf8("%1 > %2").arg(EB_COMMAND_INPUT, EB_FILE_INPUT).toAscii().data());
    ebReturn += system(QString::fromUtf8("%1 > %2").arg(EB_COMMAND_FORWARD, EB_FILE_FORWARD).toAscii().data());
    ebReturn += system(QString::fromUtf8("%1 > %2").arg(EB_COMMAND_OUTPUT, EB_FILE_OUTPUT).toAscii().data());

    if (ipReturn != 0 || ip6Return != 0 || ebReturn != 0) {
        Logger::getInstance()->debug("Error on system call for get rules statistics");
        return false;
    } else {
        Logger::getInstance()->debug("Loading statistics from system");

        FilterRule rule;
        for (int i = 0; i < rules->count(); i++) {
            rule = rules->at(i);

            /* set previous result to zero */
            rule.setBytesCount(0);
            rule.setPacketsCount(0);
            
            if(rule.isInputPossible()) {
                loadEbStats(&rule, EB_FILE_INPUT, ebInputCounter++);
            }
            
            loadEbStats(&rule, EB_FILE_FORWARD, ebForwardCounter++);
            
            if(rule.isOutputPossible()) {
                loadEbStats(&rule, EB_FILE_OUTPUT, ebOutputCounter++);
            }

            if (!rule.isOnlyBridged()) {
                loadIpStats(&rule, IP_FILE);
                loadIpStats(&rule, IP6_FILE);
            }

            /* replace the rule to write changes into list of rules */
            rules->replace(i, rule);
        }

        /* remove files */
        remove(IP_FILE);
        remove(IP6_FILE);
        remove(EB_FILE_INPUT);
        remove(EB_FILE_FORWARD);
        remove(EB_FILE_OUTPUT);

        Logger::getInstance()->debug("Statistics sucessfully loaded");
        return true;
    }
}

void RulesStatsLoader::loadIpStats(FilterRule* rule, const char *ipFilename) {
    ifstream ipFile;
    string line;
    long packets, bytes;

    ipFile.open(ipFilename, fstream::in);

    /* read file line by line */
    while (!ipFile.eof()) {

        /* get line for file */
        line.clear();
        getline(ipFile, line);

        /* find id of rule (comment) in each line, if founded, parse counters */
        if (line.find(rule->getId().toStdString()) != string::npos) {
            /* parse data from matched line */
            sscanf(line.c_str(), "%lu %lu %*s", &packets, &bytes);

            packets += rule->getPacketsCount();
            bytes += rule->getBytesCount();

            rule->setPacketsCount(packets);
            rule->setBytesCount(bytes);
        }
    }

    ipFile.close();
}

void RulesStatsLoader::loadEbStats(FilterRule* rule, const char *ebFilename, int ruleNumber) {
    ifstream ebFile;
    string line;
    long packets, bytes;
    int lineNumber;

    ebFile.open(ebFilename, fstream::in);

    /* read file line by line */
    while (!ebFile.eof()) {

        /* get line for file */
        line.clear();
        getline(ebFile, line);

        /* find rule number at start of line */
        int match = sscanf(line.c_str(), "%d. %*s", &lineNumber);
        if (match > 0 && lineNumber == ruleNumber) {
            /* get statistics separate by comma from end of line */
            string numbers = line.substr(line.find(","));
            
            /* find names in line */
            unsigned ppos = numbers.find("pcnt");
            unsigned delimiter = numbers.find("--");
            unsigned bpos = numbers.find("bcnt");
            string packetsStr = numbers.substr(ppos, delimiter - 3);
            string bytesStr = numbers.substr(bpos);
            /* parse data from matched line */
            sscanf(packetsStr.c_str(), "%*s = %lu", &packets);
            sscanf(bytesStr.c_str(), "%*s = %lu", &bytes);

            packets += rule->getPacketsCount();
            bytes += rule->getBytesCount();

            rule->setPacketsCount(packets);
            rule->setBytesCount(bytes);
        }
    }

    ebFile.close();
}
