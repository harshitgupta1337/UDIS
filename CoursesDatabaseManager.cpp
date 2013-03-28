#include<QtSql>
#include "CoursesDatabaseManager.h"
#define UNSPECIFIED -1

CoursesDatabaseManager* CoursesDatabaseManager::_instance = 0;

CoursesDatabaseManager::CoursesDatabaseManager()
{
    qDebug()<<"ENTERED CONSTRUCTOR()";
    db = QSqlDatabase::addDatabase("QSQLITE");
    //db->addDatabase("QSQLITE");
    qDebug()<<"ENTERED INSTANCE()";
    db.setDatabaseName("/home/harshit/my.sqlite.db");
    qDebug()<<"DATABASE INITIALIZED";
}


CoursesDatabaseManager* CoursesDatabaseManager::Instance()
{
    qDebug()<<"ENTERED INSTANCE()";
    if(_instance==0)
        _instance = new CoursesDatabaseManager();
    return _instance;
}

QList<Course> CoursesDatabaseManager::findCourses(int semester, int type)
{
    if(db.open())
    {
        QList<Course> list;
        QString queryString;
        if(semester == UNSPECIFIED && type == UNSPECIFIED)
        {
            queryString = "SELECT * FROM depth_courses";
        }
        else if(semester == UNSPECIFIED)
        {
            queryString = QString("SELECT * FROM depth_courses WHERE Type = %1").arg(type);
        }
        else if(type == UNSPECIFIED)
        {
            queryString = QString("SELECT * FROM depth_courses WHERE Semester = %1").arg(semester);
        }
        else
        {
            queryString = QString("SELECT * FROM depth_courses WHERE Semester = %1 AND type = %1").arg(semester, type);
        }
        QSqlQuery query(queryString, db);
        query.exec();
        while(query.next())
        {
            list.append(Course(query.value(0).toString(), query.value(1).toString(), query.value(2).toInt(), query.value(3).toInt(), -1));//, query.value(4).toInt()));
        }
        return list;

    }
    db.close();
}
