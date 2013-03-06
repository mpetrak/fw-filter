
#include <libxml/tree.h>
#include <qt4/QtCore/qlist.h>


#include "RulesXML.h"
#include "Logger.h"

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
    this->loadError = false;
}

bool RulesXML::saveRules(QList<FilterRule> rules) {
    FilterRule rule;
    xmlNodePtr ruleNode, rootNode;
    xmlDocPtr doc;

    Logger::getInstance()->debug(std::string("Saving rules to file: ") + std::string(RulesXML::FILE));
    rootNode = xmlNewNode(NULL, BAD_CAST RulesXML::NODE_ROOT);

    foreach(rule, rules) {

        ruleNode = rule2Node(&rule);
        xmlAddChild(rootNode, ruleNode);
    }

    doc = xmlNewDoc(BAD_CAST RulesXML::XML_VERSION);
    xmlDocSetRootElement(doc, rootNode);

    int result = xmlSaveFormatFileEnc(RulesXML::FILE, doc, RulesXML::XML_ENCODING, 1);

    if (result < 0) {
        Logger::getInstance()->debug("Rules saving failed");
        return false;
    } else {
        Logger::getInstance()->debug("Rules successfully saved");
        return true;
    }
}

xmlNodePtr RulesXML::rule2Node(FilterRule* rule) {
    char *mask = (char *) malloc(5 * sizeof (char));
    /* create rule node */
    xmlNodePtr ruleNode = xmlNewNode(NULL, BAD_CAST RulesXML::NODE_RULE);
    /* create link layer node */
    xmlNodePtr linkNode = xmlNewNode(NULL, BAD_CAST RulesXML::LAYER_LINK);
    /* create net layer node */
    xmlNodePtr netNode = xmlNewNode(NULL, BAD_CAST RulesXML::LAYER_NET);

    Logger::getInstance()->debug(std::string("Saving rule ") + rule->getName().toAscii().data());
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
    address2Node(&netNode, RulesXML::RULE_DEST,
            rule->getIpDest().toAscii().data(),
            mask, rule->isIpDestNeg());

    /* add link and net layers nodes to rule node */
    xmlAddChild(ruleNode, linkNode);
    xmlAddChild(ruleNode, netNode);

    Logger::getInstance()->debug("Rule saved");
    free(mask);
    return ruleNode;
}

void RulesXML::value2Node(xmlNodePtr *parent, const char *nodeName, char *value, bool negation) {

    xmlNodePtr node = xmlNewChild(*parent, NULL, BAD_CAST nodeName, BAD_CAST value);
    if (negation)
        xmlNewProp(node, BAD_CAST RulesXML::RULE_NEGATION, BAD_CAST RulesXML::RULE_NEGATION);
}

void RulesXML::address2Node(xmlNodePtr *parent, const char *nodeName, char *address, char *mask, bool negation) {

    xmlNodePtr addrNode = xmlNewNode(NULL, BAD_CAST nodeName);
    if (negation)
        xmlNewProp(addrNode, BAD_CAST RulesXML::RULE_NEGATION, BAD_CAST RulesXML::RULE_NEGATION);

    xmlNewChild(addrNode, NULL, BAD_CAST RulesXML::RULE_ADDRESS, BAD_CAST address);
    xmlNewChild(addrNode, NULL, BAD_CAST RulesXML::RULE_MASK, BAD_CAST mask);

    xmlAddChild(*parent, addrNode);
}

QList<FilterRule> RulesXML::loadRules() {
    QList<FilterRule> rulesList;
    xmlDocPtr doc;
    xmlNodePtr rootNode, node;

    this->loadError = false;
    /* parse file to tree */
    Logger::getInstance()->debug(std::string("Loading rules from file: ") + std::string(RulesXML::FILE));
    doc = xmlReadFile(RulesXML::FILE, RulesXML::XML_ENCODING, 0);
    if (doc == NULL) {
        this->loadError = true;
    } else {

        /* iterate rule by rule and load data */
        rootNode = xmlDocGetRootElement(doc);
        for (node = rootNode->children; node; node = node->next) {
            if (node->type == XML_ELEMENT_NODE
                    && strcmp((char *) node->name, RulesXML::NODE_RULE) == 0) {
                FilterRule *rule = node2Rule(node);
                if (rule != NULL)
                    rulesList.append(*rule);
            }
        }
    }

    /* clean up xml parsing */
    xmlFreeDoc(doc);
    xmlCleanupParser();

    Logger::getInstance()->debug("Rules loading finished, XML parser cleaned");

    return rulesList;
}

