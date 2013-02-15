
#ifndef OPTIONSLOADER_H
#define	OPTIONSLOADER_H

#include <iostream>
#include <fstream>

#include <QStringList>

using namespace std;

class OptionsLoader {
public:
    /** File with options for net layer protocols */
    static const QString NET_PROTOCOLS_OPTIONS;
    /** File with options for lin layer protocols */
    static const QString LINK_PROTOCOLS_OPTIONS;
    
    /**
     * Class constructor with path to options file
     * @param file path to options file
     */
    OptionsLoader(QString file);
    
    /**
     * Get loaded options in a list.
     * @return loaded options
     */
    QStringList getOptions();
private:
    /**
     * Load options from file and save them to a list.
     */
    void loadOptions();
    
    /** Path to file */
    QString file;
    /** Loaded options */
    QStringList options;
    
};

#endif	/* OPTIONSLOADER_H */

