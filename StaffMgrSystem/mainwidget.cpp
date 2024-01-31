#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "addclerkdialog.h"
#include "adduserdialog.h"
#include "attendancedialog.h"
#include "salarydialog.h"
#include "log.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    setWindowTitle("职工信息管理");
    ui->widget->setFixedWidth(250);
    this->setMinimumSize(1600, 800);
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
   // QHBoxLayout *layout = new QHBoxLayout();
    ui->tableViewSalary->horizontalHeader()->sectionResizeMode(QHeaderView::Stretch);
    ui->tableViewSalary->resizeRowsToContents();

    //ui->tableViewSalary->resizeColumnsToContents();

    ui->tableViewSalary->verticalHeader()->setHidden(true);
    ui->tableViewSalary->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewSalary->setSelectionMode(QAbstractItemView::SingleSelection);

    m_pSalaryModel = new SalarySqlQueryModel(this);
    m_pSalaryModel->select();

   //设置模型
    ui->tableViewSalary->setModel(m_pSalaryModel);
   // layout->addLayout(ui->verticalLayout_3);
   // ui->page_3->setLayout(layout);
    ui->tableViewSalary->setFixedWidth(1400);
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
         refreshSalary();
    }
}


void MainWidget::on_BtnDeleteSalary_clicked()
{
   QModelIndex index = ui->tableViewSalary->currentIndex();

   if(index.isValid())
   {
       int curRow = index.row();
       StSalary salary;
       salary.clerk_id = m_pSalaryModel->index(curRow, 0).data().toInt();
       salary.clerk_name = m_pSalaryModel->index(curRow, 1).data().toString();
       salary.year = m_pSalaryModel->index(curRow, 2).data().toInt();
       salary.month = m_pSalaryModel->index(curRow, 3).data().toInt();
       salary.basic_pay = m_pSalaryModel->index(curRow, 4).data().toInt();
       salary.butie_pay = m_pSalaryModel->index(curRow, 5).data().toInt();
       salary.kouchu_pay = m_pSalaryModel->index(curRow, 6).data().toInt();
       salary.yingfa_pay = m_pSalaryModel->index(curRow, 7).data().toInt();
       salary.shifa_pay = m_pSalaryModel->index(curRow, 8).data().toInt();

       SalaryDialog dialog;
       dialog.setType(2);
       dialog.setSalary(salary);
       if(dialog.exec() == QDialog::Accepted)
       {
           initSalaryTableview();
       }
   }
   else
   {
       LOG_DEBUG << "<on_BtnDeleteSalary_clicked> index is not valid";
       QMessageBox::information(this, "警告", "请选择要删除的数据");
   }
}


void MainWidget::on_BtnModifySalary_clicked()
{

}

void MainWidget::refreshSalary()
{
    m_pSalaryModel->select();
    ui->tableViewSalary->setModel(m_pSalaryModel);
}

