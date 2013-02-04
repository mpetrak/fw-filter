
#ifndef RULESPUSHER_H
#define	RULESPUSHER_H

#define EB_OUTUP_FILE "ebfile"
#define EB_OUTPUT_COMMAND "ebtables-restore"

#include <iostream>
#include <fstream>

#include "../model/FilterRule.h"

using namespace std;

class RulesPusher {
    
public:
    RulesPusher();
    virtual ~RulesPusher();
    
    /**
     * Write rules from given list to system kernel - Netfilter.
     * Now using output files and system call of command eb/iptables-restore.
     * @param rules ordered list of rules by priority.
     * @return true on success / false on fault
     */
    bool writeRules(QList<FilterRule> rules);
private:
    /**
     * Make header of file for ebtables
     * @return header of file
     */
    QString ebFileHeader();
    
    /* output file stream for ebtables */
    ofstream ebFile;

};

#endif	/* RULESPUSHER_H */

