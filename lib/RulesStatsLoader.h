
#ifndef RULESSTATSLOADER_H
#define	RULESSTATSLOADER_H

#include <stdio.h>
#include <stdlib.h>
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
    static const char* EB_COMMAND;
    static const char* EB_FILE;

    RulesStatsLoader();
    virtual ~RulesStatsLoader();

    bool loadStatistics(QList<FilterRule> *rules);
private:
    void loadIpStats(FilterRule *rule, const char* ipFilename);

};

#endif	/* RULESSTATSLOADER_H */

