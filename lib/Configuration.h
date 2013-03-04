
#ifndef CONFIGURATION_H
#define	CONFIGURATION_H

#include <QString>

#include "../model/FilterRule.h"

class Configuration {
public:
    Configuration();
    virtual ~Configuration();
    
    bool isDebugMode() const;
    void setDebugMode(bool debugMode);
    QString getForwardAction() const ;
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

