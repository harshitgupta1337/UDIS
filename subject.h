#include<QtGui>
#ifndef SUBJECT_H
#define SUBJECT_H

class Subject
{
    friend class LoginManager;
    friend class MainWindow;
public:
    Subject(QString, QString, int, int);

private :
    int _credits;
    QString _SubjectID;
    QString _name;
    int _type;
};

#endif // SUBJECT_H
