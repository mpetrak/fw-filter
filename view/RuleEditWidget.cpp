
#include <qt4/QtCore/qabstractitemmodel.h>
#include <qt4/QtGui/qgridlayout.h>
#include <qt4/QtGui/qcombobox.h>
#include <QString>
#include <qt4/QtGui/qapplication.h>

#include "RuleEditWidget.h"

#define MASK_EDIT_WIDTH 50

const char* RuleEditWidget::MAC_ADDRESS_REGEX = "^([0-9|A-F]{2}:){5}[0-9|A-F]{2}$";
const char* RuleEditWidget::IPV4_ADDRESS_REGEX = "^((25[0-5]|2[0-4][0-9]|[01]?[0-9]?[0-9])\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9]?[0-9])$";
const int RuleEditWidget::NORMAL_OPTION_INDEX = 0;
const int RuleEditWidget::NEGATION_OPTION_INDEX = 1;
const int RuleEditWidget::TAB_GENERAL_INDEX = 0;
const int RuleEditWidget::TAB_LINK_INDEX = 1;
const int RuleEditWidget::TAB_NET_INDEX = 2;

RuleEditWidget::RuleEditWidget(QWidget *parent) : QTabWidget(parent) {

    this->actions.append(FilterRule::ACTION_ACCEPT);
    this->actions.append(FilterRule::ACTION_DROP);

    NetInterfaces *netIfs = new NetInterfaces();
    this->interfaces = netIfs->getIfList();
    this->interfaces.insert(0, FilterRule::OPTION_VALUE_UNSPECIFIED);
    free(netIfs);

    /* Load options of protocols */
    OptionsLoader *optionsLoader = new OptionsLoader(OptionsLoader::LINK_PROTOCOLS_OPTIONS);
    this->ebProtocols.append(optionsLoader->getOptions());
    free(optionsLoader);

    optionsLoader = new OptionsLoader(OptionsLoader::NET_PROTOCOLS_OPTIONS);
    this->ipProtocols.append(optionsLoader->getOptions());
    free(optionsLoader);

    /* Insert unspecified option to eb protocols, in ip there is all value with same meanings */
    this->ebProtocols.insert(0, FilterRule::OPTION_VALUE_UNSPECIFIED);

    /* create tabs */
    this->setupGeneralWidget();
    this->setupEbWidget();
    this->setupIpWidget();

    /* set first tab */
    this->setCurrentIndex(0);
    this->setEnabled(false);
}

RuleEditWidget::~RuleEditWidget() {
}

