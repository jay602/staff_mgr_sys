#ifndef CLERK_H
#define CLERK_H

#include <QObject>
#include <QDate>

class Clerk : public QObject
{
    Q_OBJECT
public:
    Clerk(QObject *parent = nullptr);
    int id;
    int department_id;      //部门编号
    int sex;
    int user_id;
    QString name;
    QString department_name;
    QString phone_number;
    QString address;
    QString id_card;
    QString position;       //职位名称
    QDate hire_date;        //入职时间

};

#endif // CLERK_H
