#include "salarysqlquerymodel.h"
#include "sqlserver.h"
#include "log.h"

SalarySqlQueryModel::SalarySqlQueryModel(QObject *parent) : QStandardItemModel(parent)
{

}

//QVariant SalarySqlQueryModel::data(const QModelIndex &index, int role) const
//{
////    QVariant value = QSqlQueryModel::data(index,role);

////    if(role==Qt::DisplayRole &&index.column() == 0)
////    {
////        int id = value.toInt();
////        QString name;
////        if(SqlServerInstance::GetRef().GetClerkName(id, name))
////        {
////            value.setValue(name);
////        }

////        return value;
////    }

////    if(role == Qt::TextAlignmentRole)
////     {
////         value = Qt::AlignCenter;   //文本居中
////         return value;
////     }

//  //  return value;
//}

void SalarySqlQueryModel::select()
{
//    setQuery("select clerk_id, year, month, basic_pay, butie_pay, kouchu_pay, yingfa_pay, shifa_pay from salary");

//    setHeaderData(0,Qt::Horizontal,"员工");
//    setHeaderData(1,Qt::Horizontal,"年份");
//    setHeaderData(2,Qt::Horizontal,"月份");
//    setHeaderData(3,Qt::Horizontal,"基本工资");
//    setHeaderData(4,Qt::Horizontal,"补贴工资");
//    setHeaderData(5,Qt::Horizontal,"扣除工资");
//    setHeaderData(6,Qt::Horizontal,"应发工资");
//    setHeaderData(7,Qt::Horizontal,"实发工资");
    clear();
    QStringList headerList;
    headerList << "ID" << "姓名" << "年份" << "月份" << "基本工资" << "补贴工资" << "扣除工资" << "应发工资" << "实发工资";
    setHorizontalHeaderLabels(headerList);
    QList<StSalary> salaryList;
    bool ret = SqlServerInstance::GetRef().GetAllSalary(salaryList);
    if(ret)
    {
        int row = 0;
        foreach(const StSalary& salary, salaryList)
        {
            LOG_DEBUG << "clerk_id = " << salary.clerk_id << ", year=" << salary.month << ", month=" << salary.month;
            QStandardItem* item0 = new QStandardItem(QString::number(salary.clerk_id));
            item0->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            setItem(row, 0, item0);

            QStandardItem* item1 = new QStandardItem(salary.clerk_name);
            item1->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            setItem(row, 1, item1);

            QStandardItem* item2 = new QStandardItem(QString::number(salary.year));
            item2->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            setItem(row, 2, item2);

            QStandardItem* item3 = new QStandardItem(QString::number(salary.month));
            item3->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            setItem(row, 3, item3);

            QStandardItem* item4 = new QStandardItem(QString::number(salary.basic_pay));
            item4->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            setItem(row, 4, item4);

            QStandardItem* item5 = new QStandardItem(QString::number(salary.butie_pay));
            item5->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            setItem(row, 5, item5);

            QStandardItem* item6 = new QStandardItem(QString::number(salary.kouchu_pay));
            item6->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            setItem(row, 6, item6);

            QStandardItem* item7 = new QStandardItem(QString::number(salary.yingfa_pay));
            item7->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            setItem(row, 7, item7);

            QStandardItem* item8 = new QStandardItem(QString::number(salary.shifa_pay));
            item8->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            setItem(row, 8, item8);
            row++;
        }
    }
}
