
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
    
private:
    /**
     * Convert one rule to XML node.
     * @param rule rule
     * @return XML node with rule data
     */
    xmlNodePtr rule2XmlNode(FilterRule *rule);
    
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

    /** XML document */
    xmlDocPtr doc;
    /** XML document root node */
    xmlNodePtr rootNode;
};

#endif	/* RULESSAVER_H */

