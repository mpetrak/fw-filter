
#ifndef RULESSAVER_H
#define	RULESSAVER_H

#include <stdlib.h>
#include <libxml/tree.h>
#include <libxml/parser.h>

#include "../model/FilterRule.h"

class RulesXML {
public:
    static const char* FILE;
    static const char* XML_VERSION;
    static const char* XML_ENCODING;
    
    static const char* RULE_NEGATION;
    static const char* RULE_ADDRESS;
    static const char* RULE_MASK;
    
    static const char* NODE_ROOT;
    static const char* NODE_RULE;
    static const char* RULE_NAME;
    static const char* RULE_ACTION;
    static const char* RULE_DESCRIPTON;
    static const char* RULE_CHAINS;
    static const char* RULE_CHAIN_INPUT;
    static const char* RULE_CHAIN_FORWARD;
    static const char* RULE_CHAIN_OUTPUT;
    
    static const char* LAYER_LINK;
    static const char* LAYER_NET;
    
    static const char* RULE_IN_IFACE;
    static const char* RULE_OUT_IFACE;
    static const char* RULE_PROTOCOL;
    static const char* RULE_SOURCE;
    static const char* RULE_DEST;
    
    RulesXML();
    
    /**
     * Save rules in list to XML file.
     * @param rules list of rules
     * @return true on success / false on fault
     */
    bool saveRules(QList<FilterRule> rules);
    
    /**
     * Load rules from XML file.
     * @return list of loaded rules
     */
    QList<FilterRule> loadRules();
    
    /**
     * If it was error during loading.
     * @return true if there was error
     */
    bool isLoadError();
private:
    /**
     * Convert one rule to XML node.
     * @param rule rule
     * @return XML node with rule data
     */
    xmlNodePtr rule2Node(FilterRule *rule);
    
    /**
     * Convert rule value to XML node.
     * @param parent parent node of created node
     * @param nodeName name of created node
     * @param value created node value
     * @param negation if value is negatiated
     */
    void value2Node(xmlNodePtr *parent, const char *nodeName, char *value, bool negation);
    
    /**
     * Convert rule address value to XML node
     * @param parent parent node of created node
     * @param nodeName name of created node
     * @param address address value
     * @param mask address mask value
     * @param negation if address value is negatiated
     */
    void address2Node(xmlNodePtr *parent, const char *nodeName, char *address, char *mask, bool negation);
    
    /**
     * Load data about one rule from given XML node
     * and create a rule instance with them.
     * @param ruleNode XML rule node
     * @return instance of rule with loaded data
     */
    FilterRule *node2Rule(xmlNodePtr ruleNode);
    
    /**
     * If given node is negatiated by its attributes.
     * @param node node
     * @return true - node is negtiated / false
     */
    bool nodeNegation(xmlNodePtr node);

    bool loadError;

};

#endif	/* RULESSAVER_H */

