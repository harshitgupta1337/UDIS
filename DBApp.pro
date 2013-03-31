#-------------------------------------------------
#
# Project created by QtCreator 2013-03-23T15:46:07
#
#-------------------------------------------------

QT       += core gui
QT       += sql

TARGET = DBApp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    CoursesDatabaseManager.cpp \
    InventoryItem.cpp \
    InventoryDatabaseManager.cpp \
    GradesDatabaseManager.cpp \
    login.cpp \
    AccountsListTransactionsDialog.cpp \
    OldCourse.cpp \
    Course.cpp \
    student.cpp \
    studentdatabasemanager.cpp \
    subject.cpp \
    subjectperformancedetails.cpp

HEADERS  += mainwindow.h \
    Course.h \
    InventoryItem.h \
    InventoryDatabaseManager.h \
    EnterSubjectGradeQuery.h \
    GradesDatabaseManager.h \
    login.h \
    ResearchPaper.h \
    ResearchProject.h \
    Transaction.h \
    AccountsListTransactionsDialog.h \
    student.h \
    studentdatabasemanager.h \
    subject.h \
    subjectperformancedetails.h

FORMS    += mainwindow.ui
