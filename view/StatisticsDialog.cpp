
#include "StatisticsDialog.h"

int StatisticsDialog::COL_DESC = 0;
int StatisticsDialog::COL_PACKETS = 1;
int StatisticsDialog::COL_BYTES = 2;

StatisticsDialog::StatisticsDialog(QWidget *parent, QList<FilterRule> rules) : QDialog(parent) {

    this->rules = rules;

    /* make GUI object */
    if (this->objectName().isEmpty()) {
        this->setObjectName(QString::fromUtf8("StatisticsDialog"));
    }
    this->setWindowTitle(QString::fromUtf8("Statistics"));
    this->resize(400, 300);

    /* layout */
    QGridLayout *layout = new QGridLayout(this);
    layout->setObjectName(QString::fromUtf8("layout"));
    layout->setContentsMargins(10, 10, 10, 10);

    /* headers of values */
    QLabel *ruleHeaderLabel = new QLabel(this);
    ruleHeaderLabel->setText(QString::fromUtf8("Rule name"));
    layout->addWidget(ruleHeaderLabel, 0, COL_DESC, 1, 1);

    QLabel *packetHeaderLabel = new QLabel(this);
    packetHeaderLabel->setText(QString::fromUtf8("Packets count"));
    layout->addWidget(packetHeaderLabel, 0, COL_PACKETS, 1, 1);

    QLabel *bytesHeaderLabel = new QLabel(this);
    bytesHeaderLabel->setText(QString::fromUtf8("Bytes count"));
    layout->addWidget(bytesHeaderLabel, 0, COL_BYTES, 1, 1);

    /* values for each rule */
    for (int i = 0; i < rules.count(); i++) {
        FilterRule rule = rules.at(i);

        /* rule name */
        QLabel *ruleLabel = new QLabel(this);
        ruleLabel->setText(rule.getName());
        layout->addWidget(ruleLabel, i + 1, COL_DESC, 1, 1);

        QSpinBox *packets = new QSpinBox(this);
        packets->setReadOnly(true);
        layout->addWidget(packets, i + 1, COL_PACKETS, 1, 1);

        QSpinBox *bytes = new QSpinBox(this);
        bytes->setReadOnly(true);
        layout->addWidget(bytes, i + 1, COL_BYTES, 1, 1);
    }

    /* Vertical spacer to the end */
    QSpacerItem *verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    layout->addItem(verticalSpacer, rules.count() + 1, COL_DESC, 1, 1);

    /* dialog buttons */
    QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Ok, Qt::Horizontal, this);
    buttons->setObjectName(QString::fromUtf8("buttons"));
    connect(buttons, SIGNAL(accepted()), this, SLOT(accept()));
    layout->addWidget(buttons, rules.count() + 2, COL_BYTES, 1, 1);
}

StatisticsDialog::~StatisticsDialog() {
}

