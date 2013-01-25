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
    /* Constants */
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
    int getNumber() const;
    void setName(QString name);
    QString getName() const;
    QString getAction() const;
    void setAction(QString action);
    QString getDescription() const;
    void setDescription(QString description);
    QString getEbDest() const;
    void setEbDest(QString EbDest);
    QString getEbSource() const;
    void setEbSource(QString EbSource);

private:
    /** number of rule */
    int number;
    /** Name of rule */
    QString name;
    /** Rule description */
    QString description;
    
    /** Link layer source address */
    QString ebSource;
    /** Link layer destination address */
    QString ebDest;
    
    /** Type of ip protocol */
    QString IpProtocol;
    /** IP source address */
    QString IpSource;
    /** IP source mask */
    ushort IpSourceMask;
    /** IP destination address */
    QString IpDest;
    /** IP destination mask*/
    ushort IpDestMask;

    /** Action of matched packet */
    QString action;


};
/* register class as metatype to be used in QVariant object */
Q_DECLARE_METATYPE(FilterRule);

#endif	/* FILTERRULE_H */

