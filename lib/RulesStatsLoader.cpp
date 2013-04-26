
#include <stdlib.h>

#include "RulesStatsLoader.h"

const char* RulesStatsLoader::EB_COMMAND = "ebtalbes -L --Lc";
const char* RulesStatsLoader::EB_FILE = "data/ebstats";
const char* RulesStatsLoader::IP_COMMAND = "iptables -L -v";
const char* RulesStatsLoader::IP_FILE = "data/ipstats";
const char* RulesStatsLoader::IP6_COMMAND = "ip6tables -L -v";
const char* RulesStatsLoader::IP6_FILE = "data/ip6stats";

RulesStatsLoader::RulesStatsLoader() {
}

RulesStatsLoader::~RulesStatsLoader() {
}

bool RulesStatsLoader::loadStatistics(QList<FilterRule>* rules) {

    int ipReturn = -1;
    int ip6Return = -1;
    //int ebReturn = -1;

    ipReturn = system(QString::fromUtf8("%1 > %2").arg(IP_COMMAND, IP_FILE).toAscii().data());
    ip6Return = system(QString::fromUtf8("%1 > %2").arg(IP6_COMMAND, IP6_FILE).toAscii().data());

    if (ipReturn != 0) {
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

        Logger::getInstance()->debug("Statistics sucessfully loaded");
        return true;
    }
}

void RulesStatsLoader::loadIpStats(FilterRule* rule, const char* ipFilename) {
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
