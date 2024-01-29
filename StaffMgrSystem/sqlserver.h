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
    bool updateClerkInfo2(Clerk& clerk);
    bool queryAllDeparment(QMap<int, QString>& departmentMap);

private:
    QSqlQuery *query = nullptr;
    QSqlDatabase db;
    QSqlTableModel* m_model = nullptr;
};

typedef Singleton<SqlServer> SqlServerInstance;

#endif // SQLSERVER_H
