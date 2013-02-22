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
    static const QString OPTION_VALUE_UNSPECIFIED;
    static const int INT_VALUE_UNSPECIFIED;
    
    /* Constructors, destructor */
    FilterRule();
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
    QString getEbDestMask() const;
    void setEbDestMask(QString ebDestMask);
    bool isEbDestNeg() const;
    void setEbDestNeg(bool ebDestNeg);
    QString getEbSource() const;
    void setEbSource(QString EbSource);
    QString getEbSourceMask() const;
    void setEbSourceMask(QString ebSourceMask);
    bool isEbSourceNeg() const;
    void setEbSourceNeg(bool ebSourceNeg);
    QString getInInterface() const;
    void setInInterface(QString inInterface);
    bool isInInterfaceNeg() const;
    void setInInterfaceNeg(bool inInterfaceNeg);
    QString getOutInterface() const;
    void setOutInterface(QString outInterface);
     bool isOutInterfaceNeg() const;
    void setOutInterfaceNeg(bool outInterfaceNeg);
    QString getEbProtocol() const;
    void setEbProtocol(QString ebProtocol);
    bool isEbProtocolNeg() const;
    void setEbProtocolNeg(bool ebProtocolNeg);
    QString getIpProtocol() const;
    void setIpProtocol(QString ipProtocol);
    bool isIpProtocolNeg() const;
    void setIpProtocolNeg(bool ipProtocolNeg);
    QString getIpDest() const;
    void setIpDest(QString ipDest);
    short getIpDestMask() const;
    void setIpDestMask(short ipDestMask);
    bool isIpDestNeg() const;
    void setIpDestNeg(bool ipDestNeg);
    QString getIpSource() const;
    void setIpSource(QString ipSource);
    short getIpSourceMask() const;
    void setIpSourceMask(short ipSourceMask);
    bool isIpSourceNeg() const;
    void setIpSourceNeg(bool ipSourceNeg);
    bool isIpFragment() const;
    void setIpFragment(bool ipFragment);

private:
    /** number of rule */
    int number;
    /** Name of rule */
    QString name;
    /** Rule description */
    QString description;

    /** Input interface */
    QString inInterface;
    /** Input interface negation */
    bool inInterfaceNeg;
    /** Output interface */
    QString outInterface;
    /** Output interface negation */
    bool outInterfaceNeg;
    /** Link layer protocol or length */
    QString ebProtocol;
    /** Link layer rotocol negation */
    bool ebProtocolNeg;
    /** Link layer source address */
    QString ebSource;
    /** Link layer source address mask */
    QString ebSourceMask;
    /** Link layer source address negation */
    bool ebSourceNeg;
    /** Link layer destination address */
    QString ebDest;
    /** Link layer destination address mask */
    QString ebDestMask;
    /** Link layer destination address negation */
    bool ebDestNeg;

    /** Type of ip protocol */
    QString ipProtocol;
    /** Ip protocol negation */
    bool ipProtocolNeg;
    /** IP source address */
    QString ipSource;
    /** IP source mask */
    short ipSourceMask;
    /** IP source address negation */
    bool ipSourceNeg;
    /** IP destination address */
    QString ipDest;
    /** IP destination mask*/
    short ipDestMask;
    /** IP destintation address negation */
    bool ipDestNeg;
    /** Fragmented packet */
    bool ipFragment;

    /** Action of matched packet */
    QString action;


};
/* register class as metatype to be used in QVariant object */
Q_DECLARE_METATYPE(FilterRule);

#endif	/* FILTERRULE_H */

