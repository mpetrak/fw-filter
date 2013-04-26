
#ifndef NEGATIONCOMBOBOX_H
#define	NEGATIONCOMBOBOX_H

#include <QComboBox>

class NegationComboBox : public QComboBox {
    Q_OBJECT

public:
    static const int NORMAL_INDEX;
    static const int NEGATION_INDEX;

    NegationComboBox(QWidget *parent);
    virtual ~NegationComboBox();

    /**
     * Setting value, that means disable itself
     * @param disableOption disable itself value
     */
    void setDisableOption(QString disableOption);

public slots:
    /**
     * Checking, if given value match disable value and enable/disable itself.
     * @param optionValue value to match
     */
    void checkForDisable(QString optionValue);

private:

    /** disable itself value */
    QString disableOption;
};

#endif	/* NEGATIONCOMBOBOX_H */

