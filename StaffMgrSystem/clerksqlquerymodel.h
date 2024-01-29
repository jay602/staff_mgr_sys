#ifndef CLERKSQLQUERYMODEL_H
#define CLERKSQLQUERYMODEL_H

#include <QSqlQueryModel>

class ClerkSqlQueryModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit ClerkSqlQueryModel(QObject *parent = nullptr);
    QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const;
    void select();
};

#endif // CLERKSQLQUERYMODEL_H
