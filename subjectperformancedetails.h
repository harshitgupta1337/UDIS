#include<QtGui>

#ifndef SUBJECTPERFORMANCEDETAILS_H
#define SUBJECTPERFORMANCEDETAILS_H

class SubjectPerformanceDetails
{
    friend class StudentDatabaseManager;
    friend class MainWindow;
public:
    SubjectPerformanceDetails(QString, int, int, QString);

private :
    QString _courseCode;
    int _credits;
    int _semester;
    QString _grade;
};

#endif // SUBJECTPERFORMANCEDETAILS_H
