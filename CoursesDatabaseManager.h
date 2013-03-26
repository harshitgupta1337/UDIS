#ifndef COURSESDATABASEMANAGER_H
#define COURSESDATABASEMANAGER_H
#include<QtSql>
#include "Course.h"
#define UNSPECIFIED -1
class CoursesDatabaseManager
{
    public :
        static CoursesDatabaseManager* Instance();
        QList<Course> findCourses(int semester = UNSPECIFIED, int type = UNSPECIFIED);
    protected:
        CoursesDatabaseManager();
    private :
        static CoursesDatabaseManager* _instance;
        QSqlDatabase db;

};
#endif // COURSESDATABASEMANAGER_H
