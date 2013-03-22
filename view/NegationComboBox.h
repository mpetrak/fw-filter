
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

public slots:
    void checkForDisable(QString optionValue);

    void setDisableOption(QString disableOption);
private:

    QString disableOption;
};

#endif	/* NEGATIONCOMBOBOX_H */

