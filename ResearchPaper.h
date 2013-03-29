//#include "mainwindow.h"
#include<QtGui>
//#include "ResearchPapersDatabaseManager.h"
#ifndef RESEARCHPAPER_H
#define RESEARCHPAPER_H
class ResearchPaper
{
    friend class MainWindow;
    friend class LoginManager;
public :
    ResearchPaper()
    {}

    ResearchPaper(QString name, QString author, QString journal, QString abstract, int year):_name(name), _author(author), _journal(journal), _abstract(abstract), _year(year)
    {}

private :
    QString _PaperID;
    QString _name;
    QString _author;
    QString _journal;
    QString _abstract;
    int _year;
};

#endif // RESEARCHPaper_H
