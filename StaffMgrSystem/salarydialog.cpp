#include "salarydialog.h"
#include "ui_salarydialog.h"

#include "sqlserver.h"
#include "log.h"
#include <QDate>

SalaryDialog::SalaryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SalaryDialog)
{
    ui->setupUi(this);
    setWindowTitle("添加员工的工资情况");
}

SalaryDialog::~SalaryDialog()
{
    delete ui;
}

void SalaryDialog::setType(int type)
{
    m_type = type;
    if(m_type == 1)
    {
        setWindowTitle("添加员工的工资情况");
    }
    else if(m_type == 2)
    {
        setWindowTitle("删除员工的工资情况");
    }
    else if(m_type == 3)
    {
         setWindowTitle("修改员工的工资情况");
    }
}

void SalaryDialog::on_pushButtonCommit_clicked()
{

}


void SalaryDialog::on_pushButtonCancel_clicked()
{

}

