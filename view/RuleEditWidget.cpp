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

RuleEditWidget::RuleEditWidget(QWidget *parent) : QTabWidget(parent) {
    /* set own tab widget */
    this->setGeometry(QRect(230, 10, 511, 531));
    this->setObjectName(QString::fromUtf8("ruleEditWidget"));

    this->actions.append(QString::fromUtf8("ACCEPT"));
    this->actions.append(QString::fromUtf8("DROP"));
    //this->actions.append(QString::fromUtf8("CONTINUE"));
    
    NetInterfaces *netIfs = new NetInterfaces();
    this->interfaces = netIfs->getIfList();
    free(netIfs);

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
        this->outInterfaceSelect->setCurrentIndex(interfaces.indexOf(rule.getOutInterface()));
        this->macSourceEdit->setText(rule.getEbSource());
        this->macDestEdit->setText(rule.getEbDest());
    }
}

void RuleEditWidget::ruleSave(QModelIndex index) {

    if (index.isValid()) {
        FilterRule rule = this->rulesModel->getRule(index.row());

        rule.setName(this->nameEdit->text());
        rule.setDescription(this->descriptionEdit->toPlainText());
        rule.setAction(this->actionSelect->currentText());
        rule.setInInterface(this->inInterfaceSelect->currentText());
        rule.setOutInterface(this->outInterfaceSelect->currentText());
        rule.setEbSource(this->macSourceEdit->text());
        rule.setEbDest(this->macDestEdit->text());

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

    //    QSpacerItem *horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    //    gridLayout->addItem(horizontalSpacer, 1, 3, 1, 1);

    /* action */
    QLabel *actionLabel = new QLabel(this->tabGeneral);
    actionLabel->setObjectName(QString::fromUtf8("actionLabel"));
    actionLabel->setText(QString::fromUtf8("Action: "));
    gridLayout->addWidget(actionLabel, 2, 0, 1, 1);

    this->actionSelect = new QComboBox(this->tabGeneral);
    this->actionSelect->setObjectName(QString::fromUtf8("actionSelect"));
    this->actionSelect->setSizePolicy(fixedSizePolicy);
    this->actionSelect->addItems(this->actions);
    gridLayout->addWidget(this->actionSelect, 2, 2, 1, 1);

    QLabel *descriptionLabel = new QLabel(this->tabGeneral);
    descriptionLabel->setObjectName(QString::fromUtf8("descriptionLabel"));
    descriptionLabel->setText(QString::fromUtf8("Description: "));
    gridLayout->addWidget(descriptionLabel, 3, 0, 1, 1);

    this->descriptionEdit = new QTextEdit(this->tabGeneral);
    this->descriptionEdit->setObjectName(QString::fromUtf8("descriptionEdit"));
    gridLayout->addWidget(this->descriptionEdit, 4, 2, 1, 1);

    /* vertical space to the end */
    QSpacerItem *verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    gridLayout->addItem(verticalSpacer, 5, 2, 1, 1);

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

    /* source address */
    QLabel *macSourceLabel = new QLabel(this->tabEb);
    macSourceLabel->setObjectName(QString::fromUtf8("macSourceLabel"));
    macSourceLabel->setText(QString::fromUtf8("Source address: "));
    gridLayout->addWidget(macSourceLabel, 3, 0, 1, 1);
    
    this->macSourceNBox = new QCheckBox(this->tabEb);
    this->macSourceNBox->setObjectName(QString::fromUtf8("macSourceNBox"));
    this->macSourceNBox->setText(QString::fromUtf8("!"));
    gridLayout->addWidget(this->macSourceNBox, 3, 1, 1, 1);

    this->macSourceEdit = new QLineEdit(this->tabEb);
    this->macSourceEdit->setObjectName(QString::fromUtf8("macSourceEdit"));
    gridLayout->addWidget(this->macSourceEdit, 3, 2, 1, 1);
    
    /* source mask */
    QLabel *macSourceMaskLabel = new QLabel(this->tabEb);
    macSourceMaskLabel->setObjectName(QString::fromUtf8("macSourceMaskLabel"));
    macSourceMaskLabel->setText(QString::fromUtf8("/"));
    gridLayout->addWidget(macSourceMaskLabel, 3, 3, 1, 1);
    
    this->macSourceMaskEdit = new QLineEdit(this->tabEb);
    this->macSourceMaskEdit->setObjectName(QString::fromUtf8("macSourceMaskEdit"));
    gridLayout->addWidget(this->macSourceMaskEdit, 3, 4, 1, 1);

    /* destination address */
    QLabel *macDestLabel = new QLabel(this->tabEb);
    macDestLabel->setObjectName(QString::fromUtf8("macDestLabel"));
    macDestLabel->setText(QString::fromUtf8("Destination address: "));
    gridLayout->addWidget(macDestLabel, 4, 0, 1, 1);
    
    this->macDestNBox = new QCheckBox(this->tabEb);
    this->macDestNBox->setObjectName(QString::fromUtf8("macDestNBox"));
    this->macDestNBox->setText(QString::fromUtf8("!"));
    gridLayout->addWidget(this->macDestNBox, 4, 1, 1, 1);

    this->macDestEdit = new QLineEdit(this->tabEb);
    this->macDestEdit->setObjectName(QString::fromUtf8("macDestEdit"));
    gridLayout->addWidget(this->macDestEdit, 4, 2, 1, 1);
    
    /* destination mask */
    QLabel *macDestMaskLabel = new QLabel(this->tabEb);
    macDestMaskLabel->setObjectName(QString::fromUtf8("macDestMaskLabel"));
    macDestMaskLabel->setText(QString::fromUtf8("/"));
    gridLayout->addWidget(macDestMaskLabel, 4, 3, 1, 1);
    
    this->macDestMaskEdit = new QLineEdit(this->tabEb);
    this->macDestMaskEdit->setObjectName(QString::fromUtf8("macDestMaskEdit"));
    gridLayout->addWidget(this->macDestMaskEdit, 4, 4, 1, 1);

    /* Vertical spacer to the end */
    QSpacerItem *verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    gridLayout->addItem(verticalSpacer, 5, 2, 1, 1);

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
//    QSizePolicy fixedSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
//    fixedSizePolicy.setHorizontalStretch(0);
//    fixedSizePolicy.setVerticalStretch(0);
    
    /* validator for mask fields */
    QIntValidator *maskValidator = new QIntValidator(this->tabIp);
    maskValidator->setRange(0, 64);

    /* source address */
    QLabel *ipSourceLabel = new QLabel(this->tabIp);
    ipSourceLabel->setObjectName(QString::fromUtf8("ipSourceLabel"));
    ipSourceLabel->setText(QString::fromUtf8("Source address: "));
    gridLayout->addWidget(ipSourceLabel, 1, 0, 1, 1);
    
    this->ipSourceNBox = new QCheckBox(this->tabIp);
    this->ipSourceNBox->setObjectName(QString::fromUtf8("ipSourceNBox"));
    this->ipSourceNBox->setText(QString::fromUtf8("!"));
    gridLayout->addWidget(this->ipSourceNBox, 1, 1, 1, 1);

    this->ipSourceEdit = new QLineEdit(this->tabIp);
    this->ipSourceEdit->setObjectName(QString::fromUtf8("ipSourceEdit"));
    gridLayout->addWidget(this->ipSourceEdit, 1, 2, 1, 1);
    
    /* source mask */
    QLabel *ipSourceMaskLabel = new QLabel(this->tabIp);
    ipSourceMaskLabel->setObjectName(QString::fromUtf8("ipSourceMaskLabel"));
    ipSourceMaskLabel->setText(QString::fromUtf8("/"));
    gridLayout->addWidget(ipSourceMaskLabel, 1, 3, 1, 1);
    
    this->ipSourceMaskEdit = new QLineEdit(this->tabIp);
    this->ipSourceMaskEdit->setObjectName(QString::fromUtf8("ipSourceMaskEdit"));
    this->ipSourceMaskEdit->setValidator(maskValidator);
    this->ipSourceMaskEdit->setFixedWidth(MASK_EDIT_WIDTH);
    gridLayout->addWidget(this->ipSourceMaskEdit, 1, 4, 1, 1);

    /* destination address */
    QLabel *ipDestLabel = new QLabel(this->tabIp);
    ipDestLabel->setObjectName(QString::fromUtf8("ipDestLabel"));
    ipDestLabel->setText(QString::fromUtf8("Destination address: "));
    gridLayout->addWidget(ipDestLabel, 2, 0, 1, 1);
    
    this->ipDestNBox = new QCheckBox(this->tabIp);
    this->ipDestNBox->setObjectName(QString::fromUtf8("ipDestNBox"));
    this->ipDestNBox->setText(QString::fromUtf8("!"));
    gridLayout->addWidget(this->ipDestNBox, 2, 1, 1, 1);

    this->ipDestEdit = new QLineEdit(this->tabIp);
    this->ipDestEdit->setObjectName(QString::fromUtf8("ipDestEdit"));
    gridLayout->addWidget(this->ipDestEdit, 2, 2, 1, 1);
    
    /* destination mask */
    QLabel *ipDestMaskLabel = new QLabel(this->tabIp);
    ipDestMaskLabel->setObjectName(QString::fromUtf8("ipDestMaskLabel"));
    ipDestMaskLabel->setText(QString::fromUtf8("/"));
    gridLayout->addWidget(ipDestMaskLabel, 2, 3, 1, 1);
    
    this->ipDestMaskEdit = new QLineEdit(this->tabIp);
    this->ipDestMaskEdit->setObjectName(QString::fromUtf8("ipDestMaskEdit"));
    this->ipDestMaskEdit->setValidator(maskValidator);
    this->ipDestMaskEdit->setFixedWidth(MASK_EDIT_WIDTH);
    gridLayout->addWidget(this->ipDestMaskEdit, 2, 4, 1, 1);

    /* Vertical spacer to the end */
    QSpacerItem *verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    gridLayout->addItem(verticalSpacer, 3, 2, 1, 1);
    
    this->addTab(this->tabIp, QString::fromUtf8("Net layer"));
}

