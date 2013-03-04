
#include <qt4/QtGui/qgridlayout.h>
#include <qt4/QtGui/qframe.h>
#include <qt4/QtGui/qlabel.h>
#include <qt4/QtGui/qdialogbuttonbox.h>
#include <qt4/QtCore/qnamespace.h>
#include <qt4/QtGui/qmessagebox.h>

#include "SettingsDialog.h"

SettingsDialog::SettingsDialog(QWidget* parent, Configuration *configuration) : QDialog(parent) {

    this->configuration = configuration;

    this->actions.append(FilterRule::ACTION_ACCEPT);
    this->actions.append(FilterRule::ACTION_DROP);

    /* make GUI object */
    if (this->objectName().isEmpty()) {
        this->setObjectName(QString::fromUtf8("SettingsDialog"));
    }
    this->setWindowTitle(QString::fromUtf8("Settings"));
    this->resize(400, 300);

    QFrame *appFrame = new QFrame(this);
    appFrame->setObjectName(QString::fromUtf8("debugFrame"));
    appFrame->setGeometry(QRect(10, 10, 380, 75));
    appFrame->setFrameShape(QFrame::StyledPanel);
    appFrame->setFrameShadow(QFrame::Raised);

    QGridLayout *appLayout = new QGridLayout(appFrame);
    appLayout->setObjectName("appLayout");
    appLayout->setContentsMargins(10, 10, 10, 10);

    QLabel *appLabel = new QLabel(appFrame);
    appLabel->setText(QString::fromUtf8("Application settings:"));
    appLayout->addWidget(appLabel, 0, 0, 1, 1);

    this->debugBox = new QCheckBox(appFrame);
    this->debugBox->setObjectName(QString::fromUtf8("debugBox"));
    this->debugBox->setText(QString::fromUtf8("Debug mode"));
    this->debugBox->setChecked(configuration->isDebugMode());
    appLayout->addWidget(this->debugBox, 1, 1, 1, 1);

    /* vertical spacer */
    QSpacerItem *appSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    appLayout->addItem(appSpacer, 2, 0, 1, 1);

    QFrame *chainsFrame = new QFrame(this);
    chainsFrame->setObjectName(QString::fromUtf8("chainsFrame"));
    chainsFrame->setGeometry(QRect(10, 105, 380, 150));
    chainsFrame->setFrameShape(QFrame::StyledPanel);
    chainsFrame->setFrameShadow(QFrame::Raised);

    QGridLayout *chainsLayout = new QGridLayout(chainsFrame);
    chainsLayout->setObjectName(QString::fromUtf8("chainsLayout"));
    chainsLayout->setContentsMargins(10, 10, 10, 10);

    QLabel *chainsLabel = new QLabel(chainsFrame);
    chainsLabel->setObjectName(QString::fromUtf8("chainsLabel"));
    chainsLabel->setText(QString::fromUtf8("Default actions:"));
    chainsLayout->addWidget(chainsLabel, 0, 0, 1, 1);

    QLabel *inputLabel = new QLabel(chainsFrame);
    inputLabel->setObjectName(QString::fromUtf8("inputLabel"));
    inputLabel->setText(QString::fromUtf8("INPUT: "));
    chainsLayout->addWidget(inputLabel, 1, 1, 1, 1);

    this->inputActionSelect = new QComboBox(chainsFrame);
    this->inputActionSelect->setObjectName(QString::fromUtf8("inputActionSelect"));
    this->inputActionSelect->addItems(this->actions);
    this->inputActionSelect->setCurrentIndex(actions.indexOf(configuration->getInputAction()));
    chainsLayout->addWidget(this->inputActionSelect, 1, 2, 1, 1);

    QLabel *forwardLabel = new QLabel(chainsFrame);
    forwardLabel->setObjectName(QString::fromUtf8("forwardLabel"));
    forwardLabel->setText(QString::fromUtf8("FORWARD: "));
    chainsLayout->addWidget(forwardLabel, 2, 1, 1, 1);

    this->forwardActionSelect = new QComboBox(chainsFrame);
    this->forwardActionSelect->setObjectName(QString::fromUtf8("forwardActionSelect"));
    this->forwardActionSelect->addItems(this->actions);
    this->forwardActionSelect->setCurrentIndex(actions.indexOf(configuration->getForwardAction()));
    chainsLayout->addWidget(this->forwardActionSelect, 2, 2, 1, 1);

    QLabel *outputLabel = new QLabel(chainsFrame);
    outputLabel->setObjectName(QString::fromUtf8("outputLabel"));
    outputLabel->setText(QString::fromUtf8("OUTPUT: "));
    chainsLayout->addWidget(outputLabel, 3, 1, 1, 1);

    this->outputActionSelect = new QComboBox(chainsFrame);
    this->outputActionSelect->setObjectName(QString::fromUtf8("outputActionSelect"));
    this->outputActionSelect->addItems(this->actions);
    this->outputActionSelect->setCurrentIndex(actions.indexOf(configuration->getOutputAction()));
    chainsLayout->addWidget(this->outputActionSelect, 3, 2, 1, 1);

    /* vertical spacer */
    QSpacerItem *chainsSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    chainsLayout->addItem(chainsSpacer, 4, 0, 1, 1);

    /* dialog buttons */
    this->buttons = new QDialogButtonBox(QDialogButtonBox::Cancel | QDialogButtonBox::Ok,
            Qt::Horizontal, this);
    this->buttons->setObjectName(QString::fromUtf8("buttons"));
    this->buttons->setGeometry(QRect(210, 260, 176, 27));
    connect(this->buttons, SIGNAL(accepted()), this, SLOT(accept()));
    connect(this->buttons, SIGNAL(rejected()), this, SLOT(reject()));
}

SettingsDialog::~SettingsDialog() {
}

void SettingsDialog::accept() {

    /* write changes to configuration */
    configuration->setDebugMode(debugBox->isChecked());
    configuration->setInputAction(inputActionSelect->currentText());
    configuration->setForwardAction(forwardActionSelect->currentText());
    configuration->setOutputAction(outputActionSelect->currentText());

    /* save configuration */
    if (!configuration->saveToXML()) {
        QMessageBox::critical(this, QString::fromUtf8("Saving error"),
                QString::fromUtf8("Error during saving configuration to XML file"), QMessageBox::Ok, QMessageBox::Ok);
    } else {

        QDialog::accept();
    }
}
