#include <QtSql>
#include<QtGui>
#ifndef LOGIN_H
#define LOGIN_H
#include "ResearchPaper.h"
#include "Transaction.h"
#include "ResearchProject.h"
#include "Course.h"
#include "student.h"
#include "subject.h"
#include "InventoryItem.h"
#include "subjectperformancedetails.h"
class LoginManager
{
    public :
        static LoginManager* Instance();
        int loginVerification(QString, QString);
        QVector<ResearchPaper> findResearchPapers();
        QString addResearchPaper(ResearchPaper);
        QString addResearchProject(ResearchProject);
        QVector<ResearchProject> findResearchProjects(int type = -1);
        bool InsertTransaction(Transaction);
        QList<Transaction> getTransactions();
        QList<Course> getCourses();
        void RegisterStudent(Student);
        void AddLoginDetails(QString, QString, int);
        QList<Subject> getSubjects();
        bool checkRollNumber(QString roll);
        void writeRegistrationData(QString, QString);
        int studentRegisteredForSemester(QString);
        int getCredits(QString);
        QList<QString> getGrades(QString);
        void enterGrade(QString, QString, QString);
        int getCurrentSemester(QString);
        QList<QString> getRollNoList();
        void insertCGPA(QString, float);
        QStringList getRooms();
        void insertInventoryItem(InventoryItem);
        QStringList getInventoryDetails(QString);
        Student getStudentDetails(QString);
        void updateStudentDetails(QString,QString, QString);
        QList<Student> SearchStudents(QString);
        QList<ResearchProject> getProjects();

    protected:
        LoginManager();
    private :
        static LoginManager* _instance;
        QSqlDatabase db;

};
#endif // LOGIN_H