void RuleEditWidget::ruleSelected(QModelIndex index) {
    this->blockSignals(true);

    /* 
     * loading procedure only on valid index and if rules model is not empty.
     * Can be empty in case of deleting last rule from model.
     */
    if (index.isValid() && !this->rulesModel->isEmpty()) {
        FilterRule rule = this->rulesModel->getRule(index.row());

        this->nameEdit->setText(rule.getName());
        this->descriptionEdit->setText(rule.getDescription());
        this->actionSelect->setCurrentIndex(actions.indexOf(rule.getAction()));

        this->inInterfaceSelect->setCurrentIndex(interfaces.indexOf(rule.getInInterface()));
        this->inInterfaceNegSelect->setCurrentIndex(rule.isInInterfaceNeg() ? NEGATION_OPTION_INDEX : NORMAL_OPTION_INDEX);

        this->outInterfaceSelect->setCurrentIndex(interfaces.indexOf(rule.getOutInterface()));
        this->outInterfaceNegSelect->setCurrentIndex(rule.isOutInterfaceNeg() ? NEGATION_OPTION_INDEX : NORMAL_OPTION_INDEX);

        this->ebProtoSelect->setCurrentIndex(ebProtocols.indexOf(rule.getEbProtocol()));
        this->ebProtoNegSelect->setCurrentIndex(rule.isEbProtocolNeg() ? NEGATION_OPTION_INDEX : NORMAL_OPTION_INDEX);

        this->macSourceEdit->setText(rule.getEbSource());
        this->macSourceMaskEdit->setText(rule.getEbSourceMask());
        this->macSourceNegSelect->setCurrentIndex(rule.isEbSourceNeg() ? NEGATION_OPTION_INDEX : NORMAL_OPTION_INDEX);

        this->macDestEdit->setText(rule.getEbDest());
        this->macDestMaskEdit->setText(rule.getEbDestMask());
        this->macDestNegSelect->setCurrentIndex(rule.isEbDestNeg() ? NEGATION_OPTION_INDEX : NORMAL_OPTION_INDEX);

        this->ipProtoSelect->setCurrentIndex(ipProtocols.indexOf(!rule.getIpProtocol().isEmpty() ? rule.getIpProtocol() : FilterRule::IP_PROTO_VALUE_UNSPECIFIED));
        this->ipProtoNegSelect->setCurrentIndex(rule.isIpProtocolNeg() ? NEGATION_OPTION_INDEX : NORMAL_OPTION_INDEX);

        this->ipSourceEdit->setText(rule.getIpSource());
        if (rule.getIpSourceMask() == FilterRule::INT_VALUE_UNSPECIFIED)
            this->ipSourceMaskEdit->setText(QString::fromUtf8(""));
        else
            this->ipSourceMaskEdit->setText(QString::number(rule.getIpSourceMask()));
        this->ipSourceNegSelect->setCurrentIndex(rule.isIpSourceNeg() ? NEGATION_OPTION_INDEX : NORMAL_OPTION_INDEX);

        this->ipDestEdit->setText(rule.getIpDest());
        if (rule.getIpDestMask() == FilterRule::INT_VALUE_UNSPECIFIED)
            this->ipDestMaskEdit->setText(QString::fromUtf8(""));
        else
            this->ipDestMaskEdit->setText(QString::number(rule.getIpDestMask()));
        this->ipDestNegSelect->setCurrentIndex(rule.isIpDestNeg() ? NEGATION_OPTION_INDEX : NORMAL_OPTION_INDEX);

        this->setEnabled(true); // must be before enable/disable net layer protocol
        /* render net layer options */
        netProtocolChanged();
    } else {

        /* clear inputs to default */
        this->nameEdit->clear();
        this->descriptionEdit->clear();
        this->actionSelect->setCurrentIndex(actions.indexOf(FilterRule::ACTION_DROP));

        this->inInterfaceSelect->setCurrentIndex(interfaces.indexOf(FilterRule::OPTION_VALUE_UNSPECIFIED));
        this->inInterfaceNegSelect->setCurrentIndex(NORMAL_OPTION_INDEX);

        this->outInterfaceSelect->setCurrentIndex(interfaces.indexOf(FilterRule::OPTION_VALUE_UNSPECIFIED));
        this->outInterfaceNegSelect->setCurrentIndex(NORMAL_OPTION_INDEX);

        this->ebProtoSelect->setCurrentIndex(ebProtocols.indexOf(FilterRule::OPTION_VALUE_UNSPECIFIED));
        this->ebProtoNegSelect->setCurrentIndex(NORMAL_OPTION_INDEX);

        this->macSourceEdit->clear();
        this->macSourceMaskEdit->clear();
        this->macSourceNegSelect->setCurrentIndex(NORMAL_OPTION_INDEX);

        this->macDestEdit->clear();
        this->macDestMaskEdit->clear();
        this->macDestNegSelect->setCurrentIndex(NORMAL_OPTION_INDEX);

        this->ipProtoSelect->setCurrentIndex(ipProtocols.indexOf(FilterRule::IP_PROTO_VALUE_UNSPECIFIED));
        this->ipProtoNegSelect->setCurrentIndex(NORMAL_OPTION_INDEX);

        this->ipSourceEdit->clear();
        this->ipSourceMaskEdit->clear();
        this->ipSourceMaskEdit->clear();
        this->ipSourceNegSelect->setCurrentIndex(NORMAL_OPTION_INDEX);

        this->ipDestEdit->clear();
        this->ipDestMaskEdit->clear();
        this->ipDestMaskEdit->clear();
        this->ipDestNegSelect->setCurrentIndex(NORMAL_OPTION_INDEX);

        this->setEnabled(false);
    }

    /* enable emiting rule changed signal */
    this->blockSignals(false);
}

