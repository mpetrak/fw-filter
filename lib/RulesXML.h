
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
    
    bool saveRules(QList<FilterRule> rules);
    
private:
    xmlNodePtr rule2XmlNode(FilterRule *rule);
    void value2Node(xmlNodePtr *parent, const char *nodeName, char *value, bool negation);
    void address2Node(xmlNodePtr *parent, const char *nodeName, char *address, char *mask, bool negation);

    xmlDocPtr doc;
    xmlNodePtr rootNode;
};

#endif	/* RULESSAVER_H */

