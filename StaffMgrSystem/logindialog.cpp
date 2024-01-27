#include "logindialog.h"
#include "ui_logindialog.h"
#include "log.h"
#include "globle.h"

#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("职工信息管理系统"));
    ui->lineEditPwd->setEchoMode(QLineEdit::Password);
    setFixedSize(400, 300);
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
   QSqlDatabase db;
   if(QSqlDatabase::contains("qt_sql_default_connection"))
   {
        db = QSqlDatabase::database("qt_sql_default_connection");
   }
   else
   {
        db = QSqlDatabase::addDatabase("QMYSQL");
   }

   db.setHostName("localhost");
   db.setDatabaseName("staffmgr");
   db.setUserName(sqluser);
   db.setPassword(sqlpass);
    if (!db.open())
    {
        LOG_DEBUG << "Failed to connect to root mysql admin";
        return;
    }

    QSqlQuery query(db);
    query.exec("select id, username,password, is_admin from user");
    bool T1=false;
    while(query.next())
    {
       int user_id = query.value(0).toInt();
       QString user = query.value(1).toString();
       QString pass = query.value(2).toString();
       bool is_admin = query.value(3).toBool();
       qDebug() << user << pass ;
       if(username.compare(user) == 0 &&
          password.compare(pass) == 0)
        {
               password_qj = password;
               username_qj = username;
               g_is_admin = is_admin;
               g_user_id = user_id;
               T1 = true;
               accept();
        }
    }

     if(T1 == false)
     {
         QMessageBox::information(this, "警告", "用户名或密码错误");
     }
}


void LoginDialog::on_pushButtonExit_clicked()
{
    reject();
}

