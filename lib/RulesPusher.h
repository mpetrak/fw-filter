
#ifndef RULESPUSHER_H
#define	RULESPUSHER_H

#include <QString>
#include <QByteArray>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "../model/FilterRule.h"

using namespace std;

class RulesPusher {
public:
    static const char* NF_CHAIN_FORWARD;
    static const char* NF_CHAIN_OUTPUT;
    static const char* NF_CHAIN_INPUT;
    
    static const char* EB_OUTPUT_FILE;
    static const char* IP_OUTPUT_FILE;

    static const char* EB_NEGATION;
    static const char* EB_MASK_DELIMITER;

    static const char* EB_COMMAND;
    static const char* EB_COMMAND_APPEND;
    static const char* EB_COMMAND_CHAIN;
    static const char* EB_COMMAND_INPUT_IFACE;
    static const char* EB_COMMAND_OUTPUT_IFACE;
    static const char* EB_COMMAND_SOURCE_ADDR;
    static const char* EB_COMMAND_DEST_ADDR;
    static const char* EB_COMMAND_PROTOCOL;
    static const char* EB_COMMAND_ACTION;

    static const char* IP_NEGATION;
    static const char*IP_MASK_DELIMITER;

    static const char* IP_COMMAND;
    static const char* IP_COMMAND_APPEND;
    static const char* IP_COMMAND_CHAIN;
    static const char* IP_COMMAND_INPUT_IFACE;
    static const char* IP_COMMAND_OUTPUT_IFACE;
    static const char* IP_COMMAND_SOURCE_ADDR;
    static const char* IP_COMMAND_DEST_ADDR;
    static const char* IP_COMMAND_PROTOCOL;
    static const char* IP_COMMAND_ACTION;
    
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

    /**
     * Print rule to string in a format used by ebtables-restore.
     * @param rule rule instance
     * @return rule specification printed into inline string
     */
    QString rule2EbString(FilterRule *rule);

    /**
     * Print rule to string in a format used by iptables-restore.
     * @param rule rule instance
     * @return rule specification printed into inline string
     */
    QString rule2IpString(FilterRule *rule);

    /**
     * Print rule value to string for ebtables.
     * @param command command
     * @param value value
     * @param negation if value is negatiated
     * @return value as a inline string
     */
    QString value2EbString(const char *command, QString value, bool negation);

    /**
     * Print rule value to string for iptables.
     * @param command command
     * @param value value
     * @param negation if value is negatiated
     * @return value as a inline string
     */
    QString value2IpString(const char *command, QString value, bool negation);

    /**
     * Print address value to a string for ebtables.
     * @param command command
     * @param value value
     * @param mask mask
     * @param negation if value is negatiated
     * @param maskSet if mask is set
     * @return  address value as a inline string
     */
    QString address2EbString(const char *command, QString value, QString mask, bool negation, bool maskSet);

    /**
     * Print address value to a string for iptables.
     * @param command command
     * @param value value
     * @param mask mask
     * @param negation if value is negatiated
     * @param maskSet if mask is set
     * @return  address value as a inline string
     */
    QString address2IpString(const char *command, QString value, QString mask, bool negation, bool maskSet);

    /** output file stream for ebtables */
    ofstream ebFile;
    /** output file stream for iptables */
    ofstream ipFile;

};

#endif	/* RULESPUSHER_H */

