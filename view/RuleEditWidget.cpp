/* 
 * File:   ruleEditWidget.cpp
 * Author: petris
 * 
 * Created on 10. leden 2013, 13:10
 */

#include <qt4/QtCore/qabstractitemmodel.h>

#include "RuleEditWidget.h"

RuleEditWidget::RuleEditWidget(QWidget *parent) : QTabWidget(parent) {
    /* set own tab widget */
    this->setGeometry(QRect(230, 10, 511, 531));
    this->setObjectName(QString::fromUtf8("ruleEditWidget"));

    /* create and ad tabs */
    this->tabGeneral = new QWidget();
    this->tabGeneral->setObjectName(QString::fromUtf8("tabGeneral"));
    this->addTab(this->tabGeneral, QString::fromUtf8("General"));

    this->tabIp = new QWidget();
    this->tabIp->setObjectName(QString::fromUtf8("tabIp"));
    this->addTab(this->tabIp, QString::fromUtf8("IP"));

    this->numberLabel = new QLabel(tabGeneral);
    this->numberLabel->setText(QString::fromUtf8("Rule number"));
    this->nameEdit = new QLineEdit(tabGeneral);

    /* set first tab */
    this->setCurrentIndex(0);
}

RuleEditWidget::~RuleEditWidget() {
}

void RuleEditWidget::ruleSelected(QModelIndex index) {
    FilterRule rule = this->rulesModel->getRule(index.row());

    this->nameEdit->setText(rule.getName());
    //this->numberLabel->setText() = rule.getNumber();
}

void RuleEditWidget::setRulesModel(FilterRulesModel* model) {
    this->rulesModel = model;
}

