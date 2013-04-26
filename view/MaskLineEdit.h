#include <QLineEdit>

#ifndef MASKLINEEDIT_H
#define	MASKLINEEDIT_H

class MaskLineEdit : public QLineEdit {
    Q_OBJECT
public:
    MaskLineEdit(QWidget *parent);
    virtual ~MaskLineEdit();

    /**
     * Setting value, that means disable itself
     * @param disableValue disable itself value
     */
    void setDisableValue(QString disableValue);

public slots:
    /**
     * Checking, if given value match disable value and enable/disable itself.
     * @param addrValue value to match
     */
    void checkForDisable(QString addrValue);

private:
    /** disable itself value */
    QString disableValue;

};

#endif	/* MASKLINEEDIT_H */

