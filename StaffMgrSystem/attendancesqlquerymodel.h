#ifndef ATTENDANCESQLQUERYMODEL_H
#define ATTENDANCESQLQUERYMODEL_H

#include <QSqlQueryModel>
#include <QObject>

class AttendanceSqlQueryModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit AttendanceSqlQueryModel(QObject *parent = nullptr);
    QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const;
    void select();
};

#endif // ATTENDANCESQLQUERYMODEL_H
