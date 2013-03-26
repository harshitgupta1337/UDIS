#include<QtGui>
#include "CoursesDatabaseManager.h"
#ifndef COURSE_H
#define COURSE_H
class Course
{
    friend class CoursesDatabaseManager;

public :
    Course(QString, QString, int, int, int);
    QString getName() const;
private :
    QString _name;
    QString _ID;
    int _credits;
    int _semester;
    int _type;

};
#endif // COURSE_H
