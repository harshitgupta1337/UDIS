#include<Qt>
#include "Course.h"
#define DEPTH 0
#define ELECTIVE 1

Course::Course(QString ID, QString name, int credits, int semester, int type)
{
    _name = name;
    _ID = ID;
    _credits = credits;
    _semester = semester;
    _type = type;
}
QString Course::getName() const
{
    return _name;
}
