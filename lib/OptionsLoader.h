
#ifndef OPTIONSLOADER_H
#define	OPTIONSLOADER_H

#include <iostream>
#include <fstream>

#include <QStringList>

using namespace std;

class OptionsLoader {
public:
    static const QString NET_PROTOCOLS_OPTIONS;
    static const QString LINK_PROTOCOLS_OPTIONS;
    
    OptionsLoader(QString file);
    
    QStringList getOptions();
private:
    void loadOptions();
    
    QString file;
    QStringList options;
    
};

#endif	/* OPTIONSLOADER_H */

