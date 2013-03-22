
#include "NegationComboBox.h"

const int NegationComboBox::NORMAL_INDEX = 0;
const int NegationComboBox::NEGATION_INDEX = 1;

NegationComboBox::NegationComboBox(QWidget *parent) : QComboBox(parent) {
}

NegationComboBox::~NegationComboBox() {
}

void NegationComboBox::checkForDisable(QString optionValue) {
    if (optionValue == disableOption) {

        if (isEnabled()) {
            setEnabled(false);
            setCurrentIndex(NORMAL_INDEX);
        }
    } else {

        if (!isEnabled()) {
            setEnabled(true);
        }
    }
}

void NegationComboBox::setDisableOption(QString disableOption) {
    this->disableOption = disableOption;
}