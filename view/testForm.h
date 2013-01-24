/* 
 * File:   testForm.h
 * Author: petris
 *
 * Created on 24. leden 2013, 13:15
 */

#ifndef _TESTFORM_H
#define	_TESTFORM_H

#include "ui_testForm.h"

class testForm : public QDialog {
    Q_OBJECT
public:
    testForm();
    virtual ~testForm();
private:
    Ui::testForm widget;
};

#endif	/* _TESTFORM_H */
