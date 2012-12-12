/* 
 * File:   FilterRule.h
 * Author: petris
 *
 * Created on 28. listopad 2012, 17:26
 */

#ifndef FILTERRULE_H
#define	FILTERRULE_H

#include <QString>

class FilterRule {
public:
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

#endif	/* FILTERRULE_H */

