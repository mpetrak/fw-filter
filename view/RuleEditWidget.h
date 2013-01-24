/* 
 * File:   ruleEditWidget.h
 * Author: petris
 *
 * Created on 10. leden 2013, 13:10
 */

#ifndef RULEEDITWIDGET_H
#define	RULEEDITWIDGET_H

#include <QtGui/QTabWidget>
#include <QtGui/QLineEdit>
#include <QtGui/QLabel>
#include "../model/FilterRulesModel.h"

class RuleEditWidget : public QTabWidget {
    Q_OBJECT

public:
    RuleEditWidget(QWidget *parent);
    virtual ~RuleEditWidget();

    /**
     * Setting rules list model for interaction with rules selector.
     * Signal sends index to slot and widget get rule from sended index.
     * @param model rules list model pointer
     */
    void setRulesModel(FilterRulesModel *model);

public slots:
    /**
     * Public slot for updating edit widget with actual selected rule.
     * @param index index of selected rule in list of rules
     */
    void ruleSelected(QModelIndex index);
    
    void ruleSave(QModelIndex index);

private:
    /** rules list model pointer */
    FilterRulesModel *rulesModel;

    /* Tabs */
    /** Tab with general information */
    QWidget *tabGeneral;
    /** Tab with filtering information about 3rd layer */
    QWidget *tabIp;

    /* General components */
    QLineEdit *nameEdit;
    QLabel *numberLabel;

};

#endif	/* RULEEDITWIDGET_H */