bool RuleEditWidget::ruleSave(QModelIndex index) {

    /* first of all, control some edits, where is possible to write bad values */
    bool wrongInput = false;
    QString optionName;

    if (!macDestEdit->text().isEmpty() && !macDestEdit->hasAcceptableInput()) {
        wrongInput = true;
        optionName = QString("Link destination address");
    }

    if (!macDestMaskEdit->text().isEmpty() && !macDestMaskEdit->hasAcceptableInput()) {
        wrongInput = true;
        optionName = QString("Link destination address mask");
    }

    if (!macSourceEdit->text().isEmpty() && !macSourceEdit->hasAcceptableInput()) {
        wrongInput = true;
        optionName = QString("Link source address");
    }

    if (!macSourceMaskEdit->text().isEmpty() && !macSourceMaskEdit->hasAcceptableInput()) {
        wrongInput = true;
        optionName = QString("Link source address mask");
    }

    if (!ipDestEdit->text().isEmpty() && !ipDestEdit->hasAcceptableInput()) {
        wrongInput = true;
        optionName = QString("Net destination address");
    }

    if (!ipSourceEdit->text().isEmpty() && !ipSourceEdit->hasAcceptableInput()) {
        wrongInput = true;
        optionName = QString("Net source address");
    }

    if (wrongInput) {
        QMessageBox::critical(this, QString::fromUtf8("Input error"),
                QString::fromUtf8("%1: wrong value!").arg(optionName), QMessageBox::Ok, QMessageBox::Ok);
    } else {

        if (index.isValid()) {
            FilterRule rule = this->rulesModel->getRule(index.row());

            rule.setName(this->nameEdit->text().trimmed());
            rule.setDescription(this->descriptionEdit->toPlainText().trimmed());
            rule.setAction(this->actionSelect->currentText());

            rule.setInInterface(this->inInterfaceSelect->currentText());
            rule.setInInterfaceNeg(this->inInterfaceNegSelect->currentIndex() == NEGATION_OPTION_INDEX);

            rule.setOutInterface(this->outInterfaceSelect->currentText());
            rule.setOutInterfaceNeg(this->outInterfaceNegSelect->currentIndex() == NEGATION_OPTION_INDEX);

            rule.setEbProtocol(this->ebProtoSelect->currentText());
            rule.setEbProtocolNeg(this->ebProtoNegSelect->currentIndex() == NEGATION_OPTION_INDEX);

            rule.setEbSource(this->macSourceEdit->text().trimmed());
            rule.setEbSourceMask(this->macSourceMaskEdit->text().trimmed());
            rule.setEbSourceNeg(this->macSourceNegSelect->currentIndex() == NEGATION_OPTION_INDEX);

            rule.setEbDest(this->macDestEdit->text().trimmed());
            rule.setEbDestMask(this->macDestMaskEdit->text().trimmed());
            rule.setEbDestNeg(this->macDestNegSelect->currentIndex() == NEGATION_OPTION_INDEX);

            if (tabIp->isEnabled()) {
                rule.setIpProtocol(this->ipProtoSelect->currentText());
                rule.setIpProtocolNeg(this->ipProtoNegSelect->currentIndex() == NEGATION_OPTION_INDEX);

                rule.setIpSource(this->ipSourceEdit->text().trimmed());
                if (this->ipSourceMaskEdit->text().trimmed().isEmpty())
                    rule.setIpSourceMask(FilterRule::INT_VALUE_UNSPECIFIED);
                else
                    rule.setIpSourceMask(this->ipSourceMaskEdit->text().toShort());
                rule.setIpSourceNeg(this->ipSourceNegSelect->currentIndex() == NEGATION_OPTION_INDEX);

                rule.setIpDest(this->ipDestEdit->text().trimmed());
                if (this->ipDestMaskEdit->text().trimmed().isEmpty())
                    rule.setIpDestMask(FilterRule::INT_VALUE_UNSPECIFIED);
                else
                    rule.setIpDestMask(this->ipDestMaskEdit->text().toShort());
                rule.setIpDestNeg(this->ipDestNegSelect->currentIndex() == NEGATION_OPTION_INDEX);

            } else {

                rule.setIpProtocol(FilterRule::IP_PROTO_VALUE_UNSPECIFIED);
                rule.setIpProtocolNeg(false);
                rule.setIpSource(QString::fromUtf8(""));
                rule.setIpSourceMask(FilterRule::INT_VALUE_UNSPECIFIED);
                rule.setIpSourceNeg(false);
                rule.setIpDest(QString::fromUtf8(""));
                rule.setIpDestMask(FilterRule::INT_VALUE_UNSPECIFIED);
                rule.setIpDestNeg(false);
            }

            /** save rule using qt model api */
            this->rulesModel->setData(index, QVariant::fromValue<FilterRule > (rule), Qt::DisplayRole);
        } else {
            QMessageBox::critical(this, QString::fromUtf8("Internal error"),
                    QString::fromUtf8("Bad index!"), QMessageBox::Ok, QMessageBox::Ok);
        }
    }

    return !wrongInput;
}

