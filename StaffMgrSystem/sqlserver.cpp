#include "sqlserver.h"
#include "log.h"
#include "globle.h"

#include <QSqlRecord>

SqlServer::SqlServer()
{

}

bool SqlServer::initSql()
{
    db = QSqlDatabase::addDatabase("QMYSQL");   //数据库驱动类型为SQL Server
    LOG_DEBUG << "ODBC driver?"<<db.isValid();
    QString dsn = QString::fromLocal8Bit("staffmgr");          //数据源名称
    db.setHostName("localhost");                            //选择本地主机，127.0.1.1
    db.setDatabaseName(dsn);                                //设置数据源名称
    db.setUserName(sqluser);                                   //登录用户
    db.setPassword(sqlpass);                                  //密码
    if (!db.open())
    {
        LOG_WARNING << db.lastError().text();
        QMessageBox::critical(nullptr,QObject::tr("Databaseerror"),db.lastError().text());
        return false;
    }
    else
    {
         m_model = new QSqlTableModel(nullptr, db);
         query = new QSqlQuery(db);
         LOG_DEBUG <<"database open success!";
         return true;
    }
}

//注册输入信息
bool SqlServer::registerUser(QString name,QString password,QString role)
{
    query =  new QSqlQuery;
    QString str = QString("insert into Manager(Maccount,Mpassword,Mrole) values('%1','%2','%3')").arg(name).arg(password).arg(role);
    if(!query->exec(str))
        return false;
    return true;
}

//登录读取信息
bool SqlServer::loginUser(QString name,QString password)
{
   query->exec("select id, username,password, is_admin from user");
   while(query->next())
   {
      int user_id = query->value(0).toInt();
      QString user = query->value(1).toString();
      QString pass = query->value(2).toString();
      bool is_admin = query->value(3).toBool();
      if(name.compare(user) == 0 &&
         password.compare(pass) == 0)
       {
          password_qj = password;
          username_qj = name;
          g_is_admin = is_admin;
          g_user_id = user_id;
          return true;
       }
   }
    return false;
}

bool SqlServer::insertStock(QString name,QString category,QString count,QString addr,QString manu,QString note)
{
    query=new QSqlQuery;
    QString str = QString("insert into Stock values('%1', '%2', '%3','%4','%5','%6')").arg(name).arg(category).arg(count).arg(addr).arg(manu).arg(note);
    if(!query->exec(str))
        return false;
    return true;
}

bool SqlServer::queryClerkInfoByUserId(int userID, Clerk &clerk)
{
    if (!db.open())
    {
        LOG_DEBUG << "<queryClerkInfoByUserId> Failed to connect to root mysql admin";
        return false;
    }
    m_model->setTable("clerk");
    m_model->setFilter("user_id = " + QString::number(userID));
    m_model->select();
    LOG_DEBUG << "<queryClerkInfoByUserId> rowCount=" << m_model->rowCount();
    if(m_model->rowCount())
    {
        QSqlRecord record = m_model->record(0);
        clerk.user_id = userID;
        clerk.name = record.value("name").toString();
        clerk.phone_number = record.value("phone_number").toString();
        clerk.id_card = record.value("id_card").toString();
        clerk.address = record.value("address").toString();
        clerk.position = record.value("position").toString();
        clerk.id = record.value("id").toInt();
        clerk.sex = record.value("sex").toInt();
        clerk.department_id = record.value("department_id").toInt();
        clerk.hire_date = record.value("hire_date").toDate();

        m_model->setTable("department");
        m_model->setFilter("id = " + QString::number(clerk.department_id));
        m_model->select();
        if(m_model->rowCount() == 1)
        {
            QSqlRecord record1 = m_model->record(0);
            clerk.department_name = record1.value("department_name").toString();
        }

        LOG_DEBUG << "<queryClerkInfoByUserId> query clerk success: user_id =" << userID << ", name =" << clerk.name;
        return true;
    }

    LOG_DEBUG << "<queryClerkInfoByUserId> query clerk failed: user_id =" << userID;
    return false;
}
