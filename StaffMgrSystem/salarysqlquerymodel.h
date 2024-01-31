#ifndef SALARYSQLQUERYMODEL_H
#define SALARYSQLQUERYMODEL_H

#include <QStandardItemModel>

class SalarySqlQueryModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit SalarySqlQueryModel(QObject *parent = nullptr);
   // QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const;
    void select();
};

#endif // SALARYSQLQUERYMODEL_H