void RuleEditWidget::setRulesModel(FilterRulesModel* model) {
    this->rulesModel = model;
}

void RuleEditWidget::setupGeneralWidget() {
    /* create new widget */
    this->tabGeneral = new QWidget();
    this->tabGeneral->setObjectName(QString::fromUtf8("tabGeneral"));

    /* setup grid layout */
    QGridLayout *gridLayout = new QGridLayout(this->tabGeneral);
    gridLayout->setObjectName(QString::fromUtf8("tabGeneralGrid"));
    gridLayout->setContentsMargins(10, 10, 10, 10);

    /* fixed size policy object */
    QSizePolicy fixedSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    fixedSizePolicy.setHorizontalStretch(0);
    fixedSizePolicy.setVerticalStretch(0);

    /* rule name */
    QLabel *nameLabel = new QLabel(this->tabGeneral);
    nameLabel->setObjectName(QString::fromUtf8("nameLabel"));
    nameLabel->setText(QString::fromUtf8("Rule name: "));
    gridLayout->addWidget(nameLabel, 1, 0, 1, 1);

    this->nameEdit = new QLineEdit(this->tabGeneral);
    this->nameEdit->setObjectName(QString::fromUtf8("nameEdit"));
    gridLayout->addWidget(this->nameEdit, 1, 2, 1, 1);
    connect(nameEdit, SIGNAL(textEdited(const QString)),
            this, SLOT(ruleChangedSlot()));

    QLabel *descriptionLabel = new QLabel(this->tabGeneral);
    descriptionLabel->setObjectName(QString::fromUtf8("descriptionLabel"));
    descriptionLabel->setText(QString::fromUtf8("Description: "));
    gridLayout->addWidget(descriptionLabel, 2, 0, 1, 1);

    this->descriptionEdit = new QTextEdit(this->tabGeneral);
    this->descriptionEdit->setObjectName(QString::fromUtf8("descriptionEdit"));
    gridLayout->addWidget(this->descriptionEdit, 3, 2, 1, 1);
    connect(descriptionEdit, SIGNAL(textChanged()),
            this, SLOT(ruleChangedSlot()));

    /* vertical spacer before action */
    QSpacerItem *verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    gridLayout->addItem(verticalSpacer, 4, 2, 1, 1);

    /* action */
    QLabel *actionLabel = new QLabel(this->tabGeneral);
    actionLabel->setObjectName(QString::fromUtf8("actionLabel"));
    actionLabel->setText(QString::fromUtf8("Action: "));
    gridLayout->addWidget(actionLabel, 5, 0, 1, 1);

    this->actionSelect = new QComboBox(this->tabGeneral);
    this->actionSelect->setObjectName(QString::fromUtf8("actionSelect"));
    this->actionSelect->setSizePolicy(fixedSizePolicy);
    this->actionSelect->addItems(this->actions);
    gridLayout->addWidget(this->actionSelect, 5, 2, 1, 1);
    connect(actionSelect, SIGNAL(currentIndexChanged(int)),
            this, SLOT(ruleChangedSlot()));

    /* vertical space to the end */
    QSpacerItem *verticalEndSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    gridLayout->addItem(verticalEndSpacer, 6, 2, 1, 1);

    /* add widget as a tab */
    this->insertTab(TAB_GENERAL_INDEX, this->tabGeneral, QString::fromUtf8("General"));
}

