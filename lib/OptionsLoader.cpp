
#include "OptionsLoader.h"

const QString OptionsLoader::NET_PROTOCOLS_OPTIONS = QString::fromUtf8("data/netProtocols");
const QString OptionsLoader::LINK_PROTOCOLS_OPTIONS = QString::fromUtf8("data/linkProtocols");

OptionsLoader::OptionsLoader(QString file) {
    
    this->file = file;
    loadOptions();
}

QStringList OptionsLoader::getOptions() {
    return this->options;
}

void OptionsLoader::loadOptions() {
    
    ifstream file;
    string line;
    
    file.open(this->file.toAscii().data(), ifstream::in);
    
    while(!file.eof() && file.good()) {
        
        file >> line;
        this->options.append(QString::fromStdString(line));
    }
}


