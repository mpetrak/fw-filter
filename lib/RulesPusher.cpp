
#include <QString>
#include <QByteArray>
#include <stdlib.h>

#include "RulesPusher.h"

RulesPusher::RulesPusher() {
}

RulesPusher::~RulesPusher() {
}

bool RulesPusher::writeRules(QList<FilterRule> rules) {    
    ebFile.open(EB_OUTPUT_FILE, fstream::out);
    ipFile.open(IP_OUTPUT_FILE, fstream::out);
    
    ebFile << this->ebFileHeader().toAscii().data();
    ipFile << this->ipFileHeader().toAscii().data();
    
    /* iterate each rule and write ebtables string */
    FilterRule rule;
    foreach(rule, rules) {
        ebFile << rule.toEbString().toAscii().data();
        ipFile << rule.toIpString().toAscii().data();
    }
    
    ebFile << this->ebFileFooter().toAscii().data();
    ipFile << this->ipFileFooter().toAscii().data();
    
    ebFile.close();
    ipFile.close();
    
    system(QString(EB_COMMAND).arg(EB_OUTPUT_FILE).toAscii().data());
    system(QString(IP_COMMAND).arg(IP_OUTPUT_FILE).toAscii().data());
    
    return true;
}

QString RulesPusher::ebFileHeader() {
    QString header;
    header = QString::fromUtf8("# Generated by fw-filter\n");
    header.append(QString::fromUtf8("*filter\n"));
    header.append(QString::fromUtf8(":INPUT ACCEPT\n"));
    header.append(QString::fromUtf8(":FORWARD ACCEPT\n"));
    header.append(QString::fromUtf8(":OUTPUT ACCEPT\n"));
    
    return header;
}

QString RulesPusher::ipFileHeader() {
    QString header;
    header = QString::fromUtf8("# Generated by fw-filter\n");
    header.append(QString::fromUtf8("*filter\n"));
    header.append(QString::fromUtf8(":INPUT ACCEPT [0:0]\n"));
    header.append(QString::fromUtf8(":FORWARD ACCEPT [0:0]\n"));
    header.append(QString::fromUtf8(":OUTPUT ACCEPT [0:0]\n"));
    
    return header;
}

QString RulesPusher::ipFileFooter() {
    QString footer;
    footer.append(QString::fromUtf8("COMMIT\n"));
    
    return footer;
}

QString RulesPusher::ebFileFooter() {
    QString footer;
    
    return footer;
}
