#include <QtGui/QApplication>
#include <QtSql>
#include "GradesDatabaseManager.h"
#include "CoursesDatabaseManager.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //db.setDatabaseName("/home/harshit/my.sqlite.db");
    /*bool ok = db.open();
    qDebug() << "Trying to connect.......\n";
    if(ok)
    {
         qDebug() << "Connected !!!";
         QString Query("SELECT Course_ID FROM depth_courses");
         QSqlQuery query(Query, db);
         query.exec();
         /*while( query.next() )
         {

             //qDebug()<<"INSIDE LOOP";
             //qDebug()<<query.value(0).toInt()<<endl;
             qDebug()<<query.value(0).toString();
             //QString createQuery = QString("CREATE TABLE ").append(query.value(0).toString()).append(" ( rollNo char(10) NOT NULL, grade char(2) NOT NULL, year int NOT NULL, semester int NOT NULL)");
             QString createQuery = QString("CREATE TABLE table ( rollNo int )");
             QSqlQuery create_query(createQuery, db);
             //create_query.exec();

         }*/
         /*int i;
         QStringList list = db.tables();
         for(i=0;i<list.count();i++)
             qDebug()<<list.at(i);
         qDebug()<<list.count();*/
         //db.exec(Query);\
        //qDebug()<<"TRYING TO GET THE COURSES";
         /*CoursesDatabaseManager *dbm = CoursesDatabaseManager::Instance();
         //qDebug()<<"INSTANCE CREATED";
         QList<Course> list = dbm->findCourses(4);
         qDebug()<<"GOT THE COURSES";
         int i;
         for(i=0;i<list.count();i++)
         {
             qDebug()<<list.at(i).getName();
         }*/
     //}
         GradesDatabaseManager::Instance()->enterGrade(EnterSubjectGradeQuery("cs21001", "11CS30014", "EX"));
    MainWindow w;
    w.show();
    qDebug()<<"DONE\n";
    w.close();
    return a.exec();
}
