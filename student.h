#include<QtGui>
#ifndef STUDENT_H
#define STUDENT_H

class Student
{
    friend class LoginManager;
    friend class MainWindow;
public:
    Student(QString, QString,QString,QString,QString, int = 0);
    Student();
private:
    QString _name;
    QString _rollNo;
    QString _course;
    QString _address;
    QString _bloodGroup;
    int _currentSemester;
};

#endif // STUDENT_H
