/* 
 * File:   FilterRulesModel.cpp
 * Author: petris
 * 
 * Created on 28. listopad 2012, 19:10
 */


#include "FilterRulesModel.h"

FilterRulesModel::FilterRulesModel() {

    RulesXML *xmlLoader = new RulesXML();
    QList<FilterRule> loaded = xmlLoader->loadRules();
    if (xmlLoader->isLoadError()) {
        QMessageBox::critical(NULL, QString::fromUtf8("Load error"),
                QString::fromUtf8("Error during loading filter rules. "
                "A list of rules will be empty."),
                QMessageBox::Ok, QMessageBox::Ok);
    } else {

        this->rulesList.append(loaded);
    }

    free(xmlLoader);
}

FilterRulesModel::~FilterRulesModel() {
}

QList<FilterRule> FilterRulesModel::getRulesList() {
    return this->rulesList;
}

FilterRule FilterRulesModel::getRule(int index) {
    /* return only if index is valid */
    if (index < rulesList.count()) {
        return rulesList.at(index);
    } else {
        return false;
    }
}

void FilterRulesModel::newRule(int index) {
    insertRows(index, 1, QModelIndex());
}

void FilterRulesModel::deleteRule(int index) {
    removeRows(index, 1, QModelIndex());
}

int FilterRulesModel::rowCount(const QModelIndex& parent) const {
    return rulesList.count();
}

QVariant FilterRulesModel::data(const QModelIndex& index, int role) const {

    if (!index.isValid() || index.row() >= rulesList.count()) {
        return QVariant();
    }

    if (role == Qt::DisplayRole) {
        FilterRule rule = rulesList.at(index.row());
        //return tr("#%1 %2").arg(QString::number(rule.getNumber()), rule.getName());
        return rule.getName();
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
        FilterRule rule = value.value<FilterRule > ();
        rulesList.replace(index.row(), rule);
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

bool FilterRulesModel::insertRows(int position, int rows, const QModelIndex &parent) {
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row) {
        /* insert new rule */
        FilterRule *rule = new FilterRule(position);
        rule->setName("New rule");
        rulesList.insert(position, *rule);
    }

    endInsertRows();
    return true;
}

bool FilterRulesModel::removeRows(int position, int rows, const QModelIndex &parent) {
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

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

    /* create mime data object, byte array and writing stream */
    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;
    QDataStream writeStream(&encodedData, QIODevice::WriteOnly);

    /* each rule from given indexes write to byte array */
    foreach(const QModelIndex &index, indexes) {
        if (index.isValid()) {
            FilterRule rule = rulesList.at(index.row());
            rule.toStream(&writeStream);
        }
    }

    /* set byte array as own mimetype data */
    mimeData->setData("application/vnd.filterrule.list", encodedData);
    return mimeData;
}

bool FilterRulesModel::dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent) {

    /* on ignore action return success */
    if (action == Qt::IgnoreAction) {
        return true;
    }
    /* accept only own mimetype */
    if (!data->hasFormat("application/vnd.filterrule.list")) {
        return false;
    }
    /* accept only valid column */
    if (column > 0) {
        return false;
    }

    /* compute begin row */
    int beginRow;
    if (row != -1) {
        beginRow = row;
    } else if (parent.isValid()) {
        beginRow = parent.row();
    } else {
        beginRow = rowCount(QModelIndex());
    }

    /* decoding imported data */
    QByteArray encodedData = data->data("application/vnd.filterrule.list");
    QDataStream readStream(&encodedData, QIODevice::ReadOnly);
    QList<FilterRule> newRules;
    int rows = 0;

    while (!readStream.atEnd()) {
        FilterRule *rule = new FilterRule();
        rule->fromStream(&readStream);
        newRules.append(*rule);
        rows++;
    }

    insertRows(beginRow, rows, QModelIndex());

    foreach(const FilterRule &rule, newRules) {
        QModelIndex idx = index(beginRow, 0, QModelIndex());
        setData(idx, QVariant::fromValue<FilterRule > (rule), Qt::DisplayRole);
        beginRow++;
    }

    return true;
}

QStringList FilterRulesModel::mimeTypes() const {
    QStringList types;
    types << "application/vnd.filterrule.list";
    return types;
}
