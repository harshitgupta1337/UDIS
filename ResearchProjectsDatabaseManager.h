/*#include<QtSql>
#include "ResearchProject.h"
#ifndef RESEARCHPROJECTSDATABASEMANAGER_H
#define RESEARCHPROJECTSDATABASEMANAGER_H

class ResearchProjectsDatabaseManager
{
    public :
        static ResearchProjectsDatabaseManager* Instance();
        QVector<ResearchProject> findResearchProjects();
        QString addResearchProject(ResearchProject);
    protected:
        ResearchProjectsDatabaseManager();
    private :
        static ResearchProjectsDatabaseManager* _instance;
        QSqlDatabase db;

};

#endif // RESEARCHPROJECTSDATABASEMANAGER_H
*/
