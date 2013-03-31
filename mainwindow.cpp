#include "mainwindow.h"
#include "login.h"
#include "ui_mainwindow.h"
#include "Transaction.h"
#include "AccountsListTransactionsDialog.h"
#include "studentdatabasemanager.h"

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
        ui->usernameLineEdit->clear();
        ui->passwordLineEdit->clear();
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
        StudentDatabaseManager::Instance()->createStudent(ui->SignUpRollNoLineEdit->text());
        LoginManager::Instance()->AddLoginDetails(ui->SignUpRollNoLineEdit->text(), ui->SignUpPasswordLineEdit->text(), 0);
        LoginManager::Instance()->RegisterStudent(Student(ui->SignUpRollNoLineEdit->text(), ui->SignUpNameLineEdit->text(), ui->SignUpCourseComboBox->currentText(), ui->SignUpAddressTextEdit->toPlainText(), ui->SignUpBloodGroupLineEdit->text()));
    }
    else
    {
        QMessageBox::warning(this, QString("Insufficient Data"), QString("Please enter the fields with proper data"), QMessageBox::Ok, QMessageBox::Ok);
    }
}

void MainWindow::on_enterRegistrationDetailsButton_clicked()
{
    ui->CourseRegisterAllDepthCoursesListWidget->clear();
    QList<Subject> list = LoginManager::Instance()->getSubjects();
    QStringList depthList, electiveList;
    int i;
    for(i=0;i<list.count();i++)
    {
        ui->CourseRegisterAllDepthCoursesListWidget->addItem(list.at(i)._SubjectID);
    }
    ui->stackedWidget->setCurrentIndex(7);
}

void MainWindow::on_CourseRegisterAddToDepthCoursesButton_clicked()
{

    ui->CourseRegisterDepthCoursesListWidget->addItem(ui->CourseRegisterAllDepthCoursesListWidget->currentItem()->text());
}

void MainWindow::on_BacklogsButton_clicked()
{
    ui->CourseRegisterBacklogCoursesListWidget->addItem(ui->CourseRegisterAllDepthCoursesListWidget->currentItem()->text());
}


void MainWindow::on_CourseRegisterGoButton_clicked()
{
    if(ui->CourseRegisterRollNoLineEdit->text().length()==0)
    {
        QMessageBox::warning(this, QString("Insufficient Data"), QString("Please enter Roll No."), QMessageBox::Ok, QMessageBox::Ok);
    }
    else
    {
        if(LoginManager::Instance()->checkRollNumber(ui->CourseRegisterRollNoLineEdit->text()))
        {
            int currentSem = LoginManager::Instance()->studentRegisteredForSemester(ui->CourseRegisterRollNoLineEdit->text());

            int i;
            for(i=0;i<ui->CourseRegisterDepthCoursesListWidget->count();i++)
            {
                StudentDatabaseManager::Instance()->insertSubjectRegistration(ui->CourseRegisterRollNoLineEdit->text(), ui->CourseRegisterDepthCoursesListWidget->item(i)->text(), currentSem);
                LoginManager::Instance()->writeRegistrationData(ui->CourseRegisterRollNoLineEdit->text(), ui->CourseRegisterDepthCoursesListWidget->item(i)->text());
            }
            for(i=0;i<ui->CourseRegisterBacklogCoursesListWidget->count();i++)
            {
                StudentDatabaseManager::Instance()->insertSubjectRegistration(ui->CourseRegisterRollNoLineEdit->text(), ui->CourseRegisterBacklogCoursesListWidget->item(i)->text(), currentSem);
                LoginManager::Instance()->writeRegistrationData(ui->CourseRegisterRollNoLineEdit->text(), ui->CourseRegisterBacklogCoursesListWidget->item(i)->text());
            }
        }
        else
        {
            //ui->stackedWidget->setCurrentIndex(0);
            QMessageBox::warning(this, QString("Invalid Data"), QString("Please enter a Valid Roll No."), QMessageBox::Ok, QMessageBox::Ok);
        }
    }
}

void MainWindow::on_EnterGradesPushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
    ui->EnterGradesStackedWidget->setCurrentIndex(0);
}

void MainWindow::on_EnterGradesFetchGradeSheetButton_clicked()
{
    QList<QString> list = LoginManager::Instance()->getGrades(ui->EnterGradesSubjectCodeLineEdit->text());
    if(list.count()>0)
    {
        int i;
        for(i=0;i<list.count();i=i+2)
        {
            ui->EnterGradesTableWidget->insertRow(ui->EnterGradesTableWidget->rowCount());
            ui->EnterGradesTableWidget->setItem(ui->EnterGradesTableWidget->rowCount()-1, 0, new QTableWidgetItem(list.at(i)));
            ui->EnterGradesTableWidget->setItem(ui->EnterGradesTableWidget->rowCount()-1, 1, new QTableWidgetItem(list.at(i+1)));

        }
        ui->EnterGradesSubjectCodeLabel_2->setText(ui->EnterGradesSubjectCodeLineEdit->text());
        ui->EnterGradesStackedWidget->setCurrentIndex(1);
    }
}

