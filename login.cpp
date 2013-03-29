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
            db.close();
            return loginQuery.value(2).toInt();
        }
        else
        {
            db.close();
            return -1;
        }
    }
    db.close();
}
QVector<ResearchPaper> LoginManager::findResearchPapers()
{
    if(db.open())
    {
        QVector<ResearchPaper> list;
        QString queryString("SELECT * FROM research_papers");
        QSqlQuery query(queryString, db);
        query.exec();
        while(query.next())
        {
            list.append(ResearchPaper(query.value(0).toString(), query.value(1).toString(), query.value(2).toString(), query.value(3).toString(), query.value(4).toInt()));
        }
        db.close();
        return list;
       }
}
QString LoginManager::addResearchPaper(ResearchPaper paper)
{
    if(db.open())
    {
        QString countQueryString = QString("SELECT COUNT(*) FROM research_papers");
        QSqlQuery query = db.exec(countQueryString);
        query.next();
        paper._PaperID = QString("P-%1").arg(query.value(0).toInt()+1);
        QString queryString = QString("INSERT INTO research_papers VALUES ( '").append(paper._name).append("' , '").append(paper._author).append("' , '").append(paper._journal).append("' , '").append(paper._abstract).append("' , ").append(QString("%1").arg(paper._year)).append(" , '").append(paper._PaperID).append("' ) ");
        qDebug()<<queryString;
        db.exec(queryString);
        db.close();
        return paper._PaperID;
    }


}
QString LoginManager::addResearchProject(ResearchProject project)
{
    if(db.open())
    {
        if(project._type==0)
        {
            QString countQueryString= QString("SELECT COUNT(*) FROM research_projects WHERE type = 0");
            QSqlQuery query = db.exec(countQueryString);
            query.next();
            project._ProjectID = QString("SRP-%1").arg(query.value(0).toInt()+1);
            QString queryString = QString("INSERT INTO research_projects VALUES ( '").append(project._ProjectID).append("' , '").append(project._sponsor).append("' , '").append(project._faculty).append("' , '").append(project._name).append("' , ").append("0").append(" ) ");
            db.exec(queryString);
            db.close();
            return project._ProjectID;
        }
        if(project._type==1)
        {
            QString countQueryString = QString("SELECT COUNT(*) FROM research_projects WHERE type = 1");
            QSqlQuery query = db.exec(countQueryString);
            query.next();
            project._ProjectID = QString("CP-%1").arg(query.value(0).toInt()+1);
            QString queryString = QString("INSERT INTO research_projects VALUES ( '").append(project._ProjectID).append("' , '").append(project._sponsor).append("' , '").append(project._faculty).append("' , '").append(project._name).append("' , ").append("1").append(" ) ");
            db.exec(queryString);
            db.close();
            return project._ProjectID;
        }
    }
}
QVector<ResearchProject> LoginManager::findResearchProjects(int type)
{
    QString queryString;
    if(type==-1)
    {
        queryString = "SELECT * FROM research_projects";

    }
    else if(type==0)
    {
        queryString = "SELECT * FROM research_projects WHERE Type = 0";
    }
    else if(type==1)
    {
        queryString = "SELECT * FROM research_projects WHERE Type = 1";
    }

    if(db.open())
    {
        QVector<ResearchProject> list;
        QSqlQuery query = db.exec(queryString);
        while(query.next())
        {
            list.append(ResearchProject(query.value(3).toString(), query.value(2).toString(), query.value(1).toString(), query.value(4).toInt(), query.value(0).toString()));
        }
        db.close();
        return list;
    }
}
void LoginManager::InsertTransaction(Transaction transaction)
{
    if(db.open())
    {
        QString countQueryString = QString("SELECT COUNT(*) FROM accounts");
        QSqlQuery countQuery = db.exec(countQueryString);
        countQuery.next();
        transaction._TransactionID = QString("T-%1").arg(countQuery.value(0).toInt());
        transaction._timeStamp = QDateTime::currentDateTime().toString();
        QString insertQueryString = QString("INSERT INTO accounts VALUES ( '").append(transaction._TransactionID).append("' , ").append(QString("%1 , ").arg(transaction._amount)).append(QString("%1 , '").arg(transaction._type).append(transaction._cause).append("' , '").append(transaction._timeStamp).append("' )"));
        db.exec(insertQueryString);
        db.close();
    }
}
QList<Transaction> LoginManager::getTransactions()
{
    if(db.open())
    {
        QList<Transaction> list;
        QString queryString("SELECT * FROM accounts WHERE Type <> 2");
        QSqlQuery query = db.exec(queryString);
        while(query.next())
        {
            list.append(Transaction(query.value(0).toString(), query.value(1).toInt(), query.value(3).toString(), query.value(4).toString()));
        }
        db.close();
        return list;
       }
}
