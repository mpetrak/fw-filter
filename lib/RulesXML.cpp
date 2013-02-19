
#include <libxml/tree.h>


#include "RulesXML.h"

const char* RulesXML::FILE = "data/rules.xml";
const char* RulesXML::XML_VERSION = "1.0";
const char* RulesXML::XML_ENCODING = "UTF-8";

const char* RulesXML::RULE_NEGATION = "negation";
const char* RulesXML::RULE_ADDRESS = "address";
const char* RulesXML::RULE_MASK = "mask";

const char* RulesXML::NODE_ROOT = "rules";
const char* RulesXML::NODE_RULE = "rule";
const char* RulesXML::RULE_NAME = "name";
const char* RulesXML::RULE_ACTION = "action";
const char* RulesXML::RULE_DESCRIPTON = "description";

const char* RulesXML::LAYER_LINK = "link";
const char* RulesXML::LAYER_NET = "net";
    
const char* RulesXML::RULE_IN_IFACE = "in_iface";
const char* RulesXML::RULE_OUT_IFACE = "out_iface";
const char* RulesXML::RULE_PROTOCOL = "protocol";
const char* RulesXML::RULE_SOURCE = "source";
const char* RulesXML::RULE_DEST = "dest";

RulesXML::RulesXML() {
}

bool RulesXML::saveRules(QList<FilterRule> rules) {
    FilterRule rule;
    xmlNodePtr ruleNode;
    
    this->rootNode = xmlNewNode(NULL, BAD_CAST RulesXML::NODE_ROOT);
    foreach(rule, rules) {
        
        ruleNode = rule2XmlNode(&rule);
        xmlAddChild(this->rootNode, ruleNode);
        
    }
    
    this->doc = xmlNewDoc(BAD_CAST RulesXML::XML_VERSION);
    xmlDocSetRootElement(this->doc, this->rootNode);
    
    int result = xmlSaveFormatFileEnc(RulesXML::FILE, this->doc, RulesXML::XML_ENCODING, 1);
    
    return true;
}

xmlNodePtr RulesXML::rule2XmlNode(FilterRule* rule) {
    char *mask;
    /* create rule node */
    xmlNodePtr ruleNode = xmlNewNode(NULL, BAD_CAST RulesXML::NODE_RULE);
    /* create link layer node */
    xmlNodePtr linkNode = xmlNewNode(NULL, BAD_CAST RulesXML::LAYER_LINK);
    /* create net layer node */
    xmlNodePtr netNode = xmlNewNode(NULL, BAD_CAST RulesXML::LAYER_NET);
    
    
    /* add name as a node attribute */
    xmlNewProp(ruleNode, BAD_CAST RulesXML::RULE_NAME,
            BAD_CAST rule->getName().toAscii().data());
    /* add action as a node attribute */
    xmlNewProp(ruleNode, BAD_CAST RulesXML::RULE_ACTION,
            BAD_CAST rule->getAction().toAscii().data());
    
    /* add description */
    value2Node(&ruleNode, RulesXML::RULE_DESCRIPTON,
            rule->getDescription().toAscii().data(), false);    
    
    /* input interface */
    value2Node(&ruleNode, RulesXML::RULE_IN_IFACE,
            rule->getInInterface().toAscii().data(), rule->isInInterfaceNeg());
    
    /* output interface */
    value2Node(&ruleNode, RulesXML::RULE_OUT_IFACE,
            rule->getOutInterface().toAscii().data(), rule->isOutInterfaceNeg());
    
    /* link layer protocol */
    value2Node(&linkNode, RulesXML::RULE_PROTOCOL,
            rule->getEbProtocol().toAscii().data(), rule->isEbProtocolNeg());
    
    /* link layer source */
    address2Node(&linkNode, RulesXML::RULE_SOURCE,
            rule->getEbSource().toAscii().data(),
            rule->getEbSourceMask().toAscii().data(), rule->isEbSourceNeg());
    
    /* link layer destination */
    address2Node(&linkNode, RulesXML::RULE_DEST,
            rule->getEbDest().toAscii().data(),
            rule->getEbDestMask().toAscii().data(), rule->isEbDestNeg());
    
    /* net layer protocol */
    value2Node(&netNode, RulesXML::RULE_PROTOCOL,
            rule->getIpProtocol().toAscii().data(), rule->isIpProtocolNeg());
    
    /* net layer source */
    
    sprintf(mask, "%d", rule->getIpSourceMask());
    address2Node(&netNode, RulesXML::RULE_SOURCE,
            rule->getIpSource().toAscii().data(),
            mask, rule->isIpSourceNeg());
    
    /* net layer dest */
    sprintf(mask, "%d", rule->getIpDestMask());
    address2Node(&netNode, RulesXML::RULE_SOURCE,
            rule->getIpDest().toAscii().data(),
            mask, rule->isIpDestNeg());
    
    /* add link and net layers nodes to rule node */
    xmlAddChild(ruleNode, linkNode);
    xmlAddChild(ruleNode, netNode);
    
    return ruleNode;
}

void RulesXML::value2Node(xmlNodePtr *parent, const char *nodeName, char *value, bool negation) {
    
    xmlNodePtr node = xmlNewChild(*parent, NULL, BAD_CAST nodeName, BAD_CAST value);
    if(negation)
        xmlNewProp(node, BAD_CAST RulesXML::RULE_NEGATION, BAD_CAST RulesXML::RULE_NEGATION);
}

void RulesXML::address2Node(xmlNodePtr *parent, const char *nodeName, char *address, char *mask, bool negation) {
    
    xmlNodePtr addrNode = xmlNewNode(NULL, BAD_CAST nodeName);
    if(negation)
        xmlNewProp(addrNode, BAD_CAST RulesXML::RULE_NEGATION, BAD_CAST RulesXML::RULE_NEGATION);
    
    xmlNewChild(addrNode, NULL, BAD_CAST RulesXML::RULE_ADDRESS, BAD_CAST address);
    xmlNewChild(addrNode, NULL, BAD_CAST RulesXML::RULE_MASK, BAD_CAST mask);
    
    xmlAddChild(*parent, addrNode);
}



