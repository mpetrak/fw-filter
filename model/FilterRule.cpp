/* 
 * File:   FilterRule.cpp
 * Author: petris
 * 
 * Created on 28. listopad 2012, 17:26
 */

#include "FilterRule.h"

FilterRule::FilterRule(int number) {
    this->number = number;
}

FilterRule::~FilterRule() {
}

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

