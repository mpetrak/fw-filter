
#ifndef CONFIGURATION_H
#define	CONFIGURATION_H

class Configuration {
public:
    Configuration();
    virtual ~Configuration();
    
    bool isDebugMode() const;
    void setDebugMode(bool debugMode);
private:
    
    bool debugMode;

};

#endif	/* CONFIGURATION_H */

