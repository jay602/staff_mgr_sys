#include "clerksqlquerymodel.h"
#include "sqlserver.h"

ClerkSqlQueryModel::ClerkSqlQueryModel(QObject *parent) : QSqlQueryModel(parent)
{

}

QVariant ClerkSqlQueryModel::data(const QModelIndex &index, int role) const
{
    QVariant value = QSqlQueryModel::data(index,role);

    if(role==Qt::DisplayRole &&index.column()==2)
    {
        value = ((value.toInt()==1)?"男":"女");
        return value;

    }

    if(role==Qt::DisplayRole &&index.column()==7)
    {
        QMap<int, QString> departmentMap;
        SqlServerInstance::GetRef().queryAllDeparment(departmentMap);

        if(departmentMap.size())
        {
            int id = value.toInt();
            if(id < departmentMap.size())
            {
                value = departmentMap[id];
            }
        }

        return value;
    }
    return value;
}

void ClerkSqlQueryModel::select()
{
   setQuery("select user_id, name,sex,phone_number,id_card,address, position, department_id, hire_date from clerk");

   setHeaderData(0,Qt::Horizontal,"id");
   setHeaderData(1,Qt::Horizontal,"姓名");
   setHeaderData(2,Qt::Horizontal,"性别");
   setHeaderData(3,Qt::Horizontal,"手机号码");
   setHeaderData(4,Qt::Horizontal,"身份证");
   setHeaderData(5,Qt::Horizontal,"住址");
   setHeaderData(6,Qt::Horizontal,"职位");
   setHeaderData(7,Qt::Horizontal,"部门");
   setHeaderData(8,Qt::Horizontal,"入职时间");
}
