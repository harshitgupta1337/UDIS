#include "AccountsListTransactionsDialog.h"
#include "login.h"
#include "Transaction.h"
/*AccountsListTransactionsDialog::AccountsListTransactionsDialog(QWidget *parent):QDialog(parent)
{
    columnView = new QColumnView();
    model = new QStandardItemModel();
    layout = new QHBoxLayout;

    layout->addWidget(columnView);
    setLayout(layout);
}
void AccouQList<Transaction> list = LoginManager::Instance()->getTransactions();
int i;
for(i=0;i<list.count();i++)
{
    QStandardItem *group = new QStandardItem(QString(list.at(i)._timeStamp));
    group->appendRow(new QStandardItem(QString("Amount : Rs. %1").arg(list.at(i)._amount)));
    group->appendRow(new QStandardItem(QString("Cause : ").append(list.at(i)._cause)));
    model->appendRow(group);
}
columnView->setModel(model);
ntsListTransactionsDialog::opened()
{
    this->show();
    QList<Transaction> list = LoginManager::Instance()->getTransactions();
    int i;
    for(i=0;i<list.count();i++)
    {
        QStandardItem *group = new QStandardItem(QString(list.at(i)._timeStamp));
        group->appendRow(new QStandardItem(QString("Amount : Rs. %1").arg(list.at(i)._amount)));
        group->appendRow(new QStandardItem(QString("Cause : ").append(list.at(i)._cause)));
        model->appendRow(group);
    }
    columnView->setModel(model);

    this->setMinimumSize(this->sizeHint());
    connect(columnView, SIGNAL(clicked(QModelIndex)), this, SLOT(resize1()));
}
void AccountsListTransactionsDialog::resize1()
{
    this->resize(this->sizeHint());
}
*/
