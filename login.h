#include <QtSql>
#include<QtGui>
#ifndef LOGIN_H
#define LOGIN_H

class LoginManager
{
    public :
        static LoginManager* Instance();
        int loginVerification(QString, QString);
    protected:
        LoginManager();
    private :
        static LoginManager* _instance;
        QSqlDatabase db;

};
#endif // LOGIN_H
