
#ifndef RULESPUSHER_H
#define	RULESPUSHER_H

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
    
    /**
     * Make footer of file for ebtables.
     * @return footer of file
     */
    QString ebFileFooter();
    
    /**
     * Make header of file for iptables
     * @return header of file
     */
    QString ipFileHeader();
    
    /**
     * Make footer of file for iptables.
     * @return footer of file
     */
    QString ipFileFooter();
    
    /** output file stream for ebtables */
    ofstream ebFile;
    /** output file stream for iptables */
    ofstream ipFile;

};

#endif	/* RULESPUSHER_H */

