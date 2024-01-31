#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QSqlQueryModel>
#include "clerksqlquerymodel.h"
#include "attendancesqlquerymodel.h"
#include "salarysqlquerymodel.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

     void initClerkTableview();
     void initAttendanceTableview();
     void initSalaryTableview();

private slots:
     void on_pushButtonAdd_clicked();

     void on_pushButtonClerk_clicked();

     void on_pushButtonAttendance_clicked();

     void on_pushButtonSalary_clicked();

     void on_BtnAddAttendance_clicked();

     void on_BtnDeleteAttendance_clicked();

     void on_BtnModidyAttendance_clicked();

     void on_BtnAddSalary_clicked();

     void on_BtnDeleteSalary_clicked();

     void on_BtnModifySalary_clicked();

private:
     void refreshSalary();

private:
    Ui::MainWidget *ui;
    ClerkSqlQueryModel* m_pClerkQuery;
    AttendanceSqlQueryModel* m_pAttenceQuery;
    SalarySqlQueryModel* m_pSalaryModel;
};

#endif // MAINWIDGET_H
