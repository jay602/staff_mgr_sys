#include "dbhelper.h"
#include "log.h"
#include <QSqlRecord>

DBHelper2::DBHelper2(QObject *parent) : QObject(parent)
{

}

bool DBHelper2::QueryClerkInfoByUserId(int userID, Clerk& clerk)
{
    if (!db.open())
    {
        LOG_DEBUG << "<QueryClerkInfoByUserId> Failed to connect to root mysql admin";
        return false;
    }
    m_model->setTable("clerk");
    m_model->setFilter("user_id = " + QString::number(userID));
    m_model->select();
    if(m_model->rowCount() == 1)
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
        return true;
    }

    return false;
}

void DBHelper2::init_db()
{
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

    m_model = new QSqlTableModel(this, db);
}