FilterRule *RulesXML::node2Rule(xmlNodePtr ruleNode) {
    xmlNodePtr node;
    xmlNodePtr linkNode = NULL;
    xmlNodePtr netNode = NULL;
    xmlAttrPtr attr;
    FilterRule *rule = new FilterRule();

    Logger::getInstance()->debug("Parsing rule node");

    /* get rule name and action */
    for (attr = ruleNode->properties; attr; attr = attr->next) {
        if (!strcmp((char *) attr->name, RulesXML::RULE_ACTION)) {
            rule->setAction((char *) xmlNodeGetContent(attr->children));
        } else if (!strcmp((char *) attr->name, RulesXML::RULE_NAME)) {
            rule->setName((char *) xmlNodeGetContent(attr->children));
        }
    }

    /* iterate rule node */
    for (node = ruleNode->children; node; node = node->next) {
        /* skip non element nodes */
        if (node->type != XML_ELEMENT_NODE)
            continue;

        if (!strcmp((char *) node->name, RulesXML::RULE_DESCRIPTON)) {
            rule->setDescription((char *) xmlNodeGetContent(node));

        } else if (!strcmp((char *) node->name, RulesXML::RULE_IN_IFACE)) {
            rule->setInInterface((char *) xmlNodeGetContent(node));
            rule->setInInterfaceNeg(nodeNegation(node));
        } else if (!strcmp((char *) node->name, RulesXML::RULE_OUT_IFACE)) {
            rule->setOutInterface((char *) xmlNodeGetContent(node));
            rule->setOutInterfaceNeg(nodeNegation(node));
        } else if (!strcmp((char *) node->name, RulesXML::LAYER_LINK)) {
            linkNode = node;
        } else if (!strcmp((char *) node->name, RulesXML::LAYER_NET)) {
            netNode = node;
        }
    }

    /* iterate link node */
    if (linkNode != NULL) {
        for (node = linkNode->children; node; node = node->next) {
            /* skip non element nodes */
            if (node->type != XML_ELEMENT_NODE)
                continue;

            /* protocol */
            if (!strcmp((char *) node->name, RulesXML::RULE_PROTOCOL)) {
                rule->setEbProtocol((char *) xmlNodeGetContent(node));
                rule->setEbProtocolNeg(nodeNegation(node));

                /* source */
            } else if (!strcmp((char *) node->name, RulesXML::RULE_SOURCE)) {
                xmlNodePtr addrNode;
                for (addrNode = node->children; addrNode; addrNode = addrNode->next) {
                    if (!strcmp((char *) addrNode->name, RulesXML::RULE_ADDRESS)) {
                        rule->setEbSource((char *) xmlNodeGetContent(addrNode));
                    } else if (!strcmp((char *) addrNode->name, RulesXML::RULE_MASK)) {
                        rule->setEbSourceMask((char *) xmlNodeGetContent(addrNode));
                    }
                }
                /* attribute negation is for parent node */
                rule->setEbSourceNeg(nodeNegation(node));

                /* dest */
            } else if (!strcmp((char *) node->name, RulesXML::RULE_DEST)) {
                xmlNodePtr addrNode;
                for (addrNode = node->children; addrNode; addrNode = addrNode->next) {
                    if (!strcmp((char *) addrNode->name, RulesXML::RULE_ADDRESS)) {
                        rule->setEbDest((char *) xmlNodeGetContent(addrNode));
                    } else if (!strcmp((char *) addrNode->name, RulesXML::RULE_MASK)) {
                        rule->setEbDestMask((char *) xmlNodeGetContent(addrNode));
                    }
                }
                /* attribute negation is for parent node */
                rule->setEbDestNeg(nodeNegation(node));
            }
        }
    }

    /* iterate net node */
    if (netNode != NULL) {
        for (node = netNode->children; node; node = node->next) {
            /* skip non element nodes */
            if (node->type != XML_ELEMENT_NODE)
                continue;

            /* protocol */
            if (!strcmp((char *) node->name, RulesXML::RULE_PROTOCOL)) {
                rule->setIpProtocol((char *) xmlNodeGetContent(node));
                rule->setIpProtocolNeg(nodeNegation(node));

                /* source */
            } else if (!strcmp((char *) node->name, RulesXML::RULE_SOURCE)) {
                xmlNodePtr addrNode;
                for (addrNode = node->children; addrNode; addrNode = addrNode->next) {
                    if (!strcmp((char *) addrNode->name, RulesXML::RULE_ADDRESS)) {
                        rule->setIpSource((char *) xmlNodeGetContent(addrNode));
                    } else if (!strcmp((char *) addrNode->name, RulesXML::RULE_MASK)) {
                        rule->setIpSourceMask(atoi((char *) xmlNodeGetContent(addrNode)));
                    }
                }
                /* attribute negation is for parent node */
                rule->setIpSourceNeg(nodeNegation(node));

                /* dest */
            } else if (!strcmp((char *) node->name, RulesXML::RULE_DEST)) {
                xmlNodePtr addrNode;
                for (addrNode = node->children; addrNode; addrNode = addrNode->next) {
                    if (!strcmp((char *) addrNode->name, RulesXML::RULE_ADDRESS)) {
                        rule->setIpDest((char *) xmlNodeGetContent(addrNode));
                    } else if (!strcmp((char *) addrNode->name, RulesXML::RULE_MASK)) {
                        rule->setIpDestMask(atoi((char *) xmlNodeGetContent(addrNode)));
                    }
                }
                /* attribute negation is for parent node */
                rule->setIpDestNeg(nodeNegation(node));
            }
        }
    }
    Logger::getInstance()->debug(std::string("Parsed rule with name: ") + std::string(rule->getName().toAscii().data()));

    return rule;
}

bool RulesXML::nodeNegation(xmlNodePtr node) {
    xmlAttrPtr attr;

    /* iterate node attributes, search for negation */
    for (attr = node->properties; attr; attr = attr->next) {
        if (!strcmp((char *) attr->name, RulesXML::RULE_NEGATION)) {
            /* founded attribute negation return true */
            return true;
        }
    }

    /* nothing found */
    return false;
}

bool RulesXML::isLoadError() {
    return this->loadError;
}
