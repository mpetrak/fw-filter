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
#include <QtGui/QMessageBox>

#include "FilterRule.h"
#include "../lib/RulesXML.h"

class FilterRulesModel : public QAbstractListModel {
    Q_OBJECT

public:
    /* constructors and destructors */
    FilterRulesModel();
    ~FilterRulesModel();

    /* model API */
    int rowCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());
    Qt::DropActions supportedDropActions() const;
    QStringList mimeTypes() const;
    QMimeData *mimeData(const QModelIndexList &indexes) const;
    bool dropMimeData(const QMimeData* data, Qt::DropAction action,
            int row, int column, const QModelIndex& parent);

    /* own methods */
    /**
     * Get instance of rule on given index.
     * @param index index of rule
     * @return rule object instance
     */
    FilterRule getRule(int index);
    
    /**
     * Get list of rules ordered by view component.
     * @return ordered list of rules
     */
    QList<FilterRule> getRulesList();
    
    /**
     * Reload rules from XML file.
     * Using library loader.
     */
    void reloadRules();

public slots:
    /**
     * Insert one new rule onto given position
     * @param index position
     */
    void newRule(int index);
    
    /**
     * Delete one rule from given position
     * @param index position
     */
    void deleteRule(int index);
    
    /**
     * Duplicate rule on position
     * @param index position
     */
    void duplicateRule(int index);
    
private:
    /** List of rules */
    QList<FilterRule> rulesList;

};

#endif	/* FILTERRULESMODEL_H */

