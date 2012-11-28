/* 
 * File:   FilterRule.h
 * Author: petris
 *
 * Created on 28. listopad 2012, 17:26
 */

#ifndef FILTERRULE_H
#define	FILTERRULE_H

class FilterRule {
public:
    FilterRule(int number);
    virtual ~FilterRule();
    
    void setNumber(int number);
    int  getNumber();
private:
    int number;
    
};

#endif	/* FILTERRULE_H */

