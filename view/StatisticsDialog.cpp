
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

    QLabel *packetHeaderLabel = new QLabel(centralWidget);
    packetHeaderLabel->setText(QString::fromUtf8("Packets count"));
    centralLayout->addWidget(packetHeaderLabel, 0, COL_PACKETS, 1, 1);

    QLabel *bytesHeaderLabel = new QLabel(centralWidget);
    bytesHeaderLabel->setText(QString::fromUtf8("Bytes count"));
    centralLayout->addWidget(bytesHeaderLabel, 0, COL_BYTES, 1, 1);

    /* values for each rule */
    for (int i = 0; i < rules.count(); i++) {
        FilterRule rule = rules.at(i);

        /* rule name */
        QLabel *ruleLabel = new QLabel(centralWidget);
        ruleLabel->setText(rule.getName());
        centralLayout->addWidget(ruleLabel, i + 1, COL_DESC, 1, 1);

        QSpinBox *packets = new QSpinBox(centralWidget);
        packets->setReadOnly(true);
        centralLayout->addWidget(packets, i + 1, COL_PACKETS, 1, 1);

        QSpinBox *bytes = new QSpinBox(centralWidget);
        bytes->setReadOnly(true);
        centralLayout->addWidget(bytes, i + 1, COL_BYTES, 1, 1);
    }

    /* Vertical spacer to the end */
    QSpacerItem *verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    centralLayout->addItem(verticalSpacer, rules.count() + 1, COL_DESC, 1, 1);

    /* dialog buttons */
    QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Ok, Qt::Horizontal, centralWidget);
    buttons->setObjectName(QString::fromUtf8("buttons"));
    connect(buttons, SIGNAL(accepted()), this, SLOT(accept()));
    centralLayout->addWidget(buttons, rules.count() + 2, COL_BYTES + 1, 1, 1);

    /* add scroll area to dialog using layout */
    QVBoxLayout *dialogLayout = new QVBoxLayout(this);
    dialogLayout->setMargin(0);
    dialogLayout->setSpacing(0);
    dialogLayout->addWidget(scrollArea);

    setLayout(dialogLayout);
}

StatisticsDialog::~StatisticsDialog() {
}

