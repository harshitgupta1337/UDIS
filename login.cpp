#include "login.h"
#include<QtSql>

#define UNSPECIFIED -1

LoginManager::LoginManager()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/harshit/my.sqlite.db");
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
bool LoginManager::InsertTransaction(Transaction transaction)
{
    if(db.open())
    {
        QString countQueryString = QString("SELECT COUNT(*) FROM accounts");
        QSqlQuery countQuery = db.exec(countQueryString);
        countQuery.next();
        transaction._TransactionID = QString("T-%1").arg(countQuery.value(0).toInt());
        transaction._timeStamp = QDateTime::currentDateTime().toString();
        QString getCurrentBalanceQueryString("SELECT Amount FROM accounts WHERE Type = 2");
        QSqlQuery getCurrentBalanceQuery = db.exec(getCurrentBalanceQueryString);
        getCurrentBalanceQuery.next();

        if(getCurrentBalanceQuery.value(0).toInt()<transaction._amount)
            return false;

        QString insertQueryString = QString("INSERT INTO accounts VALUES ( '").append(transaction._TransactionID).append("' , ").append(QString("%1 , ").arg(transaction._amount)).append(QString("%1 , '").arg(transaction._type).append(transaction._cause).append("' , '").append(transaction._timeStamp).append(QString("' , %1 )").arg(countQuery.value(0).toInt())));
        db.exec(insertQueryString);

        if(transaction._type==10 || transaction._type==11)
        {
            QString updateQueryString = QString("UPDATE accounts SET Amount = %1 WHERE Type = 2").arg(transaction._amount + getCurrentBalanceQuery.value(0).toInt());
            db.exec(updateQueryString);
        }
        else if(transaction._type  == 0)
        {
            QString updateQueryString = QString("UPDATE accounts SET Amount = %1 WHERE Type = 2").arg(getCurrentBalanceQuery.value(0).toInt() - transaction._amount );
            db.exec(updateQueryString);

        }
        db.close();
        return true;
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
QList<Course> LoginManager::getCourses()
{
    QList<Course> list;
    if(db.open())
    {
        QString queryString("SELECT * FROM courses");
        QSqlQuery query = db.exec(queryString);
        while(query.next())
        {
            list.append(Course(query.value(0).toString(), query.value(1).toInt()));
        }
        db.close();
        return list;
    }
}
void LoginManager::RegisterStudent(Student student)
{
    if(db.open())
    {
        QString QueryString = QString("SELECT TotalCredits FROM courses WHERE Name = '").append(student._course).append("'");
        QSqlQuery Query = db.exec(QueryString);
        Query.next();
        QString insertQueryString = QString("INSERT INTO students VALUES ( '").append(student._rollNo).append("' , '").append(student._name).append("' , '").append(student._course).append("' , '").append(student._address).append("' , '").append(student._bloodGroup).append(QString("' , %1 , %2 , %3 , %4 )").arg(Query.value(0).toInt()).arg(0).arg(0).arg(0));
        qDebug()<<insertQueryString;
        db.exec(insertQueryString);
        db.close();
    }
}
void LoginManager::AddLoginDetails(QString username, QString password, int type)
{
    if(db.open())
    {
        QString insertQueryString = QString("INSERT INTO logindetails VALUES ( '").append(username).append("' , '").append(password).append("' , ").append(QString(" %1 )").arg(type));
        db.exec(insertQueryString);
        db.close();
    }
}
QList<Subject> LoginManager::getSubjects()
{
    QList<Subject> list;
    if(db.open())
    {
        QString queryString("SELECT * FROM depth_courses");
        QSqlQuery query = db.exec(queryString);
        while(query.next())
        {
            list.append(Subject(query.value(0).toString(), query.value(1).toString(), query.value(2).toInt(), query.value(4).toInt()));
        }
        db.close();
        return list;
    }
}
bool LoginManager::checkRollNumber(QString roll)
{
    if(db.open())
    {
        QString QueryString = QString("SELECT COUNT(*) FROM students WHERE RollNo = '").append(roll).append("'");
        QSqlQuery query = db.exec(QueryString);
        query.next();
        if(query.value(0)==1)
        {
            db.close();
            return true;
        }
        else
        {
            db.close();
            return false;
        }
    }
}
void LoginManager::writeRegistrationData(QString rollNo, QString subjectID)
{

    if(db.open())
    {
        QString queryString = QString("INSERT INTO ").append(subjectID.toLower()).append(" VALUES ( '").append(rollNo).append(("' , '-' , 0 , 0 )"));

        db.exec(queryString);
        db.close();
    }

}
int LoginManager::studentRegisteredForSemester(QString rollNo)//, QString subjectID)
{

    if(db.open())
    {
        QString queryString = QString("SELECT CurrentSemester FROM students WHERE RollNo = '").append(rollNo).append("'");
        QSqlQuery query = db.exec(queryString);
        query.next();
        int currentSem = query.value(0).toInt()+1;
        queryString = QString("UPDATE students SET CurrentSemester=").append(QString("%1").arg(currentSem)).append(" WHERE RollNo = '").append(rollNo).append("'");

        db.exec(queryString);
        db.close();
        return currentSem;
    }
}
int LoginManager::getCredits(QString ID)
{
    if(db.open())
    {
        QString queryString = QString("SELECT Credits FROM depth_courses WHERE Course_ID = '").append(ID).append("'");
        QSqlQuery query = db.exec(queryString);
        query.next();
        int res = query.value(0).toInt();
        db.close();
        return res;
    }
}
QList<QString> LoginManager::getGrades(QString subjectID)
{

    if(db.open())
    {
        QList<QString> list;
        QString queryString = QString("SELECT * FROM ").append(subjectID.toLower());
        QSqlQuery query = db.exec(queryString);
        while(query.next())
        {
            list.append(QString(query.value(0).toString()));
            list.append(QString(query.value(1).toString()));

        }
        db.close();
        return list;
    }
}
void LoginManager::enterGrade(QString course, QString roll, QString grade)
{
    if(db.open())
    {
        QString queryString = QString("UPDATE ").append(course.toLower()).append(" SET grade = '").append(grade.toUpper()).append("' WHERE rollNo = '").append(roll).append("'");
        db.exec(queryString);
        db.close();
    }
}
int LoginManager::getCurrentSemester(QString roll)
{
    if(db.open())
    {
        QString queryString = QString("SELECT CurrentSemester FROM students").append(" WHERE RollNo = '").append(roll.toUpper()).append("'");
        QSqlQuery query = db.exec(queryString);
        query.next();
        int res = query.value(0).toInt();
        db.close();
        return res;
    }
}
QList<QString> LoginManager::getRollNoList()
{
    if(db.open())
    {
        QList<QString> list;
        QString queryString = QString("SELECT RollNo FROM students");
        QSqlQuery query = db.exec(queryString);
        while(query.next())
        {
            list.append(query.value(0).toString());
        }
        db.close();
        return list;
    }
}
void LoginManager::insertCGPA(QString roll, float CGPA)
{
    if(db.open())
    {
        QString queryString = QString("UPDATE students SET CGPA = %1").arg(CGPA).append(" WHERE RollNo = '").append(roll.toUpper()).append("'");
        db.exec(queryString);
        db.close();
    }
}
QStringList LoginManager::getRooms()
{
    if(db.open())
    {
        QStringList list;
        QString queryString = QString("SELECT Room FROM inventory WHERE Type = 1");
        QSqlQuery query = db.exec(queryString);
        while(query.next())
        {
            list.append(query.value(0).toString());
        }
        db.close();
        return list;
    }
}
void LoginManager::insertInventoryItem(InventoryItem item)
{
    if(db.open())
    {
        QString queryString = QString("SELECT COUNT(*) FROM inventory WHERE InventoryType = %1 AND Room = '").append(item._room).arg(item._type).append("'");
        QSqlQuery query = db.exec(queryString);
        query.next();

        queryString = QString("INSERT INTO inventory VALUES ( '").append(item._room.toUpper()).append(QString("' , %1 , '").arg(item._type)).append(item._room.toUpper().append(QString("-%1-%2' , %3 , %4 , '").arg(item._type).arg(query.value(0).toInt()+1).arg(0).arg(item._price).append(item._name).append("')")));
        db.exec(queryString);
    }
}
