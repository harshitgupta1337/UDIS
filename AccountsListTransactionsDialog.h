#ifndef ACCOUNTSLISTTRANSACTIONSDIALOG_H
#define ACCOUNTSLISTTRANSACTIONSDIALOG_H
#include<QtGui>
class AccountsListTransactionsDialog : public QDialog
{
    Q_OBJECT

public :
    AccountsListTransactionsDialog(QWidget *parent = 0);

private :
    QColumnView *columnView;
    QStandardItemModel *model;
    QHBoxLayout *layout;

/*public slots :
    void opened();
private slots :
    void resize1();*/
};

#endif // ACCOUNTSLISTTRANSACTIONSDIALOG_H
