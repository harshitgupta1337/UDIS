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
        QString queryString = QString("UPDATE student_").append(roll.toLower()).append(" SET Grade = '").append(grade.toUpper()).append("' WHERE SubjectCode = '").append(ID).append("'");
        db.exec(queryString);
        db.close();
    }
}
