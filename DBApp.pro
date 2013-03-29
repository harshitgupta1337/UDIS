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
    Course.cpp \
    InventoryItem.cpp \
    InventoryDatabaseManager.cpp \
    GradesDatabaseManager.cpp \
    login.cpp \
    ResearchProjectsDatabaseManager.cpp

HEADERS  += mainwindow.h \
    Course.h \
    CoursesDatabaseManager.h \
    InventoryItem.h \
    InventoryDatabaseManager.h \
    EnterSubjectGradeQuery.h \
    GradesDatabaseManager.h \
    login.h \
    ResearchProjectsDatabaseManager.h \
    ResearchProject.h

FORMS    += mainwindow.ui
