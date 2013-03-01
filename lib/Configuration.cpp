
#include "Configuration.h"

Configuration::Configuration() {
    setDebugMode(true);
}

Configuration::~Configuration() {
}

bool Configuration::isDebugMode() const {
    return debugMode;
}

void Configuration::setDebugMode(bool debugMode) {
    this->debugMode = debugMode;
}