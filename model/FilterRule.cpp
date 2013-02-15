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
    if (getInInterface().length() > 0)
        out.append(QString("%1 %2 ").arg(EB_COMMAND_INPUT_IFACE, getInInterface().toAscii().data()));

    /* output interface if it is set */
    if (getOutInterface().length() > 0)
        out.append(QString("%1 %2 ").arg(EB_COMMAND_OUTPUT_IFACE, getOutInterface().toAscii().data()));

    /* link protocol */
    if (getEbProtocol().length() > 0)
        out.append((QString("%1 %2 ").arg(EB_COMMAND_PROTOCOL, getEbProtocol().toAscii().data())));

    /* source link address */
    if (getEbSource().length() > 0)
        out.append(QString("%1 %2 ").arg(EB_COMMAND_SOURCE_ADDR, getEbSource().toAscii().data()));

    /* destination link address */
    if (getEbDest().length() > 0)
        out.append(QString("%1 %2 ").arg(EB_COMMAND_DEST_ADDR, getEbDest().toAscii().data()));

    /* action */
    if (getAction().length() > 0)
        out.append(QString("%1 %2 ").arg(EB_COMMAND_ACTION, getAction().toAscii().data()));

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

ushort FilterRule::getIpDestMask() const {
    return ipDestMask;
}

void FilterRule::setIpDestMask(ushort ipDestMask) {
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

ushort FilterRule::getIpSourceMask() const {
    return ipSourceMask;
}

void FilterRule::setIpSourceMask(ushort ipSourceMask) {
    this->ipSourceMask = ipSourceMask;
}

