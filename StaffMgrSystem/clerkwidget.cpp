#include "clerkwidget.h"
#include "ui_clerkwidget.h"
#include "sqlserver.h"

ClerkWidget::ClerkWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClerkWidget)
{
    ui->setupUi(this);
    ui->lineEditName->setEnabled(false);
    ui->lineEditAddr->setEnabled(false);
    ui->lineEditPhone->setEnabled(false);
    ui->lineEditPosition->setEnabled(false);
    ui->lineEditIdCard->setEnabled(false);
    ui->comboBoxSex->setEnabled(false);
    ui->comboBoxDepartment->setEnabled(false);
    ui->dateEditHireDate->setEnabled(false);

    QStringList sexList;
    sexList << "女" << "男";
    ui->comboBoxSex->addItems(sexList);

    setWindowTitle("员工信息");
}

ClerkWidget::~ClerkWidget()
{
    delete ui;
}

void ClerkWidget::SetUserId(int user_id)
{
    bool ret = SqlServerInstance::GetRef().queryClerkInfoByUserId(user_id, m_clerk);
    if(ret)
    {
        QStringList departments;
        bool ret1 = SqlServerInstance::GetRef().queryAllDeparment(departments);
        if(ret1)
        {
            ui->comboBoxDepartment->addItems(departments);
        }
        m_iUserId = user_id;
        ui->labelUserId->setText(QString::number(m_iUserId));
        ui->lineEditName->setText(m_clerk.name);
        ui->lineEditAddr->setText(m_clerk.address);
        ui->lineEditPhone->setText(m_clerk.phone_number);
        ui->lineEditPosition->setText(m_clerk.position);
        ui->lineEditIdCard->setText(m_clerk.id_card);
        ui->comboBoxSex->setCurrentIndex(m_clerk.sex);
        ui->comboBoxDepartment->setCurrentIndex(m_clerk.department_id);
        ui->dateEditHireDate->setDate(m_clerk.hire_date);
    }
}

void ClerkWidget::on_pushButtonExit_clicked()
{
    qApp->quit();
}


void ClerkWidget::on_pushButtonEdit_clicked()
{
    m_isEdited = !m_isEdited;
    if(m_isEdited)
    {
        ui->pushButtonEdit->setText("确认");
        ui->lineEditName->setEnabled(true);
        ui->lineEditAddr->setEnabled(true);
        ui->lineEditPhone->setEnabled(true);
        ui->lineEditPosition->setEnabled(true);
        ui->lineEditIdCard->setEnabled(true);
        ui->comboBoxSex->setEnabled(true);
        ui->comboBoxDepartment->setEnabled(true);
        ui->dateEditHireDate->setEnabled(true);
    }
    else
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
        ui->pushButtonEdit->setText("编辑");
        ui->lineEditName->setEnabled(false);
        ui->lineEditAddr->setEnabled(false);
        ui->lineEditPhone->setEnabled(false);
        ui->lineEditPosition->setEnabled(false);
        ui->lineEditIdCard->setEnabled(false);
        ui->comboBoxSex->setEnabled(false);
        ui->comboBoxDepartment->setEnabled(false);
        ui->dateEditHireDate->setEnabled(false);

        m_clerk.name = name;
        m_clerk.address = addr;
        m_clerk.phone_number = phone;
        m_clerk.position = position;
        m_clerk.id_card = id_card;
        m_clerk.sex = ui->comboBoxSex->currentIndex();
        m_clerk.department_id =  ui->comboBoxDepartment->currentIndex();
        m_clerk.hire_date = ui->dateEditHireDate->date();
        bool ret = SqlServerInstance::GetRef().updateClerkInfo2(m_clerk);
        if(ret)
        {
            QMessageBox::information(this, tr("个人信息"), tr("信息修改成功!!!"));
        }
        else
        {
            QMessageBox::information(this, tr("个人信息"), tr("信息修改失败!!!"));

        }
    }
}

