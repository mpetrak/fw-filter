
#include "Configuration.h"

const char* Configuration::XML_FILE = "data/conf.xml";
const char* Configuration::XML_VERSION = "1.0";
const char* Configuration::XML_ENCODING = "UTF-8";

const char* Configuration::NODE_ROOT = "configuration";
const char* Configuration::NODE_DEBUG = "debug";
const char* Configuration::NODE_DEFAULT_ACTION = "default_action";

Configuration::Configuration() {
    setDebugMode(true);
    setDefaultAction(FilterRule::ACTION_ACCEPT);
}

Configuration::~Configuration() {
}

bool Configuration::saveToXML() {
    xmlNodePtr rootNode;
    xmlDocPtr doc;

    Logger::getInstance()->debug(std::string("Saving configuration to file: ") + std::string(XML_FILE));
    rootNode = xmlNewNode(NULL, BAD_CAST NODE_ROOT);

    if (this->debugMode)
        xmlNewChild(rootNode, NULL, BAD_CAST NODE_DEBUG, NULL);

    xmlNewChild(rootNode, NULL, BAD_CAST NODE_DEFAULT_ACTION, BAD_CAST defaultAction.toAscii().data());

    doc = xmlNewDoc(BAD_CAST XML_VERSION);
    xmlDocSetRootElement(doc, rootNode);

    int result = xmlSaveFormatFileEnc(XML_FILE, doc, XML_ENCODING, 1);

    if (result < 0) {
        Logger::getInstance()->debug("Configuration saving failed");
        return false;
    } else {
        Logger::getInstance()->debug("Configuration successfully saved");
        return true;
    }
}

bool Configuration::loadFromXML() {
    xmlDocPtr doc;
    xmlNodePtr rootNode, node;

    Logger::getInstance()->debug(std::string("Loading configuration from file: ") + std::string(XML_FILE));
    doc = xmlReadFile(XML_FILE, XML_ENCODING, 0);

    if (doc == NULL) {
        Logger::getInstance()->debug("Error reading configuration XML file");
        return false;
    } else {

        rootNode = xmlDocGetRootElement(doc);
        bool debugMode = false;
        for (node = rootNode->children; node; node = node->next) {
            /* skip not XML elements */
            if (node->type != XML_ELEMENT_NODE)
                continue;

            if (!strcmp((char *) node->name, NODE_DEBUG)) {
                debugMode = true;

            } else if (!strcmp((char *) node->name, NODE_DEFAULT_ACTION)) {
                this->defaultAction = (char *) xmlNodeGetContent(node);
            }
        }

        this->debugMode = debugMode;

        xmlFreeDoc(doc);
        xmlCleanupParser();

        Logger::getInstance()->debug("Configuration successfully loaded");
        return true;
    }
}

bool Configuration::isDebugMode() const {
    return debugMode;
}

void Configuration::setDebugMode(bool debugMode) {
    this->debugMode = debugMode;
}

QString Configuration::getDefaultAction() const {
    return defaultAction;
}

void Configuration::setDefaultAction(QString defaultAction) {
    this->defaultAction = defaultAction;
}
