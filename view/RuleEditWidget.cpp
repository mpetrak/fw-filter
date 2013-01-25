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

#include "RuleEditWidget.h"

RuleEditWidget::RuleEditWidget(QWidget *parent) : QTabWidget(parent) {
    /* set own tab widget */
    this->setGeometry(QRect(230, 10, 511, 531));
    this->setObjectName(QString::fromUtf8("ruleEditWidget"));

    this->actions.append(QString::fromUtf8("ACCEPT"));
    this->actions.append(QString::fromUtf8("DROP"));
    
    this->interfaces = new NetInterfaces();

    /* create tabs */
    this->setupGeneralWidget();
    this->setupEbWidget();

    this->tabIp = new QWidget();
    this->tabIp->setObjectName(QString::fromUtf8("tabIp"));
    this->addTab(this->tabIp, QString::fromUtf8("Net layer"));

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

    this->inInterfaceSelect = new QComboBox(this->tabEb);
    this->inInterfaceSelect->setObjectName(QString::fromUtf8("inInterfaceSelect"));
    this->inInterfaceSelect->setSizePolicy(fixedSizePolicy);
    this->inInterfaceSelect->addItems(this->interfaces->getIfList());
    gridLayout->addWidget(this->inInterfaceSelect, 1, 2, 1, 1);

    /* output interface */
    QLabel *outInterfaceLabel = new QLabel(this->tabEb);
    outInterfaceLabel->setObjectName(QString::fromUtf8("outInterfaceLabel"));
    outInterfaceLabel->setText(QString::fromUtf8("Output interface: "));
    gridLayout->addWidget(outInterfaceLabel, 2, 0, 1, 1);

    this->outInterfaceSelect = new QComboBox(this->tabEb);
    this->outInterfaceSelect->setObjectName(QString::fromUtf8("outInterfaceSelect"));
    this->outInterfaceSelect->setSizePolicy(fixedSizePolicy);
    this->outInterfaceSelect->addItems(this->interfaces->getIfList());
    gridLayout->addWidget(this->outInterfaceSelect, 2, 2, 1, 1);

    /* source address */
    QLabel *macSourceLabel = new QLabel(this->tabEb);
    macSourceLabel->setObjectName(QString::fromUtf8("macSourceLabel"));
    macSourceLabel->setText(QString::fromUtf8("Source address: "));
    gridLayout->addWidget(macSourceLabel, 3, 0, 1, 1);

    this->macSourceEdit = new QLineEdit(this->tabEb);
    this->macSourceEdit->setObjectName(QString::fromUtf8("macSourceEdit"));
    gridLayout->addWidget(this->macSourceEdit, 3, 2, 1, 1);

    /* destination address */
    QLabel *macDestLabel = new QLabel(this->tabEb);
    macDestLabel->setObjectName(QString::fromUtf8("macDestLabel"));
    macDestLabel->setText(QString::fromUtf8("Destination address: "));
    gridLayout->addWidget(macDestLabel, 4, 0, 1, 1);

    this->macDestEdit = new QLineEdit(this->tabEb);
    this->macDestEdit->setObjectName(QString::fromUtf8("macDestEdit"));
    //macDestEdit->setSizePolicy(fixedSizePolicy);
    gridLayout->addWidget(this->macDestEdit, 4, 2, 1, 1);

    /* Vertical spacer to the end */
    QSpacerItem *verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    gridLayout->addItem(verticalSpacer, 5, 2, 1, 1);

    /* add widget as a tab */
    this->addTab(this->tabEb, QString::fromUtf8("Link layer"));
}

