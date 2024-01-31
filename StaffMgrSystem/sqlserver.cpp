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

bool SqlServer::addClerkInfo(Clerk &clerk)
{
    if (!db.open())
    {
        LOG_DEBUG << "<addClerkInfo> Failed to connect to root mysql admin";
        return false;
    }

    if(!query)
        return false;
    LOG_DEBUG << "<addClerkInfo> user_id=" << clerk.user_id << ", department_id=" << clerk.department_id;
    QString hire_date = clerk.hire_date.toString("yyyy-MM-dd");
    QString sql = QString("INSERT INTO `clerk` (`name`, `sex`, `phone_number`, `id_card`, `address`, `position`, `department_id`, `user_id`, `hire_date`) VALUES ('%1', '%2', '%3', '%4', '%5', '%6', '%7', %8, '%9')").arg(clerk.name) \
            .arg(clerk.sex).arg(clerk.phone_number).arg(clerk.id_card).arg(clerk.address).arg(clerk.position).arg(clerk.department_id).arg(clerk.user_id).arg(hire_date);

    LOG_DEBUG << "sql:" << sql;
    if(!query->exec(sql))
    {
        LOG_CRITICAL << "<addClerkInfo> excec sql error: " << query->lastError();
        return false;
    }

    return true;
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

bool SqlServer::queryAllDeparment(QMap<int, QString>& departmentMap)
{
    if (!db.open())
    {
        LOG_DEBUG << "<queryAllDeparment> Failed to connect to root mysql admin";
        return false;
    }

    if(!query)
        return false;

    query->exec("select id, name from department");
    departmentMap.clear();
    while(query->next())
    {
        int id = query->value(0).toInt();
        QString name = query->value(1).toString();
        departmentMap[id] = name;
    }


    return departmentMap.size() > 0;
}

bool SqlServer::addUser(QString userName, QString pwd, int& id)
{
    if (!db.open())
    {
        LOG_DEBUG << "<addUser> Failed to connect to root mysql admin";
        return false;
    }

    if(!query)
        return false;

    ;
    QString sql = QString("INSERT INTO `user` (`username`, `password`, `is_admin`) VALUES ('%1', '%2', 0)").arg(userName).arg(pwd);
    LOG_DEBUG << "sql : " << sql;
    if(!query->exec(sql))
    {
        LOG_CRITICAL << "<addUser> excec sql error: " << query->lastError();
        return false;
    }

    if(query->exec("SELECT LAST_INSERT_ID()"))
    {
        query->next();
        id = query->value(0).toInt();
        LOG_DEBUG << "<addUser> id = " << id;

    }

    return true;
}

bool SqlServer::isExistUserName(QString userName)
{
    if (!db.open())
    {
        LOG_DEBUG << "<isExistUserName> Failed to connect to root mysql admin";
        return false;
    }

    if(!query)
        return false;

    QString sql = QString("select * from user where username='%1'").arg(userName);
    LOG_DEBUG << "sql :" << sql;
    if(!query->exec(sql))
    {
        LOG_CRITICAL << "<isExistUserName> excec sql error: " << query->lastError();
        return false;
    }

    LOG_DEBUG << "<isExistUserName> query.size = " << query->size();

    return query->size() > 0;
}

bool SqlServer::GetAttendanceName(int type, QString& name)
{
    if (!db.open())
    {
        LOG_DEBUG << "<GetAttendanceName> Failed to connect to root mysql admin";
        return false;
    }

    if(!query)
        return false;

    QString sql = QString("select name from attendance_name where id='%1'").arg(type);
    LOG_DEBUG << "sql :" << sql;
    if(!query->exec(sql))
    {
        LOG_CRITICAL << "<GetAttendanceName> excec sql error: " << query->lastError();
        return false;
    }

    query->next();
    name = query->value(0).toString();
    LOG_DEBUG << "<GetAttendanceName> attendance_name = " << name;
    return true;
}

bool SqlServer::GetClerkName(int id, QString &name)
{
    if (!db.open())
    {
        LOG_DEBUG << "<GetClerkName> Failed to connect to root mysql admin";
        return false;
    }

    if(!query)
        return false;

    QString sql = QString("select name from clerk where id='%1'").arg(id);
    LOG_DEBUG << "sql :" << sql;
    if(!query->exec(sql))
    {
        LOG_CRITICAL << "<GetClerkName> excec sql error: " << query->lastError();
        return false;
    }

    query->next();
    name = query->value(0).toString();
    LOG_DEBUG << "<GetClerkName> clerk_name = " << name;
    return true;
}

bool SqlServer::GetClerkIdList(QStringList& idList)
{
    if (!db.open())
    {
        LOG_DEBUG << "<GetClerkIdList> Failed to connect to root mysql admin";
        return false;
    }

    if(!query)
        return false;

    QString sql = QString("select id from clerk");
    LOG_DEBUG << "sql :" << sql;
    if(!query->exec(sql))
    {
        LOG_CRITICAL << "<GetClerkIdList> excec sql error: " << query->lastError();
        return false;
    }

    while(query->next())
    {
        idList << query->value(0).toString();
    }

    LOG_DEBUG << "<GetClerkIdList> idList = " << idList;
    return true;
}

bool SqlServer::GetAttendanceNameMap(QMap<int, QString> &AttendanceMap)
{
    if (!db.open())
    {
        LOG_DEBUG << "<GetAttendanceNameMap> Failed to connect to root mysql admin";
        return false;
    }

    if(!query)
        return false;

    QString sql = QString("select id, name from attendance_name");
    LOG_DEBUG << "sql :" << sql;
    if(!query->exec(sql))
    {
        LOG_CRITICAL << "<GetAttendanceNameMap> excec sql error: " << query->lastError();
        return false;
    }

    AttendanceMap.clear();
    while(query->next())
    {
        int id =  query->value(0).toInt();
        QString name =  query->value(1).toString();
        AttendanceMap[id] = name;
    }

    LOG_DEBUG << "<GetAttendanceNameMap> AttendanceMap = " << AttendanceMap;
    return AttendanceMap.size() > 0;
}

bool SqlServer::AddAttendance(StAttendance &data)
{
    if (!db.open())
    {
        LOG_DEBUG << "<AddAttendance> Failed to connect to root mysql admin";
        return false;
    }

    if(!query)
        return false;

    QString sql = QString("INSERT INTO `attendance` (`status`, `attendance_date`, `clerk_id`) VALUES ('%1', '%2', %3);").arg(data.status).arg(data.date).arg(data.clerk_id);
    LOG_DEBUG << "sql :" << sql;
    if(!query->exec(sql))
    {
        LOG_CRITICAL << "<AddAttendance> excec sql error: " << query->lastError();
        return false;
    }
    return true;
}

bool SqlServer::AddSalary(StSalary &data)
{
    if (!db.open())
    {
        LOG_DEBUG << "<AddSalary> Failed to connect to root mysql admin";
        return false;
    }

    if(!query)
        return false;

    QString sql = QString("INSERT INTO `salary` (`clerk_id`, `year`, `month`, `basic_pay`, `butie_pay`, `kouchu_pay`, `yingfa_pay`, `shifa_pay`) VALUES ('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8');")
            .arg(data.clerk_id).arg(data.year).arg(data.month).arg(data.basic_pay).arg(data.butie_pay).arg(data.kouchu_pay).arg(data.yingfa_pay).arg(data.shifa_pay);
    LOG_DEBUG << "sql :" << sql;
    if(!query->exec(sql))
    {
        LOG_CRITICAL << "<AddSalary> excec sql error: " << query->lastError();
        return false;
    }
    return true;
}

bool SqlServer::GetAllSalary(QList<StSalary> &data)
{
    if (!db.open())
    {
        LOG_DEBUG << "<GetAllSalary> Failed to connect to root mysql admin";
        return false;
    }

    if(!query)
        return false;

    QString sql = "select clerk_id, year, month, basic_pay, butie_pay, kouchu_pay, yingfa_pay, shifa_pay from salary";
    LOG_DEBUG << "sql :" << sql;
    if(!query->exec(sql))
    {
        LOG_CRITICAL << "<GetAllSalary> excec sql error: " << query->lastError();
        return false;
    }

    data.clear();
    LOG_DEBUG << "<GetAllSalary> record count = " << query->record().count();
    while(query->next())
    {
        StSalary salary;
        salary.clerk_id =  query->value(0).toInt();
        salary.year =  query->value(1).toInt();
        salary.month = query->value(2).toInt();
        salary.basic_pay =  query->value(3).toInt();
        salary.butie_pay =  query->value(4).toInt();
        salary.kouchu_pay =  query->value(5).toInt();
        salary.yingfa_pay =  query->value(6).toInt();
        salary.shifa_pay =  query->value(7).toInt();
//        QString name;
//        if(GetClerkName(salary.clerk_id, name))
//        {
//            salary.clerk_name = name;
//        }
        LOG_DEBUG << "<GetAllSalary> salary clerk_id=" <<  salary.clerk_id << ", year=" << salary.year << ", month=" << salary.month;
        data.push_back(salary);
    }

    for(auto iter = data.begin(); iter != data.end(); iter++)
    {
        int clerkId = iter->clerk_id;
        QString name;
        if(GetClerkName(clerkId, name))
        {
            iter->clerk_name = name;
        }
    }

//    foreach(StSalary item, data)
//    {
//        LOG_DEBUG << "<GetAllSalary> name = " << item.clerk_name;
//    }
    LOG_DEBUG << "<GetAllSalary> size = " << data.size();
    return data.size() > 0;
}

