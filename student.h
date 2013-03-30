#include<QtGui>
#ifndef STUDENT_H
#define STUDENT_H

class Student
{
    friend class LoginManager;
public:
    Student(QString, QString,QString,QString,QString, int = 0);
private:
    QString _name;
    QString _rollNo;
    QString _course;
    QString _address;
    QString _bloodGroup;
    int _currentSemester;
};

#endif // STUDENT_H
