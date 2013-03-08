
#include <qt4/QtGui/qboxlayout.h>

#include "NfOutputDialog.h"

NfOutputDialog::NfOutputDialog(QWidget *parent, QString nfOutput) : QDialog(parent) {

    if (this->objectName().isEmpty()) {
        this->setObjectName(QString::fromUtf8("NfOutputDialog"));
    }
    this->setWindowTitle(QString::fromUtf8("Netfilter output"));
    this->resize(800, 600);

    QVBoxLayout *layout = new QVBoxLayout(this);

    /* text view */
    view = new QTextEdit(this);
    view->setReadOnly(true);
    view->setText(nfOutput);
    layout->addWidget(view);

    /* dialog buttons */
    buttons = new QDialogButtonBox(QDialogButtonBox::Ok, Qt::Horizontal, this);
    buttons->setObjectName(QString::fromUtf8("buttons"));
    layout->addWidget(buttons);
    connect(this->buttons, SIGNAL(accepted()), this, SLOT(accept()));
}

NfOutputDialog::~NfOutputDialog() {
}