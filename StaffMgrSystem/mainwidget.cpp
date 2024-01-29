#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "addclerkdialog.h"
#include "adduserdialog.h"

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
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::initClerkTableview()
{
    ui->tableViewClerk->resizeRowsToContents();
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

