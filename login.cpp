#include "login.h"
#include<QtSql>
#define UNSPECIFIED -1

LoginManager::LoginManager()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/harshit/my.sqlite.db");
    //db.open();
}

LoginManager* LoginManager::_instance = 0;

LoginManager* LoginManager::Instance()
{
    if(_instance==0)
        _instance = new LoginManager();
    return _instance;
}
int LoginManager::loginVerification(QString username, QString password)
{
    if(db.open())
    {
        QString queryTemplate("SELECT * FROM logindetails");
        QSqlQuery loginQuery(queryTemplate, db);
        loginQuery.next();
        if((loginQuery.value(0).toString().compare(username)==0)&&(loginQuery.value(1).toString().compare(password)==0))
        {

            return loginQuery.value(2).toInt();
        }
        else
        {
            return -1;
        }
    }
    db.close();
}
