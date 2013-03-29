#include<Qt>
#include "mainwindow.h"
#ifndef RESEARCHPROJECT_H
#define RESEARCHPROJECT_H
class ResearchProject
{
    friend class MainWindow;
public :
    ResearchProject(QString name, QString author, QString journal, QString abstract):_name(name), _author(author), _journal(journal), _abstract(abstract)
    {

    }

private :
    QString _name;
    QString _journal;
    QString _author;
    QString _abstract;
};

#endif // RESEARCHPROJECT_H
