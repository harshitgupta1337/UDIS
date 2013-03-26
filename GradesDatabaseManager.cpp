#include "GradesDatabaseManager.h"

#define UNSPECIFIED -1

GradesDatabaseManager* GradesDatabaseManager::_instance = 0;

GradesDatabaseManager::GradesDatabaseManager()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/harshit/my.sqlite.db");
}
GradesDatabaseManager* GradesDatabaseManager::Instance()
{
    if(_instance==0)
        _instance = new GradesDatabaseManager();
    return _instance;
}
void GradesDatabaseManager::enterGrade(EnterSubjectGradeQuery arg)
{
    if(db.open())
    {

        QString queryString;
        queryString = QString("INSERT INTO %1 VALUES ( \"%2\" , \"%3\" , %4 , %5 )").arg(arg._courseID).arg(arg._rollNo).arg(arg._grade).arg(201).arg(1);
        qDebug()<<queryString;
        db.exec(queryString);
    }
    db.close();
}
