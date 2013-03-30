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
        QString QueryString = QString("CREATE TABLE student_").append(roll.toLower()).append(" ( SubjectCode TEXT , Credits INTEGER , Semester INTEGER , CurrentSemester INTEGER , Grade TEXT )");
        db.exec(QueryString);
        db.close();
    }
}
