
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
    
    QFrame *appFrame = new QFrame(this); 
    appFrame->setObjectName(QString::fromUtf8("debugFrame"));
    appFrame->setGeometry(QRect(10, 10, 380, 75));
    appFrame->setFrameShape(QFrame::StyledPanel);
    appFrame->setFrameShadow(QFrame::Raised);
    
    QGridLayout *layout = new QGridLayout(appFrame);
    layout->setObjectName("settingsLayout");
    layout->setContentsMargins(10, 10, 10, 10);
    
    QLabel *appLabel = new QLabel(this);
    appLabel->setText(QString::fromUtf8("Application settings:"));
    layout->addWidget(appLabel, 0, 0, 1, 1);
    
    this->debugBox = new QCheckBox(this);
    this->debugBox->setObjectName(QString::fromUtf8("debugBox"));
    this->debugBox->setText(QString::fromUtf8("Debug mode"));
    layout->addWidget(this->debugBox, 1, 1, 1, 1);

    /* vertical spacer */
    QSpacerItem *verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    layout->addItem(verticalSpacer, 2, 0, 1, 1);
}

SettingsDialog::~SettingsDialog() {
    free(this->debugBox);
}

