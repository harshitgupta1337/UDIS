#include "ResearchProjectsDatabaseManager.h"

ResearchProjectsDatabaseManager::ResearchProjectsDatabaseManager()
{
    db.addDatabase("QSQLITE");
    db.setDatabaseName("/home/harshit/my.sqlite.db");

}

ResearchProjectsDatabaseManager* ResearchProjectsDatabaseManager::_instance = 0;

ResearchProjectsDatabaseManager* ResearchProjectsDatabaseManager::Instance()
{
    if(_instance==0)
        _instance = new ResearchProjectsDatabaseManager();
    return _instance;
}

QList<ResearchProject> ResearchProjectsDatabaseManager::findResearchProjects()
{
    if(db.open())
    {
        QList<ResearchProject> list;
        QString queryString("SELECT * FROM research_projects");
        QSqlQuery query(queryString, db);
        query.exec();
        while(query.next())
        {
            list.append(ResearchProject(query.value(0).toString(), query.value(1).toString(), query.value(2).toString(), query.value(4).toString()));
        }
        db.close();
        return list;
       }
}
