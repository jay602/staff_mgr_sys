#ifndef STDATA_H
#define STDATA_H

#include<QString>

typedef struct StAttendance
{
    int clerk_id;
    int status;
    QString date;
}StAttendance;

typedef struct StSalary
{
    int clerk_id;
    int year;
    int month;
    int basic_pay;
    int butie_pay;
    int kouchu_pay;
    int yingfa_pay;
    int shifa_pay;
}StSalary;

#endif // STDATA_H
