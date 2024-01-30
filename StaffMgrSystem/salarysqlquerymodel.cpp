#include "salarysqlquerymodel.h"
#include "sqlserver.h"

SalarySqlQueryModel::SalarySqlQueryModel(QObject *parent) : QSqlQueryModel(parent)
{

}

QVariant SalarySqlQueryModel::data(const QModelIndex &index, int role) const
{
    QVariant value = QSqlQueryModel::data(index,role);

    if(role==Qt::DisplayRole &&index.column() == 0)
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

void SalarySqlQueryModel::select()
{
    setQuery("select clerk_id, year, month, basic_pay, butie_pay, kouchu_pay, yingfa_pay, shifa_pay from salary");

    setHeaderData(0,Qt::Horizontal,"员工");
    setHeaderData(1,Qt::Horizontal,"年份");
    setHeaderData(2,Qt::Horizontal,"月份");
    setHeaderData(3,Qt::Horizontal,"基本工资");
    setHeaderData(4,Qt::Horizontal,"补贴工资");
    setHeaderData(5,Qt::Horizontal,"扣除工资");
    setHeaderData(6,Qt::Horizontal,"应发工资");
    setHeaderData(7,Qt::Horizontal,"实发工资");
}
