
#ifndef RULESSTATSLOADER_H
#define	RULESSTATSLOADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <QList>
#include <iostream>
#include <fstream>

#include "../model/FilterRule.h"
#include "Logger.h"

using namespace std;

class RulesStatsLoader {
public:

    static const char* IP_COMMAND;
    static const char* IP_FILE;

    static const char* IP6_COMMAND;
    static const char* IP6_FILE;

    static const char* EB_COMMAND_INPUT;
    static const char* EB_FILE_INPUT;

    static const char* EB_COMMAND_FORWARD;
    static const char* EB_FILE_FORWARD;

    static const char* EB_COMMAND_OUTPUT;
    static const char* EB_FILE_OUTPUT;

    RulesStatsLoader();
    virtual ~RulesStatsLoader();

    /**
     * Loading statistics from netfilter and save it back to each rule.
     * @param rules list of filter rules
     * @return bool on success / false on error
     */
    bool loadStatistics(QList<FilterRule> *rules);
private:
    /**
     * Loading statistics from iptables/ip6tables component.
     * @param rule rule for loading statistics
     * @param ipFilename filename with command output (iptables or ip6tables output)
     */
    void loadIpStats(FilterRule *rule, const char *ipFilename);

    /**
     * Loading statistics from ebtables component.
     * @param rule rele for loading statistics
     */
    void loadEbStats(FilterRule *rule, const char *ebFilename, int ruleNumber);
};

#endif	/* RULESSTATSLOADER_H */

