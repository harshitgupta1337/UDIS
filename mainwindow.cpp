#include "mainwindow.h"
#include "login.h"
#include "ui_mainwindow.h"
#include "Transaction.h"
#include "AccountsListTransactionsDialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    QList<Course> coursesList = LoginManager::Instance()->getCourses();
    int i;
    for(i=0;i<coursesList.count();i++)
    {
        ui->SignUpCourseComboBox->addItem(coursesList.at(i)._name);
    }
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
        ui->incorrectLogin->setText("");
        ui->stackedWidget->setCurrentIndex(1);
    }
    else
    {
        ui->incorrectLogin->setText("Incorrect Username or Password");
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
    QVector<ResearchPaper> list = LoginManager::Instance()->findResearchPapers();
    QStringList stringList;
    int i;
    for(i=0;i<list.count();i++)
    {
        stringList.append(QString(list.at(i)._name).append(" By ").append(list.at(i)._author).append(" ").append(list.at(i)._journal));
    }
    ui->ResearchPapersListView->setModel(new QStringListModel(stringList));
}

void MainWindow::on_addResearchPaperButton_clicked()
{

    QString ID = LoginManager::Instance()->addResearchPaper(ResearchPaper(ui->PaperNameLineEdit->text(), ui->AuthorLineEdit->text(), ui->JournalLineEdit->text(), ui->AbstractTextEdit->toPlainText(), ui->YearLineEdit->text().toInt()));

    QMessageBox::information(this, "Research Paper Added", QString("PaperID : ").append(ID).append(" \nPaper Name : ").append(ui->PaperNameLineEdit->text()).append("\n").append("Author(s) : ").append(ui->AuthorLineEdit->text()).append("\n").append("Journal : ").append(ui->JournalLineEdit->text()), QMessageBox::Ok, QMessageBox::Ok);
}

void MainWindow::on_manageProjectsButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    ui->ProjectStackedwidget->setCurrentIndex(0);
}

void MainWindow::on_AddProjectButton_clicked()
{
    ui->ProjectStackedwidget->setCurrentIndex(1);
}


void MainWindow::on_ViewProjectsButton_clicked()
{
    ui->ProjectStackedwidget->setCurrentIndex(2);
}

void MainWindow::on_AddProjectToDatabaseButton_clicked()
{
    int type = (ui->SponsoredProjectRadioButton->isChecked())?0:1;
    QString ID = LoginManager::Instance()->addResearchProject(ResearchProject(ui->ProjectNameLineEdit->text(), ui->projectfacultyLineEdit->text(), ui->ProjectSponsorLineEdit->text(), type));
    QMessageBox::information(this, "Research Project Added", QString("Project ID : ").append(ID).append(" \nSponsor : ").append(ui->ProjectSponsorLineEdit->text()).append("\n").append("Principal Investigator(s)/Consultant(s) : ").append(ui->projectfacultyLineEdit->text()).append(ui->ProjectNameLineEdit->text()), QMessageBox::Ok, QMessageBox::Ok);
}

void MainWindow::on_manageAccountsButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->AccountsStackedWidget->setCurrentIndex(0);
    QVector<ResearchProject> list = LoginManager::Instance()->findResearchProjects();
    int i;
    for(i=0;i<list.count();i++)
    {
        ui->AccountsProjectsComboBox->addItem(list.at(i)._ProjectID);
    }
}

void MainWindow::on_AccountsEnterTransactionButton_clicked()
{
    if((!(ui->AccountsAmountLineEdit->text().length()>0))||(!(ui->AccountsUniversityGrantRadio->isChecked()||ui->AccountsConsultancyProjectGrantRadio->isChecked())))
    {
        QMessageBox::warning(this, QString("Insufficient Data"), QString("Please enter the fields with proper data"), QMessageBox::Ok, QMessageBox::Ok);
    }
    else
    {
        if(ui->AccountsUniversityGrantRadio->isChecked())
            LoginManager::Instance()->InsertTransaction(Transaction(ui->AccountsAmountLineEdit->text().toInt(), 10, QString("University Grant")));
        else
            LoginManager::Instance()->InsertTransaction(Transaction(ui->AccountsAmountLineEdit->text().toInt(), 11, ui->AccountsProjectsComboBox->currentText()));
    }
}

void MainWindow::on_AccountsUniversityGrantRadio_clicked()
{
    ui->AccountsProjectLabel->setEnabled(false);
    ui->AccountsProjectsComboBox->setEnabled(false);
}

void MainWindow::on_AccountsConsultancyProjectGrantRadio_clicked()
{
    ui->AccountsProjectLabel->setEnabled(true);
    ui->AccountsProjectsComboBox->setEnabled(true);

}

void MainWindow::on_AccountsViewDetailsButton_clicked()
{
    /*AccountsListTransactionsDialog *dialog = new AccountsListTransactionsDialog();
    dialog->opened();*/
    ui->AccountsStackedWidget->setCurrentIndex(1);
    QList<Transaction> list = LoginManager::Instance()->getTransactions();
    QStandardItemModel *model = new QStandardItemModel;
    int i;
    for(i=0;i<list.count();i++)
    {
        QStandardItem *group = new QStandardItem(QString(list.at(i)._timeStamp));
        group->appendRow(new QStandardItem(QString("Amount : Rs. %1").arg(list.at(i)._amount)));
        group->appendRow(new QStandardItem(QString("Cause : ").append(list.at(i)._cause)));
        model->appendRow(group);
    }
    ui->AccountsColumnView->setModel(model);

}

void MainWindow::on_registerPushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_SignUpRegisterButton_clicked()
{
    if(ui->SignUpPasswordLineEdit->text().compare(ui->SignUpConfirmPasswordLineEdit->text())!=0)
    {
        QMessageBox::warning(this, QString("Input Error"), QString("Passwords Don't Match"), QMessageBox::Ok, QMessageBox::Ok);
    }
    else if((ui->SignUpNameLineEdit->text().length()>0)&&(ui->SignUpRollNoLineEdit->text().length()>0))
    {
        LoginManager::Instance()->RegisterStudent(Student(ui->SignUpRollNoLineEdit->text(), ui->SignUpNameLineEdit->text(), ui->SignUpCourseComboBox->currentText(), ui->SignUpAddressTextEdit->toPlainText(), ui->SignUpBloodGroupLineEdit->text()));
    }
    else
    {
        QMessageBox::warning(this, QString("Insufficient Data"), QString("Please enter the fields with proper data"), QMessageBox::Ok, QMessageBox::Ok);
    }
}
