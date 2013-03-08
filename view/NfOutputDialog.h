
#ifndef NFOUTPUTDIALOG_H
#define	NFOUTPUTDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QTextEdit>
#include <QString>

class NfOutputDialog : public QDialog {
public:
    NfOutputDialog(QWidget *parent, QString nfOutput);
    virtual ~NfOutputDialog();

private:
    QDialogButtonBox *buttons;
    QTextEdit *view;
};

#endif	/* NFOUTPUTDIALOG_H */

