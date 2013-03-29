#include<Qt>
#ifndef TRANSACTION_H
#define TRANSACTION_H
class Transaction
{
    friend class LoginManager;
    friend class MainWindow;
public :
    Transaction(int amount, int type, QString cause):_amount(amount), _type(type), _cause(cause)
    {

    }
    Transaction(QString ID, int amount, QString cause, QString timeStamp):_TransactionID(ID), _amount(amount), _cause(cause), _timeStamp(timeStamp)
    {

    }
private :
    int _amount;
    int _type;
    QString _cause;
    QString _TransactionID;
    QString _timeStamp;

};

#endif // TRANSACTION_H
