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

#include "../model/FilterRulesModel.h"
#include "../lib/NetInterfaces.h"
#include "../lib/OptionsLoader.h"
#include "../lib/RulesPusher.h"

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
    static const char* MAC_ADDRESS_REGEX;
    static const char* IPV4_ADDRESS_REGEX;
    static const char* IPV6_ADDRESS_REGEX;
    static const int NORMAL_OPTION_INDEX;
    static const int NEGATION_OPTION_INDEX;

    void setupEbWidget();
    void setupGeneralWidget();
    void setupIpWidget();

    QComboBox *makeNegationSelect(QWidget *parent);

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
    QComboBox *macSourceNegSelect;
    QLineEdit *macSourceEdit;
    QLineEdit *macSourceMaskEdit;
    QComboBox *macDestNegSelect;
    QLineEdit *macDestEdit;
    QLineEdit *macDestMaskEdit;
    QComboBox *inInterfaceNegSelect;
    QComboBox *inInterfaceSelect;
    QComboBox *outInterfaceNegSelect;
    QComboBox *outInterfaceSelect;
    QComboBox *ebProtoNegSelect;
    QComboBox *ebProtoSelect;

    /* IP edits */
    QComboBox *ipSourceNegSelect;
    QLineEdit *ipSourceEdit;
    QLineEdit *ipSourceMaskEdit;
    QComboBox *ipDestNegSelect;
    QLineEdit *ipDestEdit;
    QLineEdit *ipDestMaskEdit;
    QComboBox *ipProtoNegSelect;
    QComboBox *ipProtoSelect;

};

#endif	/* RULEEDITWIDGET_H */

