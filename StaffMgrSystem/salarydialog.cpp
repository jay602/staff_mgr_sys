#include "salarydialog.h"
#include "ui_salarydialog.h"

#include "sqlserver.h"
#include "log.h"
#include <QMessageBox>



SalaryDialog::SalaryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SalaryDialog)
{
    ui->setupUi(this);
    setWindowTitle("添加员工的工资情况");
    QStringList idList;
    SqlServerInstance::GetRef().GetClerkIdList(idList);
    if(idList.size())
    {
        ui->comboBoxClerkId->addItems(idList);
        connect(ui->comboBoxClerkId, SIGNAL(currentIndexChanged(QString)), this, SLOT(on_comboBox_currentIndexChanged(QString)));
        QString strClerkId = ui->comboBoxClerkId->currentText();
        int id = strClerkId.toInt();
        QString name;
        if(SqlServerInstance::GetRef().GetClerkName(id, name))
        {
            ui->lineEditName->setText(name);
        }
    }
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
        setWindowTitle("添加员工的工资信息");
    }
    else if(m_type == 2)
    {
        setWindowTitle("删除员工的工资信息");
    }
    else if(m_type == 3)
    {
         setWindowTitle("修改员工的工资信息");
    }
}

void SalaryDialog::setSalary(StSalary& data)
{

}

void SalaryDialog::on_pushButtonCommit_clicked()
{
    StSalary salary;
    salary.clerk_id = ui->comboBoxClerkId->currentText().toInt();

    bool ok;
    int year = ui->lineEditYear->text().toInt(&ok, 10);
    if(!ok || year < 1900)
    {
        QMessageBox::information(this, "警告", "请输入正确的年份");
        return;
    }

    salary.year = year;

    int month = ui->lineEditMonth->text().toInt(&ok, 10);
    if(!ok || month < 0 || month > 12)
    {
        QMessageBox::information(this, "警告", "请输入正确的月份");
        return;
    }

    salary.month = month;

    int basic = ui->lineEditBasic->text().toInt(&ok, 10);
    if(!ok || basic < 0)
    {
        QMessageBox::information(this, "警告", "请输入正确的基本工资");
        return;
    }

    salary.basic_pay = basic;

    int butie = ui->lineEditButie->text().toInt(&ok, 10);
    if(!ok || butie < 0)
    {
        QMessageBox::information(this, "警告", "请输入正确的补贴工资");
        return;
    }

    salary.butie_pay = butie;

    int kouchu = ui->lineEditKouchu->text().toInt(&ok, 10);
    if(!ok || kouchu < 0)
    {
        QMessageBox::information(this, "警告", "请输入正确的扣除工资");
        return;
    }

    int yingfa = ui->lineEditYingfa->text().toInt(&ok, 10);
    if(!ok || yingfa < 0)
    {
        QMessageBox::information(this, "警告", "请输入正确的应发工资");
        return;
    }

    salary.yingfa_pay = yingfa;

    int shifa = ui->lineEditShifa->text().toInt(&ok, 10);
    if(!ok || shifa < 0)
    {
        QMessageBox::information(this, "警告", "请输入正确的实发工资");
        return;
    }

    salary.shifa_pay = shifa;

    if(SqlServerInstance::GetRef().AddSalary(salary))
    {
        QMessageBox::information(this, "信息", "添加员工的工资信息成功");
        accept();
    }
    else
    {
        QMessageBox::information(this, "信息", "添加员工的工资信息成功");
        reject();
    }
}


void SalaryDialog::on_pushButtonCancel_clicked()
{
    reject();
}

void SalaryDialog::on_comboBox_currentIndexChanged(const QString &arg1)
{
    LOG_DEBUG << "<on_comboBox_currentIndexChanged> arg1= " << arg1;
    QString strClerkId = ui->comboBoxClerkId->currentText();
    LOG_DEBUG << "<on_comboBox_currentIndexChanged> strClerkId =" << strClerkId;
    int id = strClerkId.toInt();
    QString name;
    if(SqlServerInstance::GetRef().GetClerkName(id, name))
    {
        ui->lineEditName->setText(name);
    }
}

