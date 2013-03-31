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
    ui->InventoryAddItemTypeComboBox->addItem(QString("Furniture"));
    ui->InventoryAddItemTypeComboBox->addItem(QString("Equipment"));
    ui->InventoryAddItemTypeComboBox->addItem(QString("Stationary"));
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
    else if(result == 0)
    {
        ui->StudentProfileRollNoLabel->setText(ui->usernameLineEdit->text());
        ui->incorrectLogin->setText("");
        ui->usernameLineEdit->clear();
        ui->passwordLineEdit->clear();
        ui->stackedWidget->setCurrentIndex(11);
        ui->StudentProfileStackedWidget->setCurrentIndex(0);
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
    QVector<ResearchPaper> list = LoginManager::Instance()->findResearchPapers();
    QStringList stringList;
    int i;
    for(i=0;i<list.count();i++)
    {
        stringList.append(QString("\nPaper Name :").append(list.at(i)._name).append("\nAuthor : ").append(list.at(i)._author).append("\nJournal : ").append(list.at(i)._journal));
    }
    ui->ResearchPapersListView->setModel(new QStringListModel(stringList));
}

void MainWindow::on_addResearchPaperButton_clicked()
{

    QString ID = LoginManager::Instance()->addResearchPaper(ResearchPaper(ui->PaperNameLineEdit->text(), ui->AuthorLineEdit->text(), ui->JournalLineEdit->text(), ui->AbstractTextEdit->toPlainText(), ui->YearLineEdit->text().toInt()));

    if(QMessageBox::information(this, "Research Paper Added", QString("PaperID : ").append(ID).append(" \nPaper Name : ").append(ui->PaperNameLineEdit->text()).append("\n").append("Author(s) : ").append(ui->AuthorLineEdit->text()).append("\n").append("Journal : ").append(ui->JournalLineEdit->text()), QMessageBox::Ok, QMessageBox::Ok)==QMessageBox::Ok)
    {

        ui->stackedWidget->setCurrentIndex(1);
        ui->PaperNameLineEdit->clear();
        ui->AuthorLineEdit->clear();
        ui->JournalLineEdit->clear();
        ui->YearLineEdit->clear();
        ui->AbstractTextEdit->clear();
    }
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
    QVector<ResearchProject> list = LoginManager::Instance()->findResearchProjects();
    QStringList stringList;
    int i;
    for(i=0;i<list.count();i++)
    {
        stringList.append(QString("\nProject Name : ").append(list.at(i)._name).append("\nSponsor : ").append(list.at(i)._sponsor).append("\nInvestigator : ").append(list.at(i)._faculty));
    }
    ui->ProjectsListView->setModel(new QStringListModel(stringList));
    ui->ProjectStackedwidget->setCurrentIndex(2);
}