void RuleEditWidget::setupEbWidget() {
    /* create new widget */
    this->tabEb = new QWidget();
    this->tabEb->setObjectName(QString::fromUtf8("tabEb"));

    /* setup grid layout */
    QGridLayout *gridLayout = new QGridLayout(this->tabEb);
    gridLayout->setObjectName(QString::fromUtf8("tabEbGrid"));
    gridLayout->setContentsMargins(10, 10, 10, 10);

    /* fixed size policy object */
    QSizePolicy fixedSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    fixedSizePolicy.setHorizontalStretch(0);
    fixedSizePolicy.setVerticalStretch(0);

    /* address validator */
    QRegExp rx(RuleEditWidget::MAC_ADDRESS_REGEX);
    QRegExpValidator *addrValidator = new QRegExpValidator(rx, this->tabEb);

    /* input interface */
    QLabel *inInterfaceLabel = new QLabel(this->tabEb);
    inInterfaceLabel->setObjectName(QString::fromUtf8("inInterfaceLabel"));
    inInterfaceLabel->setText(QString::fromUtf8("Input interface: "));
    gridLayout->addWidget(inInterfaceLabel, 1, 0, 1, 1);

    this->inInterfaceNegSelect = makeNegationSelect(this->tabEb);
    this->inInterfaceNegSelect->setObjectName(QString::fromUtf8("inInterfaceNegSelect"));
    gridLayout->addWidget(this->inInterfaceNegSelect, 1, 1, 1, 1);

    this->inInterfaceSelect = new QComboBox(this->tabEb);
    this->inInterfaceSelect->setObjectName(QString::fromUtf8("inInterfaceSelect"));
    this->inInterfaceSelect->setSizePolicy(fixedSizePolicy);
    this->inInterfaceSelect->addItems(this->interfaces);
    gridLayout->addWidget(this->inInterfaceSelect, 1, 2, 1, 1);
    connect(inInterfaceSelect, SIGNAL(currentIndexChanged(int)),
            this, SLOT(ruleChangedSlot()));

    /* output interface */
    QLabel *outInterfaceLabel = new QLabel(this->tabEb);
    outInterfaceLabel->setObjectName(QString::fromUtf8("outInterfaceLabel"));
    outInterfaceLabel->setText(QString::fromUtf8("Output interface: "));
    gridLayout->addWidget(outInterfaceLabel, 2, 0, 1, 1);

    this->outInterfaceNegSelect = makeNegationSelect(this->tabEb);
    this->outInterfaceNegSelect->setObjectName(QString::fromUtf8("outInterfaceNegSelect"));
    gridLayout->addWidget(this->outInterfaceNegSelect, 2, 1, 1, 1);

    this->outInterfaceSelect = new QComboBox(this->tabEb);
    this->outInterfaceSelect->setObjectName(QString::fromUtf8("outInterfaceSelect"));
    this->outInterfaceSelect->setSizePolicy(fixedSizePolicy);
    this->outInterfaceSelect->addItems(this->interfaces);
    connect(outInterfaceSelect, SIGNAL(currentIndexChanged(int)),
            this, SLOT(ruleChangedSlot()));
    gridLayout->addWidget(this->outInterfaceSelect, 2, 2, 1, 1);

    /* protocol */
    QLabel *ebProtoLabel = new QLabel(this->tabEb);
    ebProtoLabel->setObjectName(QString::fromUtf8("ebProtoLabel"));
    ebProtoLabel->setText(QString::fromUtf8("Net layer protocol: "));
    gridLayout->addWidget(ebProtoLabel, 3, 0, 1, 1);

    this->ebProtoNegSelect = makeNegationSelect(this->tabEb);
    this->ebProtoNegSelect->setObjectName(QString::fromUtf8("ebProtoNegSelect"));
    gridLayout->addWidget(this->ebProtoNegSelect, 3, 1, 1, 1);
    /* connect to slot for enable/disable net layer options */
    connect(ebProtoNegSelect, SIGNAL(currentIndexChanged(int)),
            this, SLOT(netProtocolChanged()));

    this->ebProtoSelect = new QComboBox(this->tabEb);
    this->ebProtoSelect->setObjectName(QString::fromUtf8("ebProtoSelect"));
    this->ebProtoSelect->setSizePolicy(fixedSizePolicy);
    this->ebProtoSelect->addItems(this->ebProtocols);
    /* connect to slot for enable/disable net layer options */
    connect(ebProtoSelect, SIGNAL(currentIndexChanged(const QString)),
            this, SLOT(netProtocolChanged()));
    connect(ebProtoSelect, SIGNAL(currentIndexChanged(int)),
            this, SLOT(ruleChangedSlot()));
    gridLayout->addWidget(ebProtoSelect, 3, 2, 1, 1);

    /* source address */
    QLabel *macSourceLabel = new QLabel(this->tabEb);
    macSourceLabel->setObjectName(QString::fromUtf8("macSourceLabel"));
    macSourceLabel->setText(QString::fromUtf8("Source address: "));
    gridLayout->addWidget(macSourceLabel, 4, 0, 1, 1);

    this->macSourceNegSelect = makeNegationSelect(this->tabEb);
    this->macSourceNegSelect->setObjectName(QString::fromUtf8("macSourceNegSelect"));
    gridLayout->addWidget(this->macSourceNegSelect, 4, 1, 1, 1);

    this->macSourceEdit = new QLineEdit(this->tabEb);
    this->macSourceEdit->setObjectName(QString::fromUtf8("macSourceEdit"));
    this->macSourceEdit->setValidator(addrValidator);
    connect(macSourceEdit, SIGNAL(textEdited(const QString)),
            this, SLOT(ruleChangedSlot()));
    gridLayout->addWidget(this->macSourceEdit, 4, 2, 1, 1);

    /* source mask */
    QLabel *macSourceMaskLabel = new QLabel(this->tabEb);
    macSourceMaskLabel->setObjectName(QString::fromUtf8("macSourceMaskLabel"));
    macSourceMaskLabel->setText(QString::fromUtf8("/"));
    gridLayout->addWidget(macSourceMaskLabel, 4, 3, 1, 1);

    this->macSourceMaskEdit = new QLineEdit(this->tabEb);
    this->macSourceMaskEdit->setObjectName(QString::fromUtf8("macSourceMaskEdit"));
    this->macSourceMaskEdit->setValidator(addrValidator);
    connect(macSourceMaskEdit, SIGNAL(textEdited(const QString)),
            this, SLOT(ruleChangedSlot()));
    gridLayout->addWidget(this->macSourceMaskEdit, 4, 4, 1, 1);

    /* destination address */
    QLabel *macDestLabel = new QLabel(this->tabEb);
    macDestLabel->setObjectName(QString::fromUtf8("macDestLabel"));
    macDestLabel->setText(QString::fromUtf8("Destination address: "));
    gridLayout->addWidget(macDestLabel, 5, 0, 1, 1);

    this->macDestNegSelect = makeNegationSelect(this->tabEb);
    this->macDestNegSelect->setObjectName(QString::fromUtf8("macDestNegSelect"));
    gridLayout->addWidget(this->macDestNegSelect, 5, 1, 1, 1);

    this->macDestEdit = new QLineEdit(this->tabEb);
    this->macDestEdit->setObjectName(QString::fromUtf8("macDestEdit"));
    this->macDestEdit->setValidator(addrValidator);
    connect(macDestEdit, SIGNAL(textEdited(const QString)),
            this, SLOT(ruleChangedSlot()));
    gridLayout->addWidget(this->macDestEdit, 5, 2, 1, 1);

    /* destination mask */
    QLabel *macDestMaskLabel = new QLabel(this->tabEb);
    macDestMaskLabel->setObjectName(QString::fromUtf8("macDestMaskLabel"));
    macDestMaskLabel->setText(QString::fromUtf8("/"));
    gridLayout->addWidget(macDestMaskLabel, 5, 3, 1, 1);

    this->macDestMaskEdit = new QLineEdit(this->tabEb);
    this->macDestMaskEdit->setObjectName(QString::fromUtf8("macDestMaskEdit"));
    this->macDestMaskEdit->setValidator(addrValidator);
    connect(macDestMaskEdit, SIGNAL(textEdited(const QString)),
            this, SLOT(ruleChangedSlot()));
    gridLayout->addWidget(this->macDestMaskEdit, 5, 4, 1, 1);

    /* Vertical spacer to the end */
    QSpacerItem *verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    gridLayout->addItem(verticalSpacer, 6, 2, 1, 1);

    /* add widget as a tab */
    this->insertTab(TAB_LINK_INDEX, this->tabEb, QString::fromUtf8("Link layer"));
}

