#include "attendancesqlquerymodel.h"
#include "sqlserver.h"

AttendanceSqlQueryModel::AttendanceSqlQueryModel(QObject *parent) : QSqlQueryModel(parent)
{

}

QVariant AttendanceSqlQueryModel::data(const QModelIndex &index, int role) const
{
    QVariant value = QSqlQueryModel::data(index,role);

    if(role==Qt::DisplayRole &&index.column() == 1)
    {
        int type = value.toInt();
        QString name;
        if(SqlServerInstance::GetRef().GetAttendanceName(type, name))
        {
            value.setValue(name);
        }

        return value;
    }

    if(role==Qt::DisplayRole &&index.column() == 2)
    {
        int id = value.toInt();
        QString name;
        if(SqlServerInstance::GetRef().GetClerkName(id, name))
        {
            value.setValue(name);
        }

        return value;
    }

    if(role == Qt::TextAlignmentRole)
     {
         value = Qt::AlignCenter;   //文本居中
         return value;
     }

    return value;
}

void AttendanceSqlQueryModel::select()
{
    setQuery("select attendance_date, status, clerk_id from attendance");

    setHeaderData(0,Qt::Horizontal,"日期");
    setHeaderData(1,Qt::Horizontal,"考情情况");
    setHeaderData(2,Qt::Horizontal,"员工");
}
