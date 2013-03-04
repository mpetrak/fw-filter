
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
    static const char* NODE_INPUT_ACTION;
    static const char* NODE_FORWARD_ACTION;
    static const char* NODE_OUTPUT_ACTION;

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
    QString getForwardAction() const;
    void setForwardAction(QString forwardAction);
    QString getInputAction() const;
    void setInputAction(QString inputAction);
    QString getOutputAction() const;
    void setOutputAction(QString outputAction);

private:

    bool debugMode;

    QString inputAction;
    QString forwardAction;
    QString outputAction;

};

#endif	/* CONFIGURATION_H */