void MainWindow::on_AddProjectToDatabaseButton_clicked()
{
    int type = (ui->SponsoredProjectRadioButton->isChecked())?0:1;
    QString ID = LoginManager::Instance()->addResearchProject(ResearchProject(ui->ProjectNameLineEdit->text(), ui->projectfacultyLineEdit->text(), ui->ProjectSponsorLineEdit->text(), type));
    if(QMessageBox::information(this, "Research Project Added", QString("Project ID : ").append(ID).append(" \nSponsor : ").append(ui->ProjectSponsorLineEdit->text()).append("\n").append("Principal Investigator(s)/Consultant(s) : ").append(ui->projectfacultyLineEdit->text()).append(ui->ProjectNameLineEdit->text()), QMessageBox::Ok, QMessageBox::Ok)==QMessageBox::Ok)
    {
        ui->ProjectNameLineEdit->clear();
        ui->projectfacultyLineEdit->clear();
        ui->ProjectSponsorLineEdit->clear();
        ui->SponsoredProjectRadioButton->setChecked(false);
        ui->ConsultancyProjectRadioButton->setCheckable(false);
        ui->stackedWidget->setCurrentIndex(1);
    }
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

        if(QMessageBox::information(this, "Data Successfully Submitted", "Transaction has been successfull registered. You will be redirected to Main Page.", QMessageBox::Ok, QMessageBox::Ok)==QMessageBox::Ok)
        {
            ui->AccountsAmountLineEdit->clear();
            ui->AccountsUniversityGrantRadio->setChecked(false);
            ui->AccountsConsultancyProjectGrantRadio->setChecked(false);
            ui->AccountsProjectLabel->setEnabled(false);
            ui->AccountsProjectsComboBox->setEnabled(false);
            ui->AccountsProjectsComboBox->clear();
            ui->stackedWidget->setCurrentIndex(1);
        }
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
        if((QMessageBox::information(this, "Data Successfully Submitted", "You hava been successfully registered. You will be redirected to Main Page."), QMessageBox::Ok, QMessageBox::Ok)==QMessageBox::Ok)
        {
            ui->SignUpAddressTextEdit->clear();
            ui->SignUpBloodGroupLineEdit->clear();
            ui->SignUpConfirmPasswordLineEdit->clear();
            ui->SignUpPasswordLineEdit->clear();
            ui->SignUpRollNoLineEdit->clear();
            ui->stackedWidget->setCurrentIndex(0);
        }
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
            if(QMessageBox::information(this, "Data Successfully Submitted", ui->CourseRegisterRollNoLineEdit->text().append(" has been successfully registered with the courses.\nYou will be redirected to Main Page."), QMessageBox::Ok, QMessageBox::Ok)==QMessageBox::Ok)
            {
                ui->CourseRegisterDepthCoursesListWidget->clear();
                ui->CourseRegisterAllDepthCoursesListWidget->clear();
                ui->CourseRegisterBacklogCoursesListWidget->clear();
                ui->CourseRegisterRollNoLineEdit->clear();
                ui->stackedWidget->setCurrentIndex(1);
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
    ui->EnterGradesTableWidget->clear();
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
    if(QMessageBox::information(this, "Data Successfully Submitted", "Grades have been seuccessfull entered. You will be redirected to Main Page.", QMessageBox::Ok, QMessageBox::Ok)==QMessageBox::Ok)
    {
        ui->EnterGradesTableWidget->clear();
        ui->stackedWidget->setCurrentIndex(1);
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

void MainWindow::on_manageInventoryButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(10);
    ui->InventoryStackedWidget_2->setCurrentIndex(0);
}

void MainWindow::on_InventoryAddInventoryButton_clicked()
{
    ui->InventoryAddItemRoomComboBox->clear();
    QStringList list = LoginManager::Instance()->getRooms();
    int i;
    for(i=0;i<list.count();i++)
    {
        ui->InventoryAddItemRoomComboBox->addItem(list.at(i));
    }
    ui->InventoryStackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_InventoryListInventoryButton_clicked()
{
    QStringList rooms = LoginManager::Instance()->getRooms();
    QStringList list;
    QStandardItemModel *model = new QStandardItemModel;
    int i,j;
    for(i=0;i<rooms.count();i++)
    {
        QStandardItem *group = new QStandardItem(rooms.at(i));
        list = LoginManager::Instance()->getInventoryDetails(rooms.at(i));
        for(j=0;j<list.count();j=j+4)
        {
            QStandardItem *item = new QStandardItem(QString("Item : ").append(list.at(j+1)));
            group->appendRow(item);
            item->appendRow(new QStandardItem(QString("Name : ").append(list.at(j+2))));
            item->appendRow(new QStandardItem(QString("Price : Rs. ").append(list.at(j+3))));
        }
        model->appendRow(group);
    }
    ui->InventoryListItemsTreeView->setModel(model);

    ui->InventoryStackedWidget_2->setCurrentIndex(2);
}

void MainWindow::on_InventoryAddItemButton_clicked()
{
    if(LoginManager::Instance()->InsertTransaction(Transaction(ui->InventoryAddItemPriceLineEdit_2->text().toInt(), 0, ui->InventoryAddItemRoomComboBox->currentText().append(" : ").append(ui->InventoryAddItemDescriptionLineEdit->text()))))
    {
        LoginManager::Instance()->insertInventoryItem(InventoryItem(ui->InventoryAddItemDescriptionLineEdit->text(), ui->InventoryAddItemRoomComboBox->currentText(), ui->InventoryAddItemTypeComboBox->currentIndex(), ui->InventoryAddItemPriceLineEdit_2->text().toInt()));
        if(QMessageBox::information(this, "Data Successfully Submitted", "Inventory Item added successfully.", QMessageBox::Ok, QMessageBox::Ok)==QMessageBox::Ok)
        {
            ui->InventoryAddItemDescriptionLineEdit->clear();
            ui->InventoryAddItemPriceLineEdit_2->clear();
            ui->stackedWidget->setCurrentIndex(1);
        }
    }
    else
    {
        QMessageBox::warning(this, QString("Out of Funds"), QString("The given transaction cannot be made. The Department would become out of funds."), QMessageBox::Ok, QMessageBox::Ok);
    }
}


void MainWindow::on_StudentProfileEditButton_clicked()
{
    ui->StudentProfileStackedWidget->setCurrentIndex(1);
    ui->EditProfileRollLineEdit->setText(ui->StudentProfileRollNoLabel->text());
    ui->EditProfileRollLineEdit->setEnabled(false);
    Student student = LoginManager::Instance()->getStudentDetails(ui->EditProfileRollLineEdit->text());
    ui->EditProfileAddressTextArea->setPlainText(student._address);
    ui->EditProfileBloodLineedit->setText(student._bloodGroup);
}

void MainWindow::on_EditProfileSaveChangesButton_clicked()
{
    LoginManager::Instance()->updateStudentDetails(ui->EditProfileRollLineEdit->text(), ui->EditProfileAddressTextArea->toPlainText(), ui->EditProfileBloodLineedit->text());
    if(QMessageBox::information(this, "Data Successfully Submitted", "Student Details were Successfully Updated.", QMessageBox::Ok, QMessageBox::Ok)==QMessageBox::Ok)
    {
        ui->StudentProfileStackedWidget->setCurrentIndex(0);
    }
}

void MainWindow::on_StudentProfileLogoutButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_StudentProfileViewDetailButton_clicked()
{
    QList<SubjectPerformanceDetails> list;
    int i=1, j=0;
    while(true)
    {
        list = StudentDatabaseManager::Instance()->getSemesterDetails(ui->StudentProfileRollNoLabel->text(), i);
        if(list.count()>0)
        {
            ui->StudentProfileTableWidget->insertRow(ui->StudentProfileTableWidget->rowCount());
            ui->StudentProfileTableWidget->setItem(ui->StudentProfileTableWidget->rowCount()-1, 0, new QTableWidgetItem(QString("Semester %1").arg(i)));

            ui->StudentProfileTableWidget->insertRow(ui->StudentProfileTableWidget->rowCount());
            ui->StudentProfileTableWidget->insertRow(ui->StudentProfileTableWidget->rowCount());
            ui->StudentProfileTableWidget->setItem(ui->StudentProfileTableWidget->rowCount()-1, 0, new QTableWidgetItem(QString("SUBJECT")));
            ui->StudentProfileTableWidget->setItem(ui->StudentProfileTableWidget->rowCount()-1, 1, new QTableWidgetItem(QString("CREDITS")));
            ui->StudentProfileTableWidget->setItem(ui->StudentProfileTableWidget->rowCount()-1, 2, new QTableWidgetItem(QString("GRADE")));
            for(j=0;j<list.count();j++)
            {

                ui->StudentProfileTableWidget->insertRow(ui->StudentProfileTableWidget->rowCount());
                ui->StudentProfileTableWidget->setItem(ui->StudentProfileTableWidget->rowCount()-1, 0, new QTableWidgetItem(list.at(j)._courseCode));
                ui->StudentProfileTableWidget->setItem(ui->StudentProfileTableWidget->rowCount()-1, 1, new QTableWidgetItem(QString("%1").arg(list.at(j)._credits)));
                ui->StudentProfileTableWidget->setItem(ui->StudentProfileTableWidget->rowCount()-1, 2, new QTableWidgetItem(list.at(j)._grade));
            }
            ui->StudentProfileTableWidget->insertRow(ui->StudentProfileTableWidget->rowCount());
            ui->StudentProfileTableWidget->insertRow(ui->StudentProfileTableWidget->rowCount());
            ui->StudentProfileTableWidget->setItem(ui->StudentProfileTableWidget->rowCount()-1, 0, new QTableWidgetItem(QString("SGPA = %1").arg(StudentDatabaseManager::Instance()->generateSGPA(ui->StudentProfileRollNoLabel->text(), i))));
            ui->StudentProfileTableWidget->setItem(ui->StudentProfileTableWidget->rowCount()-1, 1, new QTableWidgetItem(QString("CGPA = %1").arg(StudentDatabaseManager::Instance()->generateCGPAuptoSem(ui->StudentProfileRollNoLabel->text(), i))));
            ui->StudentProfileTableWidget->insertRow(ui->StudentProfileTableWidget->rowCount());
        }
        else
        {
            break;
        }
        i++;
    }
    ui->StudentProfileStackedWidget->setCurrentIndex(2);
}

void MainWindow::on_searchButton_clicked()
{
    ui->SearchTableWidget_2->clear();
    QString keyword = ui->searchLineEdit->text();
    ui->searchLineEdit->clear();
    QList<Student> list = LoginManager::Instance()->SearchStudents(keyword);
    int i;
    for(i=0;i<list.count();i++)
    {
        ui->SearchTableWidget_2->insertRow(ui->SearchTableWidget_2->rowCount());
        ui->SearchTableWidget_2->setItem(ui->SearchTableWidget_2->rowCount()-1, 0, new QTableWidgetItem(list.at(i)._rollNo));
        ui->SearchTableWidget_2->setItem(ui->SearchTableWidget_2->rowCount()-1, 1, new QTableWidgetItem(list.at(i)._name));
        ui->SearchTableWidget_2->setItem(ui->SearchTableWidget_2->rowCount()-1, 2, new QTableWidgetItem(list.at(i)._course));
    }
    ui->stackedWidget->setCurrentIndex(12);
}

void MainWindow::on_SearchGoBackButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_3_clicked()
{
    QVector<ResearchProject> list = LoginManager::Instance()->findResearchProjects();
    QStringList stringList;
    int i;
    for(i=0;i<list.count();i++)
    {
        stringList.append(QString("\nProject Name : ").append(list.at(i)._name).append("\nSponsor : ").append(list.at(i)._sponsor).append("\nInvestigator : ").append(list.at(i)._faculty));
    }
    ui->AllViewResearchProjectsListView->setModel(new QStringListModel(stringList));
    ui->stackedWidget->setCurrentIndex(13);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(14);
    QVector<ResearchPaper> list = LoginManager::Instance()->findResearchPapers();
    QStringList stringList;
    int i;
    for(i=0;i<list.count();i++)
    {
        stringList.append(QString("\nPaper Name :").append(list.at(i)._name).append("\nAuthor : ").append(list.at(i)._author).append("\nJournal : ").append(list.at(i)._journal));
    }
    ui->AllViewResearchPapersListView->setModel(new QStringListModel(stringList));
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
