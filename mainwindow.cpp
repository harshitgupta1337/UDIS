#include "mainwindow.h"
#include "login.h"
#include "ResearchProjectsDatabaseManager.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_submitButton_clicked()
{
    int result = LoginManager::Instance()->loginVerification(ui->usernameLineEdit->text(), ui->passwordLineEdit->text());
    if(result==1)
    {
        ui->stackedWidget->setCurrentIndex(1);
    }
}

void MainWindow::on_managePublicationsButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->ResearchPaperStackedWidget->setCurrentIndex(0);
}

void MainWindow::on_AddResearchPaperPushButton_clicked()
{
    ui->ResearchPaperStackedWidget->setCurrentIndex(1);
}

void MainWindow::on_ViewResearchPaperPushButton_clicked()
{
    ui->ResearchPaperStackedWidget->setCurrentIndex(2);
    //POPULATE THE RESEARCH PAPERS TABLE
}
