/* 
 * File:   FilterRule.cpp
 * Author: petris
 * 
 * Created on 28. listopad 2012, 17:26
 */

#include <qt4/QtCore/qdatastream.h>
#include <QString>
#include <qt4/QtCore/qbytearray.h>
#include <qt4/QtCore/qstring.h>

#include "FilterRule.h"

/* constant definitions */
const QString FilterRule::OPTION_VALUE_UNSPECIFIED = QString::fromUtf8("");
const int FilterRule::INT_VALUE_UNSPECIFIED = -1;

/* --- Constructors, destructor --- */
FilterRule::FilterRule() {
}

FilterRule::FilterRule(int number) {
    this->number = number;
}

FilterRule::~FilterRule() {
}

/* --- Other methods --- */

void FilterRule::toStream(QDataStream *stream) {

    *stream << this->number;
    *stream << this->name;
    *stream << this->action;
    *stream << this->description;
    
    *stream << this->inInterface;
    *stream << this->inInterfaceNeg;
    
    *stream << this->outInterface;
    *stream << this->outInterfaceNeg;
    
    *stream << this->ebProtocol;
    *stream << this->ebProtocolNeg;
    
    *stream << this->ebSource;
    *stream << this->ebSourceMask;
    *stream << this->ebSourceNeg;
    
    *stream << this->ebDest;
    *stream << this->ebDestMask;
    *stream << this->ebDestNeg;
    
    *stream << this->ipProtocol;
    *stream << this->ipProtocolNeg;
    
    *stream << this->ipSource;
    *stream << this->ipSourceMask;
    *stream << this->ipSourceNeg;
    
    *stream << this->ipDest;
    *stream << this->ipDestMask;
    *stream << this->ipDestNeg;
}

void FilterRule::fromStream(QDataStream *stream) {

    *stream >> this->number;
    *stream >> this->name;
    *stream >> this->action;
    *stream >> this->description;
    
    *stream >> this->inInterface;
    *stream >> this->inInterfaceNeg;
    
    *stream >> this->outInterface;
    *stream >> this->outInterfaceNeg;
    
    *stream >> this->ebProtocol;
    *stream >> this->ebProtocolNeg;
    
    *stream >> this->ebSource;
    *stream >> this->ebSourceMask;
    *stream >> this->ebSourceNeg;
    
    *stream >> this->ebDest;
    *stream >> this->ebDestMask;
    *stream >> this->ebDestNeg;
    
    *stream >> this->ipProtocol;
    *stream >> this->ipProtocolNeg;
    
    *stream >> this->ipSource;
    *stream >> this->ipSourceMask;
    *stream >> this->ipSourceNeg;
    
    *stream >> this->ipDest;
    *stream >> this->ipDestMask;
    *stream >> this->ipDestNeg;
}

QString FilterRule::toEbString() {
    QString out;

    /* append rule command */
    out.append(QString("%1 ").arg(EB_COMMAND_APPEND));

    /* chain */
    out.append(QString("%1 %2 ").arg(EB_COMMAND_CHAIN, EB_CHAIN));

    /* input interface if it is set */
    if (getInInterface() != FilterRule::OPTION_VALUE_UNSPECIFIED) {
        out.append(QString::fromUtf8(EB_COMMAND_INPUT_IFACE));
        if(isInInterfaceNeg())
                out.append(QString::fromUtf8(" %1").arg(EB_NEGATION));
        out.append(QString::fromUtf8(" %1 ").arg(getInInterface().toAscii().data()));
    }

    /* output interface if it is set */
    if (getOutInterface() != FilterRule::OPTION_VALUE_UNSPECIFIED) {
        out.append(QString::fromUtf8(EB_COMMAND_OUTPUT_IFACE));
        if(isOutInterfaceNeg())
            out.append(QString::fromUtf8(" %1").arg(EB_NEGATION));
        out.append(QString::fromUtf8(" %1 ").arg(getOutInterface().toAscii().data()));
    }
    /* link protocol */
    if (getEbProtocol() != FilterRule::OPTION_VALUE_UNSPECIFIED) {
        out.append(QString::fromUtf8(EB_COMMAND_PROTOCOL));
        if(isEbProtocolNeg())
            out.append(QString::fromUtf8(" %1").arg(EB_NEGATION));
        out.append((QString::fromUtf8(" %1 ").arg(getEbProtocol().toAscii().data())));
    }

    /* source link address */
    if (!getEbSource().isEmpty()) {
        out.append(QString::fromUtf8(EB_COMMAND_SOURCE_ADDR));
        if(isEbSourceNeg())
            out.append(QString::fromUtf8(" %1").arg(EB_NEGATION));
        out.append(QString::fromUtf8(" %1").arg(getEbSource().toAscii().data()));
        
        /* mask */
        if(!getEbSourceMask().isEmpty()) {
            out.append(QString::fromUtf8("%1%2").arg(EB_MASK_DELIMITER, getEbSourceMask().toAscii().data()));
        }
        
        /* finally append space*/
        out.append(QString::fromUtf8(" "));
    }

    /* destination link address */
    if (!getEbDest().isEmpty()) {
        out.append(QString::fromUtf8(EB_COMMAND_DEST_ADDR));
        if(isEbDestNeg())
            out.append(QString::fromUtf8(" %1").arg(EB_NEGATION));
        out.append(QString::fromUtf8(" %1").arg(getEbDest().toAscii().data()));
        
        /* mask */
        if(!getEbDestMask().isEmpty()) {
            out.append(QString::fromUtf8("%1%2").arg(EB_MASK_DELIMITER, getEbDestMask().toAscii().data()));
        }
        
        /* finally append space*/
        out.append(QString::fromUtf8(" "));
    }

    /* action */
    if (!getAction().isEmpty())
        out.append(QString("%1 %2 ").arg(EB_COMMAND_ACTION, getAction().toAscii().data()));

    /* finally line end */
    out.append(QString::fromUtf8("\n"));

    return out;
}

