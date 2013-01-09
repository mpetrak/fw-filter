/* 
 * File:   FilterRule.cpp
 * Author: petris
 * 
 * Created on 28. listopad 2012, 17:26
 */

#include <qt4/QtCore/qdatastream.h>

#include "FilterRule.h"

/* --- Constructors, destructor --- */

FilterRule::FilterRule() {}

FilterRule::FilterRule(int number) {
    this->number = number;
}

FilterRule::~FilterRule() {
}

/* --- Other methods --- */

void FilterRule::toStream(QDataStream *stream) {
    
    *stream << this->number;
    *stream << this->name;
}

void FilterRule::fromStream(QDataStream *stream) {
    
    *stream >> number;
    *stream >> name;
}

/* --- Getters and setters --- */

void FilterRule::setNumber(int number) {
    this->number = number;
}

int FilterRule::getNumber() {
    return this->number;
}

void FilterRule::setName(QString name) {
    this->name = name;
}

QString FilterRule::getName() {
    return this->name;
}

