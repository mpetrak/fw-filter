
#include <qt4/QtCore/qcoreevent.h>

#include "StatisticsDialog.h"

int StatisticsDialog::COL_DESC = 0;
int StatisticsDialog::COL_PACKETS = 2;
int StatisticsDialog::COL_BYTES = 4;
int StatisticsDialog::REFRESH = 30000;

StatisticsDialog::StatisticsDialog(QWidget *parent, QList<FilterRule> rules) : QDialog(parent) {

    this->rules = rules;

    loader = new RulesStatsLoader();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(loadStatistics()));

    /* make GUI object */
    if (this->objectName().isEmpty()) {
        this->setObjectName(QString::fromUtf8("StatisticsDialog"));
    }
    this->setWindowTitle(QString::fromUtf8("Statistics"));
    this->setFixedWidth(450);
    this->resize(450, 300);

    /* central widget and layout */
    centralWidget = new QWidget(this);
    centralWidget->setMinimumSize(this->size());
    QGridLayout *centralLayout = new QGridLayout(centralWidget);
    centralLayout->setObjectName(QString::fromUtf8("layout"));
    centralLayout->setContentsMargins(10, 10, 10, 10);
    centralLayout->setSizeConstraint(QLayout::SetMinimumSize);
    centralWidget->setLayout(centralLayout);


    /* scroll area */
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setWidget(centralWidget);

    /* headers of values */
    QLabel *ruleHeaderLabel = new QLabel(centralWidget);
    ruleHeaderLabel->setText(QString::fromUtf8("Rule name"));
    centralLayout->addWidget(ruleHeaderLabel, 0, COL_DESC, 1, 1);

    /* Horizontal after rule name spacer */
    QSpacerItem *ruleSpacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    centralLayout->addItem(ruleSpacer, rules.count() + 1, COL_DESC + 1, 1, 1);

    QLabel *packetHeaderLabel = new QLabel(centralWidget);
    packetHeaderLabel->setText(QString::fromUtf8("Packets count"));
    centralLayout->addWidget(packetHeaderLabel, 0, COL_PACKETS, 1, 1);

    /* Horizontal after packets count spacer */
    QSpacerItem *packetsSpacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    centralLayout->addItem(packetsSpacer, rules.count() + 1, COL_PACKETS + 1, 1, 1);

    QLabel *bytesHeaderLabel = new QLabel(centralWidget);
    bytesHeaderLabel->setText(QString::fromUtf8("Bytes count"));
    centralLayout->addWidget(bytesHeaderLabel, 0, COL_BYTES, 1, 1);

    /* Horizontal after bytes count spacer */
    QSpacerItem *bytesSpacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    centralLayout->addItem(bytesSpacer, rules.count() + 1, COL_BYTES + 1, 1, 1);

    /* values for each rule */
    for (int i = 0; i < rules.count(); i++) {

        /* rule name */
        QLabel *ruleLabel = new QLabel(centralWidget);
        centralLayout->addWidget(ruleLabel, i + 1, COL_DESC, 1, 1);
        ruleLabelList.append(ruleLabel);

        QLabel *packets = new QLabel(centralWidget);
        centralLayout->addWidget(packets, i + 1, COL_PACKETS, 1, 1);
        packetsList.append(packets);

        QLabel *bytes = new QLabel(centralWidget);
        centralLayout->addWidget(bytes, i + 1, COL_BYTES, 1, 1);
        bytesList.append(bytes);
    }

    /* Vertical spacer to the end */
    QSpacerItem *verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    centralLayout->addItem(verticalSpacer, rules.count() + 1, COL_DESC, 1, 1);

    /* dialog buttons */
    QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Ok, Qt::Horizontal, centralWidget);
    buttons->setObjectName(QString::fromUtf8("buttons"));
    connect(buttons, SIGNAL(accepted()), this, SLOT(close()));
    centralLayout->addWidget(buttons, rules.count() + 2, COL_BYTES, 1, 1);

    /* add scroll area to dialog using layout */
    QVBoxLayout *dialogLayout = new QVBoxLayout(this);
    dialogLayout->setMargin(0);
    dialogLayout->setSpacing(0);
    dialogLayout->addWidget(scrollArea);

    setLayout(dialogLayout);

    /* first load and start timer */
    loadStatistics();

}

StatisticsDialog::~StatisticsDialog() {

}

void StatisticsDialog::loadStatistics() {

    timer->stop();

    if (!loader->loadStatistics(&rules)) {
        QMessageBox::critical(NULL, QString::fromUtf8("Loading error"),
                QString::fromUtf8("Error during loading rules statistics from system"),
                QMessageBox::Ok, QMessageBox::Ok);

        /* disable timer signals - there is error, so not refresh loading */
        timer->blockSignals(true);
    }

    /* fill values */
    for (int i = 0; i < rules.count(); i++) {
        FilterRule rule = rules.at(i);

        ruleLabelList[i]->setText(rule.getName());
        packetsList[i]->setText(QString::number(rule.getPacketsCount()));
        bytesList[i]->setText(formatBytes(rule.getBytesCount()));
    }

    timer->start(REFRESH);
}

QString StatisticsDialog::formatBytes(long bytes) {
    QStringList suffix;
    suffix << "B" << "KB" << "MB" << "GB" << "TB";
    double doubleBytes = bytes;
    int i = 0;

    if (bytes > 1024) {
        for (i = 0; (bytes / 1024) > 0; i++, bytes /= 1024) {
            doubleBytes = bytes / 1024.0;
        }
    }

    return QString::fromUtf8("%1 %2").arg(QString::number(doubleBytes, 'f', 2), suffix[i]);
}

void StatisticsDialog::closeEvent(QCloseEvent* event) {
    disconnect(timer, SIGNAL(timeout()), this, SLOT(loadStatistics()));
    timer->stop();
    free(loader);
    event->accept();
}