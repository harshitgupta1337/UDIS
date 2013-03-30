#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QtGui>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_submitButton_clicked();

    void on_managePublicationsButton_clicked();

    void on_AddResearchPaperPushButton_clicked();

    void on_ViewResearchPaperPushButton_clicked();

    void on_addResearchPaperButton_clicked();

    void on_manageProjectsButton_clicked();

    void on_AddProjectButton_clicked();

    void on_ViewProjectsButton_clicked();

    void on_AddProjectToDatabaseButton_clicked();

    void on_manageAccountsButton_clicked();

    //void on_ConsultancyProjectGrantRadio_clicked();

    //void on_UniversityGrantRadio_clicked();

    void on_AccountsEnterTransactionButton_clicked();

    void on_AccountsUniversityGrantRadio_clicked();

    void on_AccountsConsultancyProjectGrantRadio_clicked();

    void on_AccountsViewDetailsButton_clicked();

    void on_registerPushButton_clicked();

    void on_SignUpRegisterButton_clicked();

    void on_enterRegistrationDetailsButton_clicked();

    void on_CourseRegisterAddToDepthCoursesButton_clicked();

    void on_BacklogsButton_clicked();

    void on_CourseRegisterGoButton_clicked();

    void on_EnterGradesPushButton_clicked();

    void on_EnterGradesFetchGradeSheetButton_clicked();

    void on_EnterGradesSubmitGradesButton_clicked();

    void on_GenerateCGPAPushhButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
