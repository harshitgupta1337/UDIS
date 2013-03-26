#ifndef GRADESDATABASEMANAGER_H
#define GRADESDATABASEMANAGER_H
#include<QtGui>
#include<QtSql>
#include "EnterSubjectGradeQuery.h"
class GradesDatabaseManager
{
    public :
        static GradesDatabaseManager* Instance();
        void enterGrade(EnterSubjectGradeQuery);
    protected:
        GradesDatabaseManager();

    private :
        static GradesDatabaseManager* _instance;
        QSqlDatabase db;

};
#endif // GRADESDATABASEMANAGER_H
