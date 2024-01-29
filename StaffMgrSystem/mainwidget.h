#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QSqlQueryModel>
#include "clerksqlquerymodel.h"
#include "attendancesqlquerymodel.h"

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

private:
    Ui::MainWidget *ui;
    ClerkSqlQueryModel* m_pClerkQuery;
    AttendanceSqlQueryModel* m_pAttenceQuery;
};

#endif // MAINWIDGET_H
