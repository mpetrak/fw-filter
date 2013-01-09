/* 
 * File:   FilterRulesModel.cpp
 * Author: petris
 * 
 * Created on 28. listopad 2012, 19:10
 */

#include <qt4/QtCore/qstringlist.h>

#include "FilterRulesModel.h"

FilterRulesModel::FilterRulesModel() {
    //this->rulesList = new QList<FilterRule>();
//    FilterRule *rule = new FilterRule(1);
//    rule->setName("jedna");
//
//    rulesList.append(*rule);
//
//    rule = new FilterRule(2);
//    rule->setName("dva");
//
//    rulesList.append(*rule);
    rulesList.append(QString("jedna"));
    rulesList.append(QString("dva"));
    rulesList.append(QString("tri"));
}

FilterRulesModel::~FilterRulesModel() {
}

int FilterRulesModel::rowCount(const QModelIndex& parent) const {
    return rulesList.count();
}

QVariant FilterRulesModel::data(const QModelIndex& index, int role) const {

    if (!index.isValid() || index.row() >= rulesList.count()) {
        return QVariant();
    }

    if (role == Qt::DisplayRole) {
        //FilterRule rule = rulesList.at(index.row());
        //return tr("#%1 %2").arg(QString::number(rule.getNumber()), rule.getName());
        return rulesList.at(index.row());
    } else {

        return QVariant();
    }
}

QVariant FilterRulesModel::headerData(int section, Qt::Orientation orientation, int role) const {

    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orientation == Qt::Horizontal) {
        return QString("Column %1").arg(section);
    } else {
        return QString("Row %1").arg(section);
    }
}

Qt::ItemFlags FilterRulesModel::flags(const QModelIndex& index) const {
    
    Qt::ItemFlags defaultFlags = QAbstractListModel::flags(index);

    if (index.isValid()) {
        /* valid index is enabled for drag (not replacing) */
        return Qt::ItemIsDragEnabled | defaultFlags;
    } else {
        /* invalid index is enabled for drop */
        return Qt::ItemIsDropEnabled | defaultFlags;
    }

}

bool FilterRulesModel::setData(const QModelIndex& index, const QVariant& value, int role) {

    /* enabled for display role because of drag and drop */
    if (index.isValid() && role == Qt::DisplayRole) {      
        rulesList.replace(index.row(), value.toString());
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

bool FilterRulesModel::insertRows(int position, int rows, const QModelIndex &parent) {
     beginInsertRows(QModelIndex(), position, position+rows-1);

     for (int row = 0; row < rows; ++row) {
         /* insert new rule */
         rulesList.insert(position, "New " + row);
     }

     endInsertRows();
     return true;
 }

bool FilterRulesModel::removeRows(int position, int rows, const QModelIndex &parent)
 {
     beginRemoveRows(QModelIndex(), position, position+rows-1);

     for (int row = 0; row < rows; ++row) {
         rulesList.removeAt(position);
     }

     endRemoveRows();
     return true;
 }

Qt::DropActions FilterRulesModel::supportedDropActions() const {
    return Qt::CopyAction | Qt::MoveAction;
}

QMimeData *FilterRulesModel::mimeData(const QModelIndexList &indexes) const {
    
    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;
    
    QDataStream writeStream(&encodedData, QIODevice::WriteOnly);
    
    foreach(const QModelIndex &index, indexes) {
        if(index.isValid()) {
            QString text = data(index, Qt::DisplayRole).toString();
            writeStream << text;
        }
    }
    
    mimeData->setData("application/vnd.text.list", encodedData);
    return mimeData; 
}

bool FilterRulesModel::dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent) {
    
    if(action == Qt::IgnoreAction) {
        return true;
    }   
    if(!data->hasFormat("application/vnd.text.list")) {
        return false;
    }
    if (column > 0) {
        return false;
    }
    
    int beginRow;
    if(row != -1) {
        beginRow = row;
    }  
    else if(parent.isValid()) {
        beginRow = parent.row();
    }
    else {
        beginRow = rowCount(QModelIndex());
    }
    
    /* decoding imported data */
    QByteArray encodedData = data->data("application/vnd.text.list");
    QDataStream readStream(&encodedData, QIODevice::ReadOnly);
    QStringList newItems;
    int rows = 0;
    
    while(!readStream.atEnd()) {
        QString text;
        readStream >> text;
        newItems << text;
        rows++;
    }
    
    insertRows(beginRow, rows, QModelIndex());
    foreach(const QString &text, newItems) {
        QModelIndex idx = index(beginRow, 0, QModelIndex());
        setData(idx, text, Qt::DisplayRole);
        beginRow++;
    }
    
    return true;
}

QStringList FilterRulesModel::mimeTypes() const {
     QStringList types;
     types << "application/vnd.text.list";
     return types;
 }
