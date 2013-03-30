#include<QtSql>
#ifndef STUDENTDATABASEMANAGER_H
#define STUDENTDATABASEMANAGER_H

class StudentDatabaseManager
{
public :
    static StudentDatabaseManager* Instance();
    void createStudent(QString);
    void insertSubjectRegistration(QString, QString, int);
    void enterGrade(QString, QString, QString);
    float generateCGPA(QString);
protected:
    StudentDatabaseManager();
private :
    static StudentDatabaseManager* _instance;
    QSqlDatabase db;
};

#endif // STUDENTDATABASEMANAGER_H
