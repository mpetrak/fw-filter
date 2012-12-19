/* 
 * File:   FilterRulesModel.h
 * Author: petris
 *
 * Created on 28. listopad 2012, 19:10
 */

#ifndef FILTERRULESMODEL_H
#define	FILTERRULESMODEL_H

#include <QAbstractListModel>
#include <QStringList>
#include <QMimeData>

#include "FilterRule.h"

class FilterRulesModel : public QAbstractListModel {
public:
    FilterRulesModel();
    ~FilterRulesModel();
    
    int rowCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());
    Qt::DropActions supportedDropActions() const;
private:
    QStringList rulesList;

};

#endif	/* FILTERRULESMODEL_H */