QString FilterRule::toIpString() {
    QString out;

    /* append rule command */
    out.append(QString("%1 ").arg(IP_COMMAND_APPEND));

    /* chain */
    out.append(QString("%1 %2 ").arg(IP_COMMAND_CHAIN, IP_CHAIN));

    /* input interface if it is set */
    if (getInInterface() != FilterRule::OPTION_VALUE_UNSPECIFIED) {
        if(isInInterfaceNeg())
                out.append(QString::fromUtf8("%1 ").arg(IP_NEGATION));
        out.append(QString::fromUtf8(IP_COMMAND_INPUT_IFACE));
        out.append(QString::fromUtf8(" %1 ").arg(getInInterface().toAscii().data()));
    }

    /* output interface if it is set */
    if (getOutInterface() != FilterRule::OPTION_VALUE_UNSPECIFIED) {
        if(isOutInterfaceNeg())
            out.append(QString::fromUtf8("%1 ").arg(IP_NEGATION));
        out.append(QString::fromUtf8(IP_COMMAND_OUTPUT_IFACE));
        out.append(QString::fromUtf8(" %1 ").arg(getOutInterface().toAscii().data()));
    }
    /* protocol */
    if (getIpProtocol() != FilterRule::OPTION_VALUE_UNSPECIFIED) {
        if(isIpProtocolNeg())
            out.append(QString::fromUtf8("%1 ").arg(IP_NEGATION));
        out.append(QString::fromUtf8(IP_COMMAND_PROTOCOL));
        out.append((QString::fromUtf8(" %1 ").arg(getIpProtocol().toAscii().data())));
    }

    /* source net address */
    if (!getIpSource().isEmpty()) {
        if(isIpSourceNeg())
            out.append(QString::fromUtf8("%1 ").arg(IP_NEGATION));
        out.append(QString::fromUtf8(IP_COMMAND_SOURCE_ADDR));
        out.append(QString::fromUtf8(" %1").arg(getIpSource().toAscii().data()));
        
        /* mask */
        if(getIpSourceMask() != FilterRule::INT_VALUE_UNSPECIFIED) {
            out.append(QString::fromUtf8("%1%2").arg(IP_MASK_DELIMITER, QString::number(getIpSourceMask())));
        }
        
        /* finally append space*/
        out.append(QString::fromUtf8(" "));
    }

    /* destination link address */
    if (!getIpDest().isEmpty()) {
        if(isIpDestNeg())
            out.append(QString::fromUtf8("%1 ").arg(IP_NEGATION));
        out.append(QString::fromUtf8(IP_COMMAND_DEST_ADDR));
        out.append(QString::fromUtf8(" %1").arg(getIpDest().toAscii().data()));
        
        /* mask */
        if(getIpDestMask() != FilterRule::INT_VALUE_UNSPECIFIED) {
            out.append(QString::fromUtf8("%1%2").arg(IP_MASK_DELIMITER, QString::number(getIpDestMask())));
        }
        
        /* finally append space*/
        out.append(QString::fromUtf8(" "));
    }

    /* action */
    if (!getAction().isEmpty())
        out.append(QString("%1 %2 ").arg(IP_COMMAND_ACTION, getAction().toAscii().data()));

    /* finally line end */
    out.append(QString::fromUtf8("\n"));

    return out;
}

/* --- Getters and setters --- */

void FilterRule::setNumber(int number) {
    this->number = number;
}