void RuleEditWidget::setupIpWidget() {
    /* create new widget */
    this->tabIp = new QWidget();
    this->tabIp->setObjectName(QString::fromUtf8("tabIp"));

    /* setup grid layout */
    QGridLayout *gridLayout = new QGridLayout(this->tabIp);
    gridLayout->setObjectName(QString::fromUtf8("tabIpGrid"));
    gridLayout->setContentsMargins(10, 10, 10, 10);

    /* fixed size policy object */
    QSizePolicy fixedSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    fixedSizePolicy.setHorizontalStretch(0);
    fixedSizePolicy.setVerticalStretch(0);

    /* validator for addresses */
    QRegExp rx(RuleEditWidget::IPV4_ADDRESS_REGEX);
    QRegExpValidator *addrValidator = new QRegExpValidator(rx, this->tabIp);

    /* validator for mask fields */
    QIntValidator *maskValidator = new QIntValidator(this->tabIp);
    maskValidator->setRange(0, 64);

    /* protocol */
    QLabel *ipProtoLabel = new QLabel(this->tabIp);
    ipProtoLabel->setObjectName(QString::fromUtf8("ipProtoLabel"));
    ipProtoLabel->setText(QString::fromUtf8("Upper layer protocol: "));
    gridLayout->addWidget(ipProtoLabel, 1, 0, 1, 1);

    this->ipProtoNegSelect = makeNegationSelect(this->tabIp);
    this->ipProtoNegSelect->setObjectName(QString::fromUtf8("ipProtoNegSelect"));
    gridLayout->addWidget(this->ipProtoNegSelect, 1, 1, 1, 1);

    this->ipProtoSelect = new QComboBox(this->tabIp);
    this->ipProtoSelect->setObjectName(QString::fromUtf8("ipProtoSelect"));
    this->ipProtoSelect->setSizePolicy(fixedSizePolicy);
    this->ipProtoSelect->addItems(this->ipProtocols);
    connect(ipProtoSelect, SIGNAL(currentIndexChanged(int)),
            this, SLOT(ruleChangedSlot()));
    gridLayout->addWidget(ipProtoSelect, 1, 2, 1, 1);

    /* source address */
    QLabel *ipSourceLabel = new QLabel(this->tabIp);
    ipSourceLabel->setObjectName(QString::fromUtf8("ipSourceLabel"));
    ipSourceLabel->setText(QString::fromUtf8("Source address: "));
    gridLayout->addWidget(ipSourceLabel, 2, 0, 1, 1);

    this->ipSourceNegSelect = makeNegationSelect(this->tabIp);
    this->ipSourceNegSelect->setObjectName(QString::fromUtf8("ipSourceNegSelect"));
    gridLayout->addWidget(ipSourceNegSelect, 2, 1, 1, 1);

    this->ipSourceEdit = new QLineEdit(this->tabIp);
    this->ipSourceEdit->setObjectName(QString::fromUtf8("ipSourceEdit"));
    this->ipSourceEdit->setValidator(addrValidator);
    connect(ipSourceEdit, SIGNAL(textEdited(const QString)),
            this, SLOT(ruleChangedSlot()));
    gridLayout->addWidget(this->ipSourceEdit, 2, 2, 1, 1);

    /* source mask */
    QLabel *ipSourceMaskLabel = new QLabel(this->tabIp);
    ipSourceMaskLabel->setObjectName(QString::fromUtf8("ipSourceMaskLabel"));
    ipSourceMaskLabel->setText(QString::fromUtf8("/"));
    gridLayout->addWidget(ipSourceMaskLabel, 2, 3, 1, 1);

    this->ipSourceMaskEdit = new QLineEdit(this->tabIp);
    this->ipSourceMaskEdit->setObjectName(QString::fromUtf8("ipSourceMaskEdit"));
    this->ipSourceMaskEdit->setValidator(maskValidator);
    this->ipSourceMaskEdit->setFixedWidth(MASK_EDIT_WIDTH);
    connect(ipSourceMaskEdit, SIGNAL(textEdited(const QString)),
            this, SLOT(ruleChangedSlot()));
    gridLayout->addWidget(this->ipSourceMaskEdit, 2, 4, 1, 1);

    /* destination address */
    QLabel *ipDestLabel = new QLabel(this->tabIp);
    ipDestLabel->setObjectName(QString::fromUtf8("ipDestLabel"));
    ipDestLabel->setText(QString::fromUtf8("Destination address: "));
    gridLayout->addWidget(ipDestLabel, 3, 0, 1, 1);

    this->ipDestNegSelect = makeNegationSelect(this->tabIp);
    this->ipDestNegSelect->setObjectName(QString::fromUtf8("ipDestNegSelect"));
    gridLayout->addWidget(this->ipDestNegSelect, 3, 1, 1, 1);

    this->ipDestEdit = new QLineEdit(this->tabIp);
    this->ipDestEdit->setObjectName(QString::fromUtf8("ipDestEdit"));
    this->ipDestEdit->setValidator(addrValidator);
    connect(ipDestEdit, SIGNAL(textEdited(const QString)),
            this, SLOT(ruleChangedSlot()));
    gridLayout->addWidget(this->ipDestEdit, 3, 2, 1, 1);

    /* destination mask */
    QLabel *ipDestMaskLabel = new QLabel(this->tabIp);
    ipDestMaskLabel->setObjectName(QString::fromUtf8("ipDestMaskLabel"));
    ipDestMaskLabel->setText(QString::fromUtf8("/"));
    gridLayout->addWidget(ipDestMaskLabel, 3, 3, 1, 1);

    this->ipDestMaskEdit = new QLineEdit(this->tabIp);
    this->ipDestMaskEdit->setObjectName(QString::fromUtf8("ipDestMaskEdit"));
    this->ipDestMaskEdit->setValidator(maskValidator);
    this->ipDestMaskEdit->setFixedWidth(MASK_EDIT_WIDTH);
    connect(ipDestMaskEdit, SIGNAL(textEdited(const QString)),
            this, SLOT(ruleChangedSlot()));
    gridLayout->addWidget(this->ipDestMaskEdit, 3, 4, 1, 1);

    /* Vertical spacer to the end */
    QSpacerItem *verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    gridLayout->addItem(verticalSpacer, 4, 2, 1, 1);

    this->insertTab(TAB_NET_INDEX, this->tabIp, QString::fromUtf8("Net layer"));
}

