
#include <qt4/QtGui/qgridlayout.h>
#include <qt4/QtGui/qframe.h>
#include <qt4/QtGui/qlabel.h>
#include <qt4/QtGui/qdialogbuttonbox.h>
#include <qt4/QtCore/qnamespace.h>

#include "SettingsDialog.h"

SettingsDialog::SettingsDialog(QWidget* parent, Configuration *configuration) : QDialog(parent) {

    this->configuration = configuration;

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

    QGridLayout *layout = new QGridLayout(appFrame);
    layout->setObjectName("settingsLayout");
    layout->setContentsMargins(10, 10, 10, 10);

    QLabel *appLabel = new QLabel(this);
    appLabel->setText(QString::fromUtf8("Application settings:"));
    layout->addWidget(appLabel, 0, 0, 1, 1);

    this->debugBox = new QCheckBox(this);
    this->debugBox->setObjectName(QString::fromUtf8("debugBox"));
    this->debugBox->setText(QString::fromUtf8("Debug mode"));
    this->debugBox->setChecked(configuration->isDebugMode());
    layout->addWidget(this->debugBox, 1, 1, 1, 1);

    /* vertical spacer */
    QSpacerItem *verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    layout->addItem(verticalSpacer, 2, 0, 1, 1);

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
    this->configuration->setDebugMode(this->debugBox->isChecked());
    
    QDialog::accept();
}
