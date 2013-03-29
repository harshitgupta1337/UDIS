#include<Qt>
#ifndef RESEARCHPROJECT_H
#define RESEARCHPROJECT_H
class ResearchProject
{
    friend class MainWindow;
    friend class LoginManager;
public :
    ResearchProject()
    {}

    ResearchProject(QString name, QString faculty, QString sponsor, int type):_name(name), _faculty(faculty), _sponsor(sponsor), _type(type)
    {}
    ResearchProject(QString name, QString faculty, QString sponsor, int type, QString ID):_name(name), _faculty(faculty), _sponsor(sponsor), _type(type), _ProjectID(ID)
    {}
private :
    QString _name;
    QString _faculty;
    QString _sponsor;
    QString _ProjectID;
    int _type;
};
#endif // RESEARCHPROJECT_H
