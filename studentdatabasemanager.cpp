#include "login.h"
#include "studentdatabasemanager.h"
StudentDatabaseManager::StudentDatabaseManager()
{
    db = QSqlDatabase::addDatabase("QSQLITE", QString("studentConnection"));
    db.setDatabaseName("/home/harshit/students.sqlite.db");
}

StudentDatabaseManager* StudentDatabaseManager::_instance = 0;

StudentDatabaseManager* StudentDatabaseManager::Instance()
{
    if(_instance==0)
        _instance = new StudentDatabaseManager();
    return _instance;
}
void StudentDatabaseManager::createStudent(QString roll)
{
    if(db.open())
    {
        QString QueryString = QString("CREATE TABLE student_").append(roll.toLower()).append(" ( SubjectCode TEXT , Credits INTEGER , Semester INTEGER , Grade TEXT )");
        db.exec(QueryString);
        db.close();
    }
}
 void StudentDatabaseManager::insertSubjectRegistration(QString rollNo, QString subjectID, int semester)
 {
     if(db.open())
     {
         QString QueryString = QString("INSERT INTO student_").append(rollNo.toLower()).append(" VALUES ( '").append(subjectID).append(QString("' , %1 , %2 , '-')").arg(LoginManager::Instance()->getCredits(subjectID)).arg(semester));
         db.exec(QueryString);
         db.close();
     }
 }
void StudentDatabaseManager::enterGrade(QString ID, QString roll, QString grade)
{
    if(db.open())
    {
        QString queryString = QString("UPDATE student_").append(roll.toLower()).append(" SET Grade = '").append(grade.toUpper()).append("' WHERE SubjectCode = '").append(ID).append(QString("' AND Semester = %1").arg(LoginManager::Instance()->getCurrentSemester(roll)));
        db.exec(queryString);
        db.close();
    }
}
float StudentDatabaseManager::generateCGPA(QString roll)
{
    if(db.open())
    {
        float num = 0, den =  0;
        QString queryString = QString("SELECT * FROM student_").append(roll.toLower());//.append(" WHERE Grade <> 'F'");
        QSqlQuery query = db.exec(queryString);
        while(query.next())
        {
            if(query.value(3).toString().compare(QString("EX"))==0)
            {
                num += 10*query.value(1).toInt();
                den += query.value(1).toInt();
            }
            else if(query.value(3).toString().compare(QString("A"))==0)
            {
                num += 9*query.value(1).toInt();
                den += query.value(1).toInt();
            }
            else if(query.value(3).toString().compare(QString("B"))==0)
            {
                num += 8*query.value(1).toInt();
                den += query.value(1).toInt();
            }
            else if(query.value(3).toString().compare(QString("C"))==0)
            {
                num += 7*query.value(1).toInt();
                den += query.value(1).toInt();
            }
            else if(query.value(3).toString().compare(QString("D"))==0)
            {
                num += 6*query.value(1).toInt();
                den += query.value(1).toInt();
            }
            else if(query.value(3).toString().compare(QString("P"))==0)
            {
                num += 5*query.value(1).toInt();
                den += query.value(1).toInt();
            }
        }
        db.close();
        return (num/den*1.0);
    }
}
