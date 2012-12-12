/* 
 * File:   FilterRulesModel.cpp
 * Author: petris
 * 
 * Created on 28. listopad 2012, 19:10
 */

#include "FilterRulesModel.h"

FilterRulesModel::FilterRulesModel() {
    //this->rulesList = new QList<FilterRule>();
    FilterRule *rule = new FilterRule(1);
    rule->setName("jedna");
    
    rulesList.append(*rule);
    
    rule = new FilterRule(2);
    rule->setName("dva");
    
    rulesList.append(*rule);
}

FilterRulesModel::~FilterRulesModel() {
}

int FilterRulesModel::rowCount(const QModelIndex& parent) const {
    return rulesList.count();
}

QVariant FilterRulesModel::data(const QModelIndex& index, int role) const {
    
    if(!index.isValid()) {
        return QVariant();
    }
    
    if (index.row() >= rulesList.count()) {
        return QVariant();
    }  
    
    if (role == Qt::DisplayRole) {
        FilterRule rule = rulesList.at(index.row());
        return tr("#%1 %2").arg(QString::number(rule.getNumber()), rule.getName());
    } else {
        
        return QVariant();
    }
}

QVariant FilterRulesModel::headerData(int section, Qt::Orientation orientation, int role) const {
    
}

