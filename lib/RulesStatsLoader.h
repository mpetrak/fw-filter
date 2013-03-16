
#ifndef RULESSTATSLOADER_H
#define	RULESSTATSLOADER_H

#include <stdio.h>
#include <stdlib.h>
#include <QList>

#include "../model/FilterRule.h"
#include "Logger.h"

class RulesStatsLoader {
public:
    
    static const char* IP_COMMAND;
    static const char* IP_FILE;
    static const char* EB_COMMAND;
    static const char* EB_FILE;
    
    RulesStatsLoader();
    virtual ~RulesStatsLoader();
    
    bool loadStatistics(QList<FilterRule> *rules);
private:

};

#endif	/* RULESSTATSLOADER_H */

