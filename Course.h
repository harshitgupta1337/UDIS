#include<QtGui>
#include "CoursesDatabaseManager.h"
#ifndef COURSE_H
#define COURSE_H
class Course
{
    friend class LoginManager;
    friend class MainWindow;

public :
    Course(QString, int);
private :
    QString _name;
    int _credits;
};


#endif // COURSE_H
