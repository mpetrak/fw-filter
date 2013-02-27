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

    setNumber(0);
    setName("New rule");
    setDescription("Insert description");
    setChainInput(true);
    setChainForward(true);
    setChainOutput(true);
    setAction("DROP");
    setInInterface(FilterRule::OPTION_VALUE_UNSPECIFIED);
    setInInterfaceNeg(false);
    setOutInterface(FilterRule::OPTION_VALUE_UNSPECIFIED);
    setOutInterfaceNeg(false);
    setEbProtocol(FilterRule::OPTION_VALUE_UNSPECIFIED);
    setEbProtocolNeg(false);
    setEbDest("");
    setEbDestMask("");
    setEbDestNeg(false);
    setEbSource("");
    setEbSourceMask("");
    setEbSourceNeg(false);
    setIpProtocol(FilterRule::OPTION_VALUE_UNSPECIFIED);
    setIpProtocolNeg(false);
    setIpSource("");
    setIpSourceMask(FilterRule::INT_VALUE_UNSPECIFIED);
    setIpSourceNeg(false);
    setIpDest("");
    setIpDestMask(FilterRule::INT_VALUE_UNSPECIFIED);
    setIpDestNeg(false);
    setIpFragment(false);
}

FilterRule::FilterRule(FilterRule* copy) {
    setNumber(copy->getNumber());
    setName(QString::fromUtf8("%1 copy").arg(copy->getName()));
    setDescription(copy->getDescription());
    setChainInput(copy->isChainInput());
    setChainForward(copy->isChainForward());
    setChainOutput(copy->isChainOutput());
    setAction(copy->getAction());
    setInInterface(copy->getInInterface());
    setInInterfaceNeg(copy->isInInterfaceNeg());
    setOutInterface(copy->getOutInterface());
    setOutInterfaceNeg(copy->isOutInterfaceNeg());
    setEbProtocol(copy->getEbProtocol());
    setEbProtocolNeg(copy->isEbProtocolNeg());
    setEbDest(copy->getEbDest());
    setEbDestMask(copy->getEbDestMask());
    setEbDestNeg(copy->isEbDestNeg());
    setEbSource(copy->getEbSource());
    setEbSourceMask(copy->getEbSourceMask());
    setEbSourceNeg(copy->isEbSourceNeg());
    setIpProtocol(copy->getIpProtocol());
    setIpProtocolNeg(copy->isIpProtocolNeg());
    setIpSource(copy->getIpSource());
    setIpSourceMask(copy->getIpSourceMask());
    setIpSourceNeg(copy->isIpSourceNeg());
    setIpDest(copy->getIpDest());
    setIpDestMask(copy->getIpDestMask());
    setIpDestNeg(copy->isIpDestNeg());
    setIpFragment(copy->isIpFragment());
}

FilterRule::~FilterRule() {
}

/* --- Other methods --- */

void FilterRule::toStream(QDataStream *stream) {

    *stream << this->number;
    *stream << this->name;
    *stream << this->description;
    *stream << this->chainInput;
    *stream << this->chainForward;
    *stream << this->chainOutput;
    *stream << this->action;

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
    *stream >> this->description;
    *stream >> this->chainInput;
    *stream >> this->chainForward;
    *stream >> this->chainOutput;
    *stream >> this->action;

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

bool FilterRule::isChainForward() const {
    return chainForward;
}

void FilterRule::setChainForward(bool chainForward) {
    this->chainForward = chainForward;
}

bool FilterRule::isChainInput() const {
    return chainInput;
}

void FilterRule::setChainInput(bool chainInput) {
    this->chainInput = chainInput;
}

bool FilterRule::isChainOutput() const {
    return chainOutput;
}

void FilterRule::setChainOutput(bool chainOutput) {
    this->chainOutput = chainOutput;
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

