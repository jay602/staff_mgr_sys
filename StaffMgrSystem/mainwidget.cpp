#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "addclerkdialog.h"
#include "adduserdialog.h"
#include "attendancedialog.h"
#include "salarydialog.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    setWindowTitle("职工信息管理");
    ui->widget->setFixedWidth(250);
    this->setMinimumSize(1550, 800);
    initClerkTableview();
    initAttendanceTableview();
    initSalaryTableview();
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::initClerkTableview()
{
    ui->tableViewClerk->resizeRowsToContents();
    ui->tableViewClerk->resizeColumnsToContents();
    ui->tableViewClerk->verticalHeader()->setHidden(true);
    ui->tableViewClerk->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableViewClerk->setSelectionMode(QAbstractItemView::SingleSelection);

    m_pClerkQuery = new ClerkSqlQueryModel(this);
    m_pClerkQuery->select();

   //设置模型
    ui->tableViewClerk->setModel(m_pClerkQuery);
}

void MainWidget::initAttendanceTableview()
{
    ui->tableViewAttendance->resizeRowsToContents();
    ui->tableViewAttendance->resizeColumnsToContents();
    ui->tableViewAttendance->verticalHeader()->setHidden(true);
    ui->tableViewAttendance->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableViewAttendance->setSelectionMode(QAbstractItemView::SingleSelection);

    m_pAttenceQuery = new AttendanceSqlQueryModel(this);
    m_pAttenceQuery->select();

   //设置模型
    ui->tableViewAttendance->setModel(m_pAttenceQuery);
}

void MainWidget::initSalaryTableview()
{
     ui->tableViewSalary->setFixedWidth(1400);
    ui->tableViewSalary->resizeRowsToContents();

    ui->tableViewSalary->resizeColumnsToContents();

    ui->tableViewSalary->verticalHeader()->setHidden(true);
    ui->tableViewSalary->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewSalary->setSelectionMode(QAbstractItemView::SingleSelection);

    m_pSalaryModel = new SalarySqlQueryModel(this);
    m_pSalaryModel->select();

   //设置模型
    ui->tableViewSalary->setModel(m_pSalaryModel);
}

void MainWidget::on_pushButtonAdd_clicked()
{
    AddUserDialog dialog1;
    if(dialog1.exec() == QDialog::Accepted)
    {
        int id = dialog1.GetUserId();
        AddClerkDialog dialog2;
        dialog2.setUserId(id);
        if(dialog2.exec() == QDialog::Accepted)
        {
            m_pClerkQuery->select();
        }
    }
}


void MainWidget::on_pushButtonClerk_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWidget::on_pushButtonAttendance_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
}


void MainWidget::on_pushButtonSalary_clicked()
{
     ui->stackedWidget->setCurrentIndex(2);
}


void MainWidget::on_BtnAddAttendance_clicked()
{
    AttendanceDialog dialog;
    if(dialog.exec() == QDialog::Accepted)
    {
        m_pAttenceQuery->select();
    }
}


void MainWidget::on_BtnDeleteAttendance_clicked()
{

}


void MainWidget::on_BtnModidyAttendance_clicked()
{

}


void MainWidget::on_BtnAddSalary_clicked()
{
    SalaryDialog dialog;
    if(dialog.exec() == QDialog::Accepted)
    {
        m_pAttenceQuery->select();
    }
}


void MainWidget::on_BtnDeleteSalary_clicked()
{

}


void MainWidget::on_BtnModifySalary_clicked()
{

}

