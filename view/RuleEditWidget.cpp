/* 
 * File:   ruleEditWidget.cpp
 * Author: petris
 * 
 * Created on 10. leden 2013, 13:10
 */

#include <qt4/QtCore/qabstractitemmodel.h>
#include <qt4/QtGui/qgridlayout.h>
#include <qt4/QtGui/qcombobox.h>
#include <QString>
#include <qt4/QtGui/qapplication.h>

#include "RuleEditWidget.h"

#define MASK_EDIT_WIDTH 50

const char* RuleEditWidget::MAC_ADDRESS_REGEX = "^([0-9|A-F]{2}:){5}[0-9|A-F]{2}$";
const char* RuleEditWidget::IPV4_ADDRESS_REGEX = "^((25[0-5]|2[0-4][0-9]|[01]?[0-9]?[0-9])\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9]?[0-9])$";

RuleEditWidget::RuleEditWidget(QWidget *parent) : QTabWidget(parent) {
    /* set own tab widget */
    this->setGeometry(QRect(230, 10, 511, 531));
    this->setObjectName(QString::fromUtf8("ruleEditWidget"));

    this->actions.append(QString::fromUtf8("ACCEPT"));
    this->actions.append(QString::fromUtf8("DROP"));
    //this->actions.append(QString::fromUtf8("CONTINUE"));

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

    /* Insert unspecified option*/
    this->ipProtocols.insert(0, FilterRule::OPTION_VALUE_UNSPECIFIED);
    this->ebProtocols.insert(0, FilterRule::OPTION_VALUE_UNSPECIFIED);

    /* create tabs */
    this->setupGeneralWidget();
    this->setupEbWidget();
    this->setupIpWidget();

    /* set first tab */
    this->setCurrentIndex(0);
}

RuleEditWidget::~RuleEditWidget() {
}

void RuleEditWidget::ruleSelected(QModelIndex index) {

    if (index.isValid()) {
        FilterRule rule = this->rulesModel->getRule(index.row());

        this->nameEdit->setText(rule.getName());
        this->descriptionEdit->setText(rule.getDescription());
        this->actionSelect->setCurrentIndex(actions.indexOf(rule.getAction()));

        this->inInterfaceSelect->setCurrentIndex(interfaces.indexOf(rule.getInInterface()));
        this->inInterfaceNBox->setChecked(rule.isInInterfaceNeg());

        this->outInterfaceSelect->setCurrentIndex(interfaces.indexOf(rule.getOutInterface()));
        this->outInterfaceNBox->setChecked(rule.isOutInterfaceNeg());

        this->ebProtoSelect->setCurrentIndex(ebProtocols.indexOf(rule.getEbProtocol()));
        this->ebProtoNBox->setChecked(rule.isEbProtocolNeg());

        this->macSourceEdit->setText(rule.getEbSource());
        this->macSourceMaskEdit->setText(rule.getEbSourceMask());
        this->macSourceNBox->setChecked(rule.isEbSourceNeg());

        this->macDestEdit->setText(rule.getEbDest());
        this->macDestMaskEdit->setText(rule.getEbDestMask());
        this->macDestNBox->setChecked(rule.isEbDestNeg());

        this->ipProtoSelect->setCurrentIndex(ipProtocols.indexOf(rule.getIpProtocol()));
        this->ipProtoNBox->setChecked(rule.isIpProtocolNeg());

        this->ipSourceEdit->setText(rule.getIpSource());
        if (rule.getIpSourceMask() == FilterRule::INT_VALUE_UNSPECIFIED)
            this->ipSourceMaskEdit->setText(QString::fromUtf8(""));
        else
            this->ipSourceMaskEdit->setText(QString::number(rule.getIpSourceMask()));
        this->ipSourceNBox->setChecked(rule.isIpSourceNeg());

        this->ipDestEdit->setText(rule.getIpDest());
        if (rule.getIpDestMask() == FilterRule::INT_VALUE_UNSPECIFIED)
            this->ipDestMaskEdit->setText(QString::fromUtf8(""));
        else
            this->ipDestMaskEdit->setText(QString::number(rule.getIpDestMask()));
        this->ipDestNBox->setChecked(rule.isIpDestNeg());
    }
}

