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
#include <QtGui/QComboBox>
#include <QtGui/QTextEdit>
#include <QtGui/QCheckBox>

#include "../model/FilterRulesModel.h"
#include "../lib/NetInterfaces.h"
#include "../lib/OptionsLoader.h"

class RuleEditWidget : public QTabWidget {
    Q_OBJECT

public:   
    static const char* MAC_ADDRESS_REGEX;
    static const char* IPV4_ADDRESS_REGEX;
    static const char* IPV6_ADDRESS_REGEX;
    
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
    void setupEbWidget();
    void setupGeneralWidget();
    void setupIpWidget();

    /** List of rule actions */
    QStringList actions;
    
    /** List of system interfaces */
    QStringList interfaces;
    
    /** List of possible link protocols */
    QStringList ebProtocols;
    
    /** List of possible net protocols */
    QStringList ipProtocols;

    /** Rules list model pointer */
    FilterRulesModel *rulesModel;

    /* Tabs */
    /** Tab with general information */
    QWidget *tabGeneral;
    /** Tab with filtering information about 3rd layer */
    QWidget *tabIp;
    /** Tab with filtering information about 2nd layer */
    QWidget *tabEb;

    /* General edits */
    QLineEdit *nameEdit;
    QLabel *numberLabel;
    QComboBox *actionSelect;
    QTextEdit *descriptionEdit;

    /* EB edits */
    QCheckBox *macSourceNBox;
    QLineEdit *macSourceEdit;
    QLineEdit *macSourceMaskEdit;
    QCheckBox *macDestNBox;
    QLineEdit *macDestEdit;
    QLineEdit *macDestMaskEdit;
    QCheckBox *inInterfaceNBox;
    QComboBox *inInterfaceSelect;
    QCheckBox *outInterfaceNBox;
    QComboBox *outInterfaceSelect;
    QCheckBox *ebProtoNBox;
    QComboBox *ebProtoSelect;
    
    /* IP edits */
    QCheckBox *ipSourceNBox;
    QLineEdit *ipSourceEdit;
    QLineEdit *ipSourceMaskEdit;
    QCheckBox *ipDestNBox;
    QLineEdit *ipDestEdit;
    QLineEdit *ipDestMaskEdit;
    QCheckBox *ipProtoNBox;
    QComboBox *ipProtoSelect;

};

#endif	/* RULEEDITWIDGET_H */

