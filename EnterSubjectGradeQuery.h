#ifndef ENTERSUBJECTGRADEQUERY_H
#define ENTERSUBJECTGRADEQUERY_H
#include<QtGui>

class EnterSubjectGradeQuery
{
    friend class GradesDatabaseManager;
public :
    EnterSubjectGradeQuery(QString courseID, QString rollNo, QString grade):_courseID(courseID), _rollNo(rollNo), _grade(grade)
    {

    }

private :
    QString _rollNo;
    QString _courseID;
    QString _grade;
};

#endif // ENTERSUBJECTGRADEQUERY_H
