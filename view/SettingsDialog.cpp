
#include <qt4/QtGui/qgridlayout.h>
#include <qt4/QtGui/qframe.h>
#include <qt4/QtGui/qlabel.h>

#include "SettingsDialog.h"

SettingsDialog::SettingsDialog(QWidget* parent) : QDialog(parent) {
    
    if(this->objectName().isEmpty()) {
        this->setObjectName(QString::fromUtf8("SettingsDialog"));
    }
    this->setWindowTitle(QString::fromUtf8("Settings"));
    this->resize(400, 300);
    
    QFrame *chainsFrame = new QFrame(this); 
    chainsFrame->setObjectName(QString::fromUtf8("chainsFrame"));
    chainsFrame->setGeometry(QRect(10, 10, 380, 125));
    chainsFrame->setFrameShape(QFrame::StyledPanel);
    chainsFrame->setFrameShadow(QFrame::Raised);
    
    QGridLayout *layout = new QGridLayout(chainsFrame);
    layout->setObjectName("settingsLayout");
    layout->setContentsMargins(10, 10, 10, 10);
    
    QLabel *chainsLabel = new QLabel(this);
    chainsLabel->setObjectName(QString::fromUtf8("chainsLabel"));
    chainsLabel->setText(QString::fromUtf8("Select affected netfilter chains:"));
    layout->addWidget(chainsLabel, 0, 0, 1, 1);
    
    this->chainInputBox = new QCheckBox(this);
    this->chainInputBox->setObjectName(QString::fromUtf8("chainInputBox"));
    this->chainInputBox->setText(RulesPusher::NF_CHAIN_INPUT);
    layout->addWidget(this->chainInputBox, 1, 1, 1, 1);
    
    this->chainForwardBox = new QCheckBox(this);
    this->chainForwardBox->setObjectName(QString::fromUtf8("chainFilterBox"));
    this->chainForwardBox->setText(RulesPusher::NF_CHAIN_FORWARD);
    layout->addWidget(this->chainForwardBox, 2, 1, 1, 1);
    
    this->chainOutputBox = new QCheckBox(this);
    this->chainOutputBox->setObjectName(QString::fromUtf8("chainOutputBox"));
    this->chainOutputBox->setText(RulesPusher::NF_CHAIN_OUTPUT);
    layout->addWidget(this->chainOutputBox, 3, 1, 1, 1);
    
    /* vertical spacer */
    QSpacerItem *verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    layout->addItem(verticalSpacer, 4, 1, 1, 1);
}

SettingsDialog::~SettingsDialog() {
}

