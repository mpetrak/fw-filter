/* 
 * File:   ruleEditWidget.cpp
 * Author: petris
 * 
 * Created on 10. leden 2013, 13:10
 */

#include <qt4/QtCore/qabstractitemmodel.h>
#include <qt4/QtGui/qgridlayout.h>
#include <qt4/QtGui/qcombobox.h>

#include "RuleEditWidget.h"
#include "qstring.h"

RuleEditWidget::RuleEditWidget(QWidget *parent) : QTabWidget(parent) {
    /* set own tab widget */
    this->setGeometry(QRect(230, 10, 511, 531));
    this->setObjectName(QString::fromUtf8("ruleEditWidget"));

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
        //this->numberLabel->setText() = rule.getNumber();
    }
}

void RuleEditWidget::ruleSave(QModelIndex index) {

    if (index.isValid()) {
        FilterRule rule = this->rulesModel->getRule(index.row());

        rule.setName(this->nameEdit->text());

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

    this->nameEdit = new QLineEdit(this->tabGeneral);
    this->nameEdit->setObjectName(QString::fromUtf8("nameEdit"));
    gridLayout->addWidget(this->nameEdit, 1, 2, 1, 1);

    QLabel *nameLabel = new QLabel(this->tabGeneral);
    nameLabel->setObjectName(QString::fromUtf8("nameLabel"));
    nameLabel->setText(QString::fromUtf8("Rule name: "));
    gridLayout->addWidget(nameLabel, 1, 0, 1, 1);

    QSpacerItem *horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    gridLayout->addItem(horizontalSpacer, 1, 3, 1, 1);

    QSpacerItem *verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    gridLayout->addItem(verticalSpacer, 2, 2, 1, 1);

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

    /* source address */
    QLabel *macSourceLabel = new QLabel(this->tabEb);
    macSourceLabel->setObjectName(QString::fromUtf8("macSourceLabel"));
    macSourceLabel->setText(QString::fromUtf8("Source address: "));
    gridLayout->addWidget(macSourceLabel, 1, 0, 1, 1);
    
    this->macSourceEdit = new QLineEdit(this->tabEb);
    this->macSourceEdit->setObjectName(QString::fromUtf8("macSourceEdit"));
    gridLayout->addWidget(this->macSourceEdit, 1, 2, 1, 1);

    /* destination address */
    QLabel *macDestLabel = new QLabel(this->tabEb);
    macDestLabel->setObjectName(QString::fromUtf8("macDestLabel"));
    macDestLabel->setText(QString::fromUtf8("Destination address: "));
    gridLayout->addWidget(macDestLabel, 2, 0, 1, 1);
    
    this->macDestEdit = new QLineEdit(this->tabEb);
    this->macDestEdit->setObjectName(QString::fromUtf8("macDestEdit"));
    //macDestEdit->setSizePolicy(fixedSizePolicy);
    gridLayout->addWidget(this->macDestEdit, 2, 2, 1, 1);
    
    /* input interface */
    QLabel *inInterfaceLabel = new QLabel(this->tabEb);
    inInterfaceLabel->setObjectName(QString::fromUtf8("inInterfaceLabel"));
    inInterfaceLabel->setText(QString::fromUtf8("Input interface: "));
    gridLayout->addWidget(inInterfaceLabel, 3, 0, 1, 1);
    
    this->inInterfaceSelect = new QComboBox(this->tabEb);
    this->inInterfaceSelect->setObjectName(QString::fromUtf8("inInterfaceSelect"));
    this->inInterfaceSelect->setSizePolicy(fixedSizePolicy);
    gridLayout->addWidget(this->inInterfaceSelect, 3, 2, 1, 1);
    
    /* output interface */
    QLabel *outInterfaceLabel = new QLabel(this->tabEb);
    outInterfaceLabel->setObjectName(QString::fromUtf8("outInterfaceLabel"));
    outInterfaceLabel->setText(QString::fromUtf8("Output interface: "));
    gridLayout->addWidget(outInterfaceLabel, 4, 0, 1, 1);
    
    this->outInterfaceSelect = new QComboBox(this->tabEb);
    this->outInterfaceSelect->setObjectName(QString::fromUtf8("outInterfaceSelect"));
    this->outInterfaceSelect->setSizePolicy(fixedSizePolicy);
    gridLayout->addWidget(this->outInterfaceSelect, 4, 2, 1, 1);

    /* Vertical spacer to the end */
    QSpacerItem *verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    gridLayout->addItem(verticalSpacer, 5, 2, 1, 1);

    /* add widget as a tab */
    this->addTab(this->tabEb, QString::fromUtf8("Link layer"));
}

