/* 
 * File:   FilterRule.h
 * Author: petris
 *
 * Created on 28. listopad 2012, 17:26
 */

#ifndef FILTERRULE_H
#define	FILTERRULE_H

#include <QString>
#include <QMetaType>

class FilterRule {
public:
    FilterRule();
    FilterRule(int number);
    virtual ~FilterRule();
    
    void setNumber(int number);
    int  getNumber();
    void setName(QString name);
    QString getName();
private:
    int number;
    QString name;
    
};
/* register class as metatype to be used in QVariant object */
Q_DECLARE_METATYPE(FilterRule);

#endif	/* FILTERRULE_H */

