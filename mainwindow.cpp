#include "mainwindow.h"
#include "login.h"
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
}
