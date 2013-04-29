
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
    this->setFixedSize(400, 300);

    QFrame *appFrame = new QFrame(this);
    appFrame->setObjectName(QString::fromUtf8("debugFrame"));
    appFrame->setGeometry(QRect(10, 10, 380, 160));
    appFrame->setFrameShape(QFrame::StyledPanel);
    appFrame->setFrameShadow(QFrame::Raised);

    QGridLayout *appLayout = new QGridLayout(appFrame);
    appLayout->setObjectName("appLayout");
    appLayout->setContentsMargins(10, 10, 10, 10);

    QLabel *appLabel = new QLabel(appFrame);
    appLabel->setText(QString::fromUtf8("Application settings: "));
    appLayout->addWidget(appLabel, 0, 0, 1, 1);

    QLabel *debugLabel = new QLabel(appFrame);
    debugLabel->setText(QString::fromUtf8("Debug mode: "));
    appLayout->addWidget(debugLabel, 1, 1, 1, 1);

    this->debugBox = new QCheckBox(appFrame);
    this->debugBox->setObjectName(QString::fromUtf8("debugBox"));
    this->debugBox->setText(QString::fromUtf8(""));
    this->debugBox->setChecked(configuration->isDebugMode());
    appLayout->addWidget(this->debugBox, 1, 2, 1, 1);

    QLabel *writeOnStartLabel = new QLabel(appFrame);
    writeOnStartLabel->setText(QString::fromUtf8("Write rules at start: "));
    appLayout->addWidget(writeOnStartLabel, 2, 1, 1, 1);
    QLabel *writeOnStartLabel2 = new QLabel(appFrame);
    writeOnStartLabel2->setText(QString::fromUtf8("(recommended)"));
    appLayout->addWidget(writeOnStartLabel2, 3, 1, 1, 1);

    this->writeOnStartBox = new QCheckBox(appFrame);
    this->writeOnStartBox->setObjectName(QString::fromUtf8("writeOnStartBox"));
    this->writeOnStartBox->setText(QString::fromUtf8(""));
    this->writeOnStartBox->setChecked(configuration->isWriteOnStart());
    appLayout->addWidget(this->writeOnStartBox, 2, 2, 2, 1);

    /* default action */
    QLabel *defaultActionLabel = new QLabel(appFrame);
    defaultActionLabel->setObjectName(QString::fromUtf8("defaultActionLabel"));
    defaultActionLabel->setText(QString::fromUtf8("Default action: "));
    appLayout->addWidget(defaultActionLabel, 4, 1, 1, 1);

    this->defaultActionSelect = new QComboBox(appFrame);
    this->defaultActionSelect->setObjectName(QString::fromUtf8("defaultActionSelect"));
    this->defaultActionSelect->addItems(this->actions);
    this->defaultActionSelect->setCurrentIndex(actions.indexOf(configuration->getDefaultAction()));
    appLayout->addWidget(this->defaultActionSelect, 4, 2, 1, 1);

    /* vertical spacer */
    QSpacerItem *appSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    appLayout->addItem(appSpacer, 5, 0, 1, 1);

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
    configuration->setWriteOnStart(writeOnStartBox->isChecked());
    configuration->setDefaultAction(defaultActionSelect->currentText());

    /* save configuration */
    if (!configuration->saveToXML()) {
        QMessageBox::critical(this, QString::fromUtf8("Saving error"),
                QString::fromUtf8("Error during saving configuration to XML file"), QMessageBox::Ok, QMessageBox::Ok);
    } else {

        QDialog::accept();
    }
}
