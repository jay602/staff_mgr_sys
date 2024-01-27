#ifndef DBHELPER_H
#define DBHELPER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include "singleton.hpp"
#include "globle.h"
#include "clerk.h"

class DBHelper2 : public QObject
{
    Q_OBJECT
public:
    DBHelper2(QObject *parent = nullptr);
    bool QueryClerkInfoByUserId(int userID, Clerk& clerk);

private:
    void init_db();


private:
    QSqlDatabase* db;
    QSqlTableModel* m_model;
};


typedef Singleton<DBHelper2> DBHelperInstance;

#endif // DBHELPER_H
