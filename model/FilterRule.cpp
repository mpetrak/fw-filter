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
    *stream << this->outInterface;
    *stream << this->ebProtocol;
    *stream << this->ebSource;
    *stream << this->ebSourceMask;
    *stream << this->ebDest;
    *stream << this->ebDestMask;
    *stream << this->ipProtocol;
    *stream << this->ipSource;
    *stream << this->ipSourceMask;
    *stream << this->ipDest;
    *stream << this->ipDestMask;
}

void FilterRule::fromStream(QDataStream *stream) {

    *stream >> this->number;
    *stream >> this->name;
    *stream >> this->action;
    *stream >> this->description;
    *stream >> this->inInterface;
    *stream >> this->outInterface;
    *stream >> this->ebProtocol;
    *stream >> this->ebSource;
    *stream >> this->ebSourceMask;
    *stream >> this->ebDest;
    *stream >> this->ebDestMask;
    *stream >> this->ipProtocol;
    *stream >> this->ipSource;
    *stream >> this->ipSourceMask;
    *stream >> this->ipDest;
    *stream >> this->ipDestMask;
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

QString FilterRule::getInInterface() const {
    return this->inInterface;
}

void FilterRule::setInInterface(QString inInterface) {
    this->inInterface = inInterface;
}

QString FilterRule::getOutInterface() const {
    return this->outInterface;
}

void FilterRule::setOutInterface(QString outInterface) {
    this->outInterface = outInterface;
}

QString FilterRule::getEbProtocol() const {
    return ebProtocol;
}

void FilterRule::setEbProtocol(QString ebProtocol) {
    this->ebProtocol = ebProtocol;
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

QString FilterRule::getIpSource() const {
    return ipSource;
}

void FilterRule::setIpSource(QString ipSource) {
    this->ipSource = ipSource;
}

ushort FilterRule::getIpSourceMask() const {
    return ipSourceMask;
}

void FilterRule::setIpSourceMask(ushort ipSourceMask) {
    this->ipSourceMask = ipSourceMask;
}