void MainWindow::on_EnterGradesSubmitGradesButton_clicked()
{
    int i, flag = 0;
    for(i=0;i<ui->EnterGradesTableWidget->rowCount();i++)
    {
        if(ui->EnterGradesTableWidget->item(i, 1)->text().compare(QString("-"))==0)
            flag = 1;
    }
    if(flag==1)
    {
        QMessageBox::warning(this, QString("Incomplete Data"), QString("Please enter grades for all students"), QMessageBox::Ok, QMessageBox::Ok);
    }
    else
    {
        for(i=0;i<ui->EnterGradesTableWidget->rowCount();i++)
        {
            LoginManager::Instance()->enterGrade(ui->EnterGradesSubjectCodeLabel_2->text(), ui->EnterGradesTableWidget->item(i,0)->text(), ui->EnterGradesTableWidget->item(i,1)->text());
            StudentDatabaseManager::Instance()->enterGrade(ui->EnterGradesSubjectCodeLabel_2->text(), ui->EnterGradesTableWidget->item(i,0)->text(), ui->EnterGradesTableWidget->item(i,1)->text());
        }

    }
}

void MainWindow::on_GenerateCGPAPushhButton_clicked()
{
    QList<QString> list = LoginManager::Instance()->getRollNoList();
    int i;
    for(i=0;i<list.count();i++)
    {
        float CGPA = StudentDatabaseManager::Instance()->generateCGPA(list.at(i));
        LoginManager::Instance()->insertCGPA(list.at(i), CGPA);
    }
}

void MainWindow::on_secretaryLogoutPushButton_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_secretaryLogoutPushButton_8_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_secretaryLogoutPushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_secretaryLogoutPushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_secretaryLogoutPushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_secretaryLogoutPushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_secretaryLogoutPushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
    ui->GradeSheetStackedWidget->setCurrentIndex(0);
}

void MainWindow::on_GradeSheetGetGradeSheetButton_clicked()
{
    if(LoginManager::Instance()->checkRollNumber(ui->GradeSheetRollNumberLineEdit->text()))
    {
        QList<SubjectPerformanceDetails> list;
        int i=1, j=0;
        while(true)
        {
            list = StudentDatabaseManager::Instance()->getSemesterDetails(ui->GradeSheetRollNumberLineEdit->text(), i);
            if(list.count()>0)
            {
                ui->GradeSheetTableWidget->insertRow(ui->GradeSheetTableWidget->rowCount());
                ui->GradeSheetTableWidget->setItem(ui->GradeSheetTableWidget->rowCount()-1, 0, new QTableWidgetItem(QString("Semester %1").arg(i)));

                ui->GradeSheetTableWidget->insertRow(ui->GradeSheetTableWidget->rowCount());
                ui->GradeSheetTableWidget->insertRow(ui->GradeSheetTableWidget->rowCount());
                ui->GradeSheetTableWidget->setItem(ui->GradeSheetTableWidget->rowCount()-1, 0, new QTableWidgetItem(QString("SUBJECT")));
                ui->GradeSheetTableWidget->setItem(ui->GradeSheetTableWidget->rowCount()-1, 1, new QTableWidgetItem(QString("CREDITS")));
                ui->GradeSheetTableWidget->setItem(ui->GradeSheetTableWidget->rowCount()-1, 2, new QTableWidgetItem(QString("GRADE")));
                for(j=0;j<list.count();j++)
                {
                    qDebug()<<list.at(0)._courseCode;
                    ui->GradeSheetTableWidget->insertRow(ui->GradeSheetTableWidget->rowCount());
                    ui->GradeSheetTableWidget->setItem(ui->GradeSheetTableWidget->rowCount()-1, 0, new QTableWidgetItem(list.at(j)._courseCode));
                    ui->GradeSheetTableWidget->setItem(ui->GradeSheetTableWidget->rowCount()-1, 1, new QTableWidgetItem(QString("%1").arg(list.at(j)._credits)));
                    ui->GradeSheetTableWidget->setItem(ui->GradeSheetTableWidget->rowCount()-1, 2, new QTableWidgetItem(list.at(j)._grade));
                }
                ui->GradeSheetTableWidget->insertRow(ui->GradeSheetTableWidget->rowCount());
                ui->GradeSheetTableWidget->insertRow(ui->GradeSheetTableWidget->rowCount());
                ui->GradeSheetTableWidget->setItem(ui->GradeSheetTableWidget->rowCount()-1, 0, new QTableWidgetItem(QString("SGPA = %1").arg(StudentDatabaseManager::Instance()->generateSGPA(ui->GradeSheetRollNumberLineEdit->text(), i))));
                ui->GradeSheetTableWidget->setItem(ui->GradeSheetTableWidget->rowCount()-1, 1, new QTableWidgetItem(QString("CGPA = %1").arg(StudentDatabaseManager::Instance()->generateCGPAuptoSem(ui->GradeSheetRollNumberLineEdit->text(), i))));
                ui->GradeSheetTableWidget->insertRow(ui->GradeSheetTableWidget->rowCount());
            }
            else
            {
                break;
            }
            i++;
        }
        ui->GradeSheetStackedWidget->setCurrentIndex(1);

    }
    else
    {
        QMessageBox::warning(this, QString("Invalid Data"), QString("Please enter a Valid Roll No."), QMessageBox::Ok, QMessageBox::Ok);
    }
}
