#ifndef SALARYSQLQUERYMODEL_H
#define SALARYSQLQUERYMODEL_H

#include <QSqlQueryModel>

class SalarySqlQueryModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit SalarySqlQueryModel(QObject *parent = nullptr);
    QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const;
    void select();
};

#endif // SALARYSQLQUERYMODEL_H