int FilterRule::getNumber() const {
    return this->number;
}

void FilterRule::setName(QString name) {
    this->name = name;
}

QString FilterRule::getName() const {
    return this->name;
}

QString FilterRule::getAction() const {
    return this->action;
}

void FilterRule::setAction(QString action) {
    this->action = action;
}

QString FilterRule::getDescription() const {
    return this->description;
}

void FilterRule::setDescription(QString description) {
    this->description = description;
}

QString FilterRule::getEbDest() const {
    return this->ebDest;
}

void FilterRule::setEbDest(QString EbDest) {
    this->ebDest = EbDest;
}

QString FilterRule::getEbDestMask() const {
    return ebDestMask;
}

void FilterRule::setEbDestMask(QString ebDestMask) {
    this->ebDestMask = ebDestMask;
}

bool FilterRule::isEbDestNeg() const {
    return ebDestNeg;
}

void FilterRule::setEbDestNeg(bool ebDestNeg) {
    this->ebDestNeg = ebDestNeg;
}

QString FilterRule::getEbSource() const {
    return this->ebSource;
}

void FilterRule::setEbSource(QString EbSource) {
    this->ebSource = EbSource;
}

QString FilterRule::getEbSourceMask() const {
    return ebSourceMask;
}

void FilterRule::setEbSourceMask(QString ebSourceMask) {
    this->ebSourceMask = ebSourceMask;
}

bool FilterRule::isEbSourceNeg() const {
    return ebSourceNeg;
}

void FilterRule::setEbSourceNeg(bool ebSourceNeg) {
    this->ebSourceNeg = ebSourceNeg;
}

QString FilterRule::getInInterface() const {
    return this->inInterface;
}

void FilterRule::setInInterface(QString inInterface) {
    this->inInterface = inInterface;
}

bool FilterRule::isInInterfaceNeg() const {
    return inInterfaceNeg;
}

void FilterRule::setInInterfaceNeg(bool inInterfaceNeg) {
    this->inInterfaceNeg = inInterfaceNeg;
}

QString FilterRule::getOutInterface() const {
    return this->outInterface;
}

void FilterRule::setOutInterface(QString outInterface) {
    this->outInterface = outInterface;
}

bool FilterRule::isOutInterfaceNeg() const {
    return outInterfaceNeg;
}

void FilterRule::setOutInterfaceNeg(bool outInterfaceNeg) {
    this->outInterfaceNeg = outInterfaceNeg;
}

QString FilterRule::getEbProtocol() const {
    return ebProtocol;
}

void FilterRule::setEbProtocol(QString ebProtocol) {
    this->ebProtocol = ebProtocol;
}

bool FilterRule::isEbProtocolNeg() const {
    return ebProtocolNeg;
}

void FilterRule::setEbProtocolNeg(bool ebProtocolNeg) {
    this->ebProtocolNeg = ebProtocolNeg;
}

QString FilterRule::getIpDest() const {
    return ipDest;
}

void FilterRule::setIpDest(QString ipDest) {
    this->ipDest = ipDest;
}

short FilterRule::getIpDestMask() const {
    return ipDestMask;
}

void FilterRule::setIpDestMask(short ipDestMask) {
    this->ipDestMask = ipDestMask;
}

bool FilterRule::isIpDestNeg() const {
    return ipDestNeg;
}

void FilterRule::setIpDestNeg(bool ipDestNeg) {
    this->ipDestNeg = ipDestNeg;
}

bool FilterRule::isIpFragment() const {
    return ipFragment;
}

void FilterRule::setIpFragment(bool ipFragment) {
    this->ipFragment = ipFragment;
}

QString FilterRule::getIpProtocol() const {
    return ipProtocol;
}

void FilterRule::setIpProtocol(QString ipProtocol) {
    this->ipProtocol = ipProtocol;
}

bool FilterRule::isIpProtocolNeg() const {
    return ipProtocolNeg;
}

void FilterRule::setIpProtocolNeg(bool ipProtocolNeg) {
    this->ipProtocolNeg = ipProtocolNeg;
}

QString FilterRule::getIpSource() const {
    return ipSource;
}

void FilterRule::setIpSource(QString ipSource) {
    this->ipSource = ipSource;
}

bool FilterRule::isIpSourceNeg() const {
    return ipSourceNeg;
}

void FilterRule::setIpSourceNeg(bool ipSourceNeg) {
    this->ipSourceNeg = ipSourceNeg;
}

short FilterRule::getIpSourceMask() const {
    return ipSourceMask;
}

void FilterRule::setIpSourceMask(short ipSourceMask) {
    this->ipSourceMask = ipSourceMask;
}

