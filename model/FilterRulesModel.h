/* 
 * File:   FilterRulesModel.h
 * Author: petris
 *
 * Created on 28. listopad 2012, 19:10
 */

#ifndef FILTERRULESMODEL_H
#define	FILTERRULESMODEL_H

#include <QAbstractListModel>

#include "FilterRule.h"

class FilterRulesModel : public QAbstractListModel {
public:
    FilterRulesModel();
    ~FilterRulesModel();
    
    int rowCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
private:
    QList<FilterRule> rulesList;

};

#endif	/* FILTERRULESMODEL_H */

