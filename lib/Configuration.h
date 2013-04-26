
#ifndef CONFIGURATION_H
#define	CONFIGURATION_H

#include <QString>
#include <libxml/tree.h>
#include <libxml/parser.h>

#include "../model/FilterRule.h"
#include "Logger.h"

class Configuration {
public:
    /* constants */
    static const char* XML_FILE;
    static const char* XML_VERSION;
    static const char* XML_ENCODING;
    static const char* NODE_ROOT;
    static const char* NODE_DEBUG;
    static const char* NODE_DEFAULT_ACTION;

    Configuration();
    virtual ~Configuration();

    /**
     * Save configuration to XML file.
     * @return true on success / false on error
     */
    bool saveToXML();

    /**
     * Load configuration from XML file.
     * @return true on success / false on error
     */
    bool loadFromXML();

    /* getters and setters */
    bool isDebugMode() const;
    void setDebugMode(bool debugMode);
    QString getDefaultAction() const;
    void setDefaultAction(QString defaultAction);

private:

    /** debug mode */
    bool debugMode;

    /** default action */
    QString defaultAction;
};

#endif	/* CONFIGURATION_H */

