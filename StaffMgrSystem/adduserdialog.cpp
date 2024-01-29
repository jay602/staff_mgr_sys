#include "adduserdialog.h"
#include "ui_adduserdialog.h"
#include "sqlserver.h"
#include <QMessageBox>
#include "addclerkdialog.h"

AddUserDialog::AddUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUserDialog)
{
    ui->setupUi(this);
    ui->lineEditPwd->setEchoMode(QLineEdit::Password);
    ui->lineEditPwd2->setEchoMode(QLineEdit::Password);
    setWindowTitle("添加用户信息");
}

AddUserDialog::~AddUserDialog()
{
    delete ui;
}

void AddUserDialog::on_pushButtonCommit_clicked()
{
    QString user_name = ui->lineEditUser->text();
    QString pwd = ui->lineEditPwd->text();
    QString pwd2 = ui->lineEditPwd2->text();

    if(user_name.isEmpty() || pwd.isEmpty() || pwd2.isEmpty())
    {
        QMessageBox::critical(this, tr("错误"), tr("用户名或密码不能为空!!!"));
              return;
        return;
    }

    if( pwd != pwd2)
    {
        QMessageBox::critical(this, tr("错误"), tr("密码不一致!!!"));
              return;
        return;
    }

    if(SqlServerInstance::GetRef().isExistUserName(user_name))
    {
        QMessageBox::critical(this, tr("错误"), tr("用户名已存在!!!"));
              return;
        return;
    }

    bool ret = SqlServerInstance::GetRef().addUser(user_name, pwd, id_);
    if(ret)
    {
        QMessageBox::information(this, tr("用户信息"), tr("添加成功"));
        accept();
    }
    else
    {
        QMessageBox::critical(this, tr("用户信息"), tr("添加失败"));
        return;
    }
}


void AddUserDialog::on_pushButtonCancel_clicked()
{
    reject();
}

