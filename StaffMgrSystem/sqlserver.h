#ifndef SQLSERVER_H
#define SQLSERVER_H

#include <QSql>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QSqlTableModel>
#include "singleton.hpp"
#include "clerk.h"
#include "StData.h"

class SqlServer
{
public:
    SqlServer();
    bool initSql();
    bool registerUser(QString name,QString password,QString role);
    bool loginUser(QString name,QString password);
    bool insertStock(QString name,QString Scategory,QString Scount,QString Saddr,QString Smanu,QString Snote);
    bool queryClerkInfoByUserId(int userID, Clerk& clerk);
    bool queryAllDeparment(QStringList& departments);
    bool updateClerkInfo(Clerk& clerk);
    bool addClerkInfo(Clerk& clerk);
    bool updateClerkInfo2(Clerk& clerk);
    bool queryAllDeparment(QMap<int, QString>& departmentMap);
    bool addUser(QString userName, QString pwd, int& id);
    bool isExistUserName(QString userName);

    bool GetAttendanceName(int type, QString& name);
    bool GetClerkName(int id, QString& name);
    bool GetClerkIdList(QStringList& idList);
    bool GetAttendanceNameMap(QMap<int, QString>& AttendanceMap);
    bool AddAttendance(StAttendance& data);

    bool AddSalary(StSalary& data);

private:
    QSqlQuery *query = nullptr;
    QSqlDatabase db;
    QSqlTableModel* m_model = nullptr;
};

typedef Singleton<SqlServer> SqlServerInstance;

#endif // SQLSERVER_H