void RuleEditWidget::ruleSave(QModelIndex index) {

    if (index.isValid()) {
        FilterRule rule = this->rulesModel->getRule(index.row());

        rule.setName(this->nameEdit->text().trimmed());
        rule.setDescription(this->descriptionEdit->toPlainText().trimmed());
        rule.setAction(this->actionSelect->currentText());

        rule.setInInterface(this->inInterfaceSelect->currentText());
        rule.setInInterfaceNeg(this->inInterfaceNBox->isChecked());

        rule.setOutInterface(this->outInterfaceSelect->currentText());
        rule.setOutInterfaceNeg(this->outInterfaceNBox->isChecked());

        rule.setEbProtocol(this->ebProtoSelect->currentText());
        rule.setEbProtocolNeg(this->ebProtoNBox->isChecked());

        rule.setEbSource(this->macSourceEdit->text().trimmed());
        rule.setEbSourceMask(this->macSourceMaskEdit->text().trimmed());
        rule.setEbSourceNeg(this->macSourceNBox->isChecked());

        rule.setEbDest(this->macDestEdit->text().trimmed());
        rule.setEbDestMask(this->macDestMaskEdit->text().trimmed());
        rule.setEbDestNeg(this->macDestNBox->isChecked());

        rule.setIpProtocol(this->ipProtoSelect->currentText());
        rule.setIpProtocolNeg(this->ipProtoNBox->isChecked());

        rule.setIpSource(this->ipSourceEdit->text().trimmed());
        if (this->ipSourceMaskEdit->text().trimmed().isEmpty())
            rule.setIpSourceMask(FilterRule::INT_VALUE_UNSPECIFIED);
        else
            rule.setIpSourceMask(this->ipSourceMaskEdit->text().toShort());
        rule.setIpSourceNeg(this->ipSourceNBox->isChecked());

        rule.setIpDest(this->ipDestEdit->text().trimmed());
        if (this->ipDestMaskEdit->text().trimmed().isEmpty())
            rule.setIpDestMask(FilterRule::INT_VALUE_UNSPECIFIED);
        else
            rule.setIpDestMask(this->ipDestMaskEdit->text().toShort());
        rule.setIpDestNeg(this->ipDestNBox->isChecked());

        /** save rule using qt model api */
        this->rulesModel->setData(index, QVariant::fromValue<FilterRule > (rule), Qt::DisplayRole);
    }
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
    //this->nameEdit->setSizePolicy(fixedSizePolicy);
    gridLayout->addWidget(this->nameEdit, 1, 2, 1, 1);

    QLabel *descriptionLabel = new QLabel(this->tabGeneral);
    descriptionLabel->setObjectName(QString::fromUtf8("descriptionLabel"));
    descriptionLabel->setText(QString::fromUtf8("Description: "));
    gridLayout->addWidget(descriptionLabel, 2, 0, 1, 1);

    this->descriptionEdit = new QTextEdit(this->tabGeneral);
    this->descriptionEdit->setObjectName(QString::fromUtf8("descriptionEdit"));
    gridLayout->addWidget(this->descriptionEdit, 3, 2, 1, 1);

    /* affected chains */
    QLabel *chainsLabel = new QLabel(this->tabGeneral);
    chainsLabel->setObjectName(QString::fromUtf8("chainsLabel"));
    chainsLabel->setText(QString::fromUtf8("Affected chains:"));
    gridLayout->addWidget(chainsLabel, 4, 0, 1, 1);

    this->chainInputBox = new QCheckBox(this->tabGeneral);
    this->chainInputBox->setObjectName(QString::fromUtf8("chainInputBox"));
    this->chainInputBox->setText(RulesPusher::NF_CHAIN_INPUT);
    gridLayout->addWidget(this->chainInputBox, 5, 2, 1, 1);

    this->chainForwardBox = new QCheckBox(this->tabGeneral);
    this->chainForwardBox->setObjectName(QString::fromUtf8("chainForwardBox"));
    this->chainForwardBox->setText(RulesPusher::NF_CHAIN_FORWARD);
    gridLayout->addWidget(this->chainForwardBox, 6, 2, 1, 1);

    this->chainOutputBox = new QCheckBox(this->tabGeneral);
    this->chainOutputBox->setObjectName(QString::fromUtf8("chainOutputBox"));
    this->chainOutputBox->setText(RulesPusher::NF_CHAIN_OUTPUT);
    gridLayout->addWidget(this->chainOutputBox, 7, 2, 1, 1);

    //        QSpacerItem *horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    //        gridLayout->addItem(horizontalSpacer, 7, 2, 1, 1);

    /* vertical spacer before action */
    QSpacerItem *verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    gridLayout->addItem(verticalSpacer, 8, 2, 1, 1);

    /* action */
    QLabel *actionLabel = new QLabel(this->tabGeneral);
    actionLabel->setObjectName(QString::fromUtf8("actionLabel"));
    actionLabel->setText(QString::fromUtf8("Action: "));
    gridLayout->addWidget(actionLabel, 9, 0, 1, 1);

    this->actionSelect = new QComboBox(this->tabGeneral);
    this->actionSelect->setObjectName(QString::fromUtf8("actionSelect"));
    this->actionSelect->setSizePolicy(fixedSizePolicy);
    this->actionSelect->addItems(this->actions);
    gridLayout->addWidget(this->actionSelect, 9, 2, 1, 1);

    /* vertical space to the end */
    QSpacerItem *verticalEndSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    gridLayout->addItem(verticalEndSpacer, 10, 2, 1, 1);

    /* add widget as a tab */
    this->addTab(this->tabGeneral, QString::fromUtf8("General"));
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

    this->inInterfaceNBox = new QCheckBox(this->tabEb);
    this->inInterfaceNBox->setObjectName(QString::fromUtf8("inInterfaceNBox"));
    this->inInterfaceNBox->setText(QString::fromUtf8("!"));
    gridLayout->addWidget(this->inInterfaceNBox, 1, 1, 1, 1);

    this->inInterfaceSelect = new QComboBox(this->tabEb);
    this->inInterfaceSelect->setObjectName(QString::fromUtf8("inInterfaceSelect"));
    this->inInterfaceSelect->setSizePolicy(fixedSizePolicy);
    this->inInterfaceSelect->addItems(this->interfaces);
    gridLayout->addWidget(this->inInterfaceSelect, 1, 2, 1, 1);

    /* output interface */
    QLabel *outInterfaceLabel = new QLabel(this->tabEb);
    outInterfaceLabel->setObjectName(QString::fromUtf8("outInterfaceLabel"));
    outInterfaceLabel->setText(QString::fromUtf8("Output interface: "));
    gridLayout->addWidget(outInterfaceLabel, 2, 0, 1, 1);

    this->outInterfaceNBox = new QCheckBox(this->tabEb);
    this->outInterfaceNBox->setObjectName(QString::fromUtf8("outInterfaceNBox"));
    this->outInterfaceNBox->setText(QString::fromUtf8("!"));
    gridLayout->addWidget(this->outInterfaceNBox, 2, 1, 1, 1);

    this->outInterfaceSelect = new QComboBox(this->tabEb);
    this->outInterfaceSelect->setObjectName(QString::fromUtf8("outInterfaceSelect"));
    this->outInterfaceSelect->setSizePolicy(fixedSizePolicy);
    this->outInterfaceSelect->addItems(this->interfaces);
    gridLayout->addWidget(this->outInterfaceSelect, 2, 2, 1, 1);

    /* protocol */
    QLabel *ebProtoLabel = new QLabel(this->tabEb);
    ebProtoLabel->setObjectName(QString::fromUtf8("ebProtoLabel"));
    ebProtoLabel->setText(QString::fromUtf8("Protocol: "));
    gridLayout->addWidget(ebProtoLabel, 3, 0, 1, 1);

    this->ebProtoNBox = new QCheckBox(this->tabEb);
    this->ebProtoNBox->setObjectName(QString::fromUtf8("ebProtoNBox"));
    this->ebProtoNBox->setText(QString::fromUtf8("!"));
    gridLayout->addWidget(this->ebProtoNBox, 3, 1, 1, 1);

    this->ebProtoSelect = new QComboBox(this->tabEb);
    this->ebProtoSelect->setObjectName(QString::fromUtf8("ebProtoSelect"));
    this->ebProtoSelect->setSizePolicy(fixedSizePolicy);
    this->ebProtoSelect->addItems(this->ebProtocols);
    gridLayout->addWidget(ebProtoSelect, 3, 2, 1, 1);

    /* source address */
    QLabel *macSourceLabel = new QLabel(this->tabEb);
    macSourceLabel->setObjectName(QString::fromUtf8("macSourceLabel"));
    macSourceLabel->setText(QString::fromUtf8("Source address: "));
    gridLayout->addWidget(macSourceLabel, 4, 0, 1, 1);

    this->macSourceNBox = new QCheckBox(this->tabEb);
    this->macSourceNBox->setObjectName(QString::fromUtf8("macSourceNBox"));
    this->macSourceNBox->setText(QString::fromUtf8("!"));
    gridLayout->addWidget(this->macSourceNBox, 4, 1, 1, 1);

    this->macSourceEdit = new QLineEdit(this->tabEb);
    this->macSourceEdit->setObjectName(QString::fromUtf8("macSourceEdit"));
    this->macSourceEdit->setValidator(addrValidator);
    gridLayout->addWidget(this->macSourceEdit, 4, 2, 1, 1);

    /* source mask */
    QLabel *macSourceMaskLabel = new QLabel(this->tabEb);
    macSourceMaskLabel->setObjectName(QString::fromUtf8("macSourceMaskLabel"));
    macSourceMaskLabel->setText(QString::fromUtf8("/"));
    gridLayout->addWidget(macSourceMaskLabel, 4, 3, 1, 1);

    this->macSourceMaskEdit = new QLineEdit(this->tabEb);
    this->macSourceMaskEdit->setObjectName(QString::fromUtf8("macSourceMaskEdit"));
    this->macSourceMaskEdit->setValidator(addrValidator);
    gridLayout->addWidget(this->macSourceMaskEdit, 4, 4, 1, 1);

    /* destination address */
    QLabel *macDestLabel = new QLabel(this->tabEb);
    macDestLabel->setObjectName(QString::fromUtf8("macDestLabel"));
    macDestLabel->setText(QString::fromUtf8("Destination address: "));
    gridLayout->addWidget(macDestLabel, 5, 0, 1, 1);

    this->macDestNBox = new QCheckBox(this->tabEb);
    this->macDestNBox->setObjectName(QString::fromUtf8("macDestNBox"));
    this->macDestNBox->setText(QString::fromUtf8("!"));
    gridLayout->addWidget(this->macDestNBox, 5, 1, 1, 1);

    this->macDestEdit = new QLineEdit(this->tabEb);
    this->macDestEdit->setObjectName(QString::fromUtf8("macDestEdit"));
    this->macDestEdit->setValidator(addrValidator);
    gridLayout->addWidget(this->macDestEdit, 5, 2, 1, 1);

    /* destination mask */
    QLabel *macDestMaskLabel = new QLabel(this->tabEb);
    macDestMaskLabel->setObjectName(QString::fromUtf8("macDestMaskLabel"));
    macDestMaskLabel->setText(QString::fromUtf8("/"));
    gridLayout->addWidget(macDestMaskLabel, 5, 3, 1, 1);

    this->macDestMaskEdit = new QLineEdit(this->tabEb);
    this->macDestMaskEdit->setObjectName(QString::fromUtf8("macDestMaskEdit"));
    this->macDestMaskEdit->setValidator(addrValidator);
    gridLayout->addWidget(this->macDestMaskEdit, 5, 4, 1, 1);

    /* Vertical spacer to the end */
    QSpacerItem *verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    gridLayout->addItem(verticalSpacer, 6, 2, 1, 1);

    /* add widget as a tab */
    this->addTab(this->tabEb, QString::fromUtf8("Link layer"));
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
    ipProtoLabel->setText(QString::fromUtf8("Protocol: "));
    gridLayout->addWidget(ipProtoLabel, 1, 0, 1, 1);

    this->ipProtoNBox = new QCheckBox(this->tabIp);
    this->ipProtoNBox->setObjectName(QString::fromUtf8("ipProtoNBox"));
    this->ipProtoNBox->setText(QString::fromUtf8("!"));
    gridLayout->addWidget(this->ipProtoNBox, 1, 1, 1, 1);

    this->ipProtoSelect = new QComboBox(this->tabIp);
    this->ipProtoSelect->setObjectName(QString::fromUtf8("ipProtoSelect"));
    this->ipProtoSelect->setSizePolicy(fixedSizePolicy);
    this->ipProtoSelect->addItems(this->ipProtocols);
    gridLayout->addWidget(ipProtoSelect, 1, 2, 1, 1);

    /* source address */
    QLabel *ipSourceLabel = new QLabel(this->tabIp);
    ipSourceLabel->setObjectName(QString::fromUtf8("ipSourceLabel"));
    ipSourceLabel->setText(QString::fromUtf8("Source address: "));
    gridLayout->addWidget(ipSourceLabel, 2, 0, 1, 1);

    this->ipSourceNBox = new QCheckBox(this->tabIp);
    this->ipSourceNBox->setObjectName(QString::fromUtf8("ipSourceNBox"));
    this->ipSourceNBox->setText(QString::fromUtf8("!"));
    gridLayout->addWidget(this->ipSourceNBox, 2, 1, 1, 1);

    this->ipSourceEdit = new QLineEdit(this->tabIp);
    this->ipSourceEdit->setObjectName(QString::fromUtf8("ipSourceEdit"));
    this->ipSourceEdit->setValidator(addrValidator);
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
    gridLayout->addWidget(this->ipSourceMaskEdit, 2, 4, 1, 1);

    /* destination address */
    QLabel *ipDestLabel = new QLabel(this->tabIp);
    ipDestLabel->setObjectName(QString::fromUtf8("ipDestLabel"));
    ipDestLabel->setText(QString::fromUtf8("Destination address: "));
    gridLayout->addWidget(ipDestLabel, 3, 0, 1, 1);

    this->ipDestNBox = new QCheckBox(this->tabIp);
    this->ipDestNBox->setObjectName(QString::fromUtf8("ipDestNBox"));
    this->ipDestNBox->setText(QString::fromUtf8("!"));
    gridLayout->addWidget(this->ipDestNBox, 3, 1, 1, 1);

    this->ipDestEdit = new QLineEdit(this->tabIp);
    this->ipDestEdit->setObjectName(QString::fromUtf8("ipDestEdit"));
    this->ipDestEdit->setValidator(addrValidator);
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
    gridLayout->addWidget(this->ipDestMaskEdit, 3, 4, 1, 1);

    /* Vertical spacer to the end */
    QSpacerItem *verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    gridLayout->addItem(verticalSpacer, 4, 2, 1, 1);

    this->addTab(this->tabIp, QString::fromUtf8("Net layer"));
}

