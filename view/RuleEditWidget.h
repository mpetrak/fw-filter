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

class RuleEditWidget : public QTabWidget {
public:
    RuleEditWidget(QWidget *parent);
    virtual ~RuleEditWidget();
private:
    /* Tabs */
    QWidget *tabGeneral;
    QWidget *tabIp;
    
    /* General components */
    QLineEdit *nameEdit;
    QLabel *numberLabel;

};

#endif	/* RULEEDITWIDGET_H */

