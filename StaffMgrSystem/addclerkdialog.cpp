#include "addclerkdialog.h"
#include "ui_addclerkdialog.h"
#include "sqlserver.h"
#include "clerk.h"
#include "log.h"

AddClerkDialog::AddClerkDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddClerkDialog)
{
    ui->setupUi(this);
    QStringList sexList;
    sexList << "女" << "男";
    ui->comboBoxSex->addItems(sexList);
    QStringList departments;
    bool ret1 = SqlServerInstance::GetRef().queryAllDeparment(departments);
    if(ret1)
    {
        ui->comboBoxDepartment->addItems(departments);
    }

    setWindowTitle("编辑员工信息");
}

AddClerkDialog::~AddClerkDialog()
{
    delete ui;
}

void AddClerkDialog::on_pushButtonOk_clicked()
{
    QString name = ui->lineEditName->text();
    QString addr = ui->lineEditAddr->text();
    QString phone = ui->lineEditPhone->text();
    QString position = ui->lineEditPhone->text();
    QString id_card = ui->lineEditIdCard->text();

    if(name.isEmpty() && addr.isEmpty() &&
       phone.isEmpty() && position.isEmpty() &&
       id_card.isEmpty())
    {
        QMessageBox::critical(this, tr("错误"), tr("信息不能为空!!!"));
              return;
        return;
    }

    Clerk m_clerk;
    m_clerk.user_id = id_;
    m_clerk.name = name;
    m_clerk.address = addr;
    m_clerk.phone_number = phone;
    m_clerk.position = position;
    m_clerk.id_card = id_card;
    m_clerk.sex = ui->comboBoxSex->currentIndex();
    m_clerk.department_id =  ui->comboBoxDepartment->currentIndex();
    m_clerk.hire_date = ui->dateEditHireDate->date();
    bool ret = SqlServerInstance::GetRef().addClerkInfo(m_clerk);

    if(ret)
    {
        QMessageBox::information(this, tr("员工信息"), tr("添加成功"));
        accept();
    }
    else
    {
        QMessageBox::critical(this, tr("员工信息"), tr("添加失败"));
        return;
    }
}


void AddClerkDialog::on_pushButtonCancel_clicked()
{
    reject();
}

