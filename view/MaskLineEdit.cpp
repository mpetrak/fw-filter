#include "MaskLineEdit.h"

MaskLineEdit::MaskLineEdit(QWidget *parent) : QLineEdit(parent) {
    setDisableValue("");
}

MaskLineEdit::~MaskLineEdit() {
}

void MaskLineEdit::checkForDisable(QString addrValue) {
    if (addrValue == disableValue) {
        if (isEnabled()) {
            setEnabled(false);
            clear();
        }
    } else {

        if (!isEnabled()) {
            setEnabled(true);
        }
    }
}

void MaskLineEdit::setDisableValue(QString disableValue) {
    this->disableValue = disableValue;
}