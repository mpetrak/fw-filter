
#include "Configuration.h"

Configuration::Configuration() {
    setDebugMode(true);
    setInputAction(FilterRule::ACTION_ACCEPT);
    setForwardAction(FilterRule::ACTION_ACCEPT);
    setOutputAction(FilterRule::ACTION_ACCEPT);
}

Configuration::~Configuration() {
}

bool Configuration::isDebugMode() const {
    return debugMode;
}

void Configuration::setDebugMode(bool debugMode) {
    this->debugMode = debugMode;
}

QString Configuration::getForwardAction() const {
    return forwardAction;
}

void Configuration::setForwardAction(QString forwardAction) {
    this->forwardAction = forwardAction;
}

QString Configuration::getInputAction() const {
    return inputAction;
}

void Configuration::setInputAction(QString inputAction) {
    this->inputAction = inputAction;
}

QString Configuration::getOutputAction() const {
    return outputAction;
}

void Configuration::setOutputAction(QString outputAction) {
    this->outputAction = outputAction;
}