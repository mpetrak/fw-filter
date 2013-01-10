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
    /* Constructors, destructor */
    FilterRule();
    FilterRule(int number);
    virtual ~FilterRule();

    /* Other methods */
    /**
     * Write all rules parameters to given data stream.
     * Using in model with manipulation.
     * @param stream data stream to write to
     */
    void toStream(QDataStream *stream);

    /**
     * Read all rules parameters from given data stream.
     * Using in model with manipulation.
     * @param stream data stream to read from
     */
    void fromStream(QDataStream *stream);

    /* Setters and getters */
    void setNumber(int number);
    int getNumber();
    void setName(QString name);
    QString getName();
private:
    /** number of rule */
    int number;
    /** name of rule */
    QString name;

};
/* register class as metatype to be used in QVariant object */
Q_DECLARE_METATYPE(FilterRule);

#endif	/* FILTERRULE_H */

