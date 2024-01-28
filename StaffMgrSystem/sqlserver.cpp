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

bool SqlServer::queryAllDeparment(QStringList &departments)
{
    if (!db.open())
    {
        LOG_DEBUG << "<queryAllDeparment> Failed to connect to root mysql admin";
        return false;
    }

    if(!query)
        return false;

    query->exec("select name from department");
    while(query->next())
    {
        QString name = query->value(0).toString();
        departments << name;
    }

    LOG_DEBUG << "<queryAllDeparment> deparments=" << departments;

    return departments.size() > 0;
}

bool SqlServer::updateClerkInfo(Clerk &clerk)
{
    if (!db.open())
    {
        LOG_DEBUG << "<updateClerkInfo> Failed to connect to root mysql admin";
        return false;
    }

    if(!query)
        return false;


    m_model->setTable("clerk");
    m_model->setFilter("user_id = " + QString::number(clerk.user_id));
    m_model->select();
    LOG_DEBUG << "<updateClerkInfo> rowCount = " << m_model->rowCount();
    if(m_model->rowCount() == 1)
    {
        QSqlRecord record = m_model->record(0);
        record.setValue('name', clerk.name);
        record.setValue('sex', clerk.sex);
        record.setValue('phone_number', clerk.phone_number);
        record.setValue('id_card', clerk.id_card);
        record.setValue('address', clerk.address);
        record.setValue('position', clerk.position);
        record.setValue('department_id', clerk.department_id);
        record.setValue('hire_date', clerk.hire_date);
        m_model->setRecord(0, record);
        m_model->database().transaction();
        if(m_model->submitAll())
        {
            LOG_DEBUG << "<updateClerkInfo> submitAll success, clerk id=" << clerk.user_id << "," << clerk.name << clerk.address;
            if(m_model->database().commit())
            {
                LOG_DEBUG << "<updateClerkInfo> commit success";
                return true;
            }
            m_model->database().rollback();
            LOG_DEBUG << "<updateClerkInfo> commit error:" << m_model->lastError().text();
            return false;
        }
        else
        {
             LOG_DEBUG << "<updateClerkInfo> submitAll failed, clerk id=" << clerk.user_id << "," << clerk.name;
             LOG_DEBUG << "<updateClerkInfo> error:" << m_model->lastError().text();
             return false;
        }
    }


}

bool SqlServer::updateClerkInfo2(Clerk &clerk)
{
    if (!db.open())
    {
        LOG_DEBUG << "<updateClerkInfo> Failed to connect to root mysql admin";
        return false;
    }

    if(!query)
        return false;

    QString hire_date = clerk.hire_date.toString("yyyy-MM-dd");
    QString updateSql = QString("update clerk set name='%1',sex='%2',phone_number='%3',id_card='%4',address='%5',position='%6',department_id='%7',hire_date='%8' where user_id='%9'")
         .arg(clerk.name).arg(clerk.sex).arg(clerk.phone_number).arg(clerk.id_card).arg(clerk.address)
         .arg(clerk.position).arg(clerk.department_id).arg(hire_date).arg(clerk.user_id);
     LOG_DEBUG << "sql:" << updateSql;
     if(query->exec(updateSql))
            return true;

    LOG_DEBUG << "<updateClerkInfo2> update failed: " << clerk.user_id << "," << clerk.name;
    LOG_WARNING << "<updateClerkInfo2> error: "<< db.lastError().text();
    return false;
}