QComboBox *RuleEditWidget::makeNegationSelect(QWidget *parent) {
    QComboBox *select = new QComboBox(parent);
    select->insertItem(NORMAL_OPTION_INDEX, QString::fromUtf8("IS"));
    select->insertItem(NEGATION_OPTION_INDEX, QString::fromUtf8("NOT"));
    connect(select, SIGNAL(currentIndexChanged(int)), this, SLOT(ruleChangedSlot()));
    return select;
}

void RuleEditWidget::netProtocolChanged() {
    if (ebProtoSelect->currentText() == FilterRule::IP_PROTO_VALUE_IPV4
            && ebProtoNegSelect->currentIndex() != NEGATION_OPTION_INDEX) {


        if (!tabIp->isEnabled()) {
            this->tabIp->setEnabled(true);
            this->setTabEnabled(TAB_NET_INDEX, true);

            Logger::getInstance()->debug(std::string("Enabled net options for protocol: ") +
                    ebProtoSelect->currentText().toStdString());
        }
    } else {

        if (tabIp->isEnabled()) {
            this->tabIp->setEnabled(false);
            this->setTabEnabled(TAB_NET_INDEX, false);
            Logger::getInstance()->debug("Disabled net options");
        }
    }
}

void RuleEditWidget::ruleChangedSlot() {
    emit ruleChanged();
}
