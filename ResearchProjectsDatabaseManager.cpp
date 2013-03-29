/*#include "ResearchProjectsDatabaseManager.h"

ResearchProjectsDatabaseManager::ResearchProjectsDatabaseManager()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/harshit/my.sqlite.db");
}

ResearchProjectsDatabaseManager* ResearchProjectsDatabaseManager::_instance = 0;

ResearchProjectsDatabaseManager* ResearchProjectsDatabaseManager::Instance()
{
    if(_instance==0)
        _instance = new ResearchProjectsDatabaseManager();
    return _instance;
}

QVector<ResearchProject> ResearchProjectsDatabaseManager::findResearchProjects()
{
    if(db.open())
    {
        QVector<ResearchProject> list;
        QString queryString("SELECT * FROM research_papers");
        QSqlQuery query(queryString, db);
        query.exec();
        while(query.next())
        {
            list.append(ResearchProject(query.value(0).toString(), query.value(1).toString(), query.value(2).toString(), query.value(3).toString(), query.value(4).toInt()));
        }
        db.close();
        return list;
       }
}
QString ResearchProjectsDatabaseManager::addResearchProject(ResearchProject paper)
{
    if(db.open())
    {
        QString queryString = QString("INSERT INTO research_papers VALUES ( '").append(paper._name).append("' , '").append(paper._author).append("' , '").append(paper._journal).append("' , '").append(paper._abstract).append("' , ").append(QString("%1").arg(paper._year)).append(" ) ");
        qDebug()<<queryString;
        db.exec(queryString);
    }
    db.close();
}
*/
