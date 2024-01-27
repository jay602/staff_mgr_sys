#include "logindialog.h"
#include "ui_logindialog.h"
#include "log.h"
#include "globle.h"
#include "sqlserver.h"

#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("职工信息管理系统"));
    ui->label->setFixedWidth(80);
    ui->label_2->setFixedWidth(80);
    ui->lineEditPwd->setEchoMode(QLineEdit::Password);
    setFixedSize(400, 300);

    SqlServerInstance::GetRef().initSql();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pushButtonLogin_clicked()
{
   QString username = ui->lineEditUserName->text();
   QString password = ui->lineEditPwd->text();
   if(username.size() == 0 || password.size() == 0)
   {
        QMessageBox::information(this, "警告", "用户名或密码不能为空");
        return;
   }
    LOG_DEBUG <<"用户名："<<username<<", 密码:"<<password;

    bool T1 = SqlServerInstance::GetRef().loginUser(username, password);

    if(T1 == false)
    {
        QMessageBox::information(this, "警告", "用户名或密码错误");
    }
    else
    {
        accept();
    }
}


void LoginDialog::on_pushButtonExit_clicked()
{
    reject();
}

