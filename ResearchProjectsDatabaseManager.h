#include<QtSql>
#include "ResearchProject.h"
#ifndef RESEARCHPROJECTSDATABASEMANAGER_H
#define RESEARCHPROJECTSDATABASEMANAGER_H

class ResearchProjectsDatabaseManager
{
    public :
        static ResearchProjectsDatabaseManager* Instance();
    protected:
        ResearchProjectsDatabaseManager();
    private :
        static ResearchProjectsDatabaseManager* _instance;
        QSqlDatabase db;
        QList<ResearchProject> findResearchProjects();
};

#endif // RESEARCHPROJECTSDATABASEMANAGER_H
