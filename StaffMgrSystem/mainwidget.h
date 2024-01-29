#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QSqlQueryModel>
#include "clerksqlquerymodel.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

     void initClerkTableview();

private slots:
     void on_pushButtonAdd_clicked();

private:
    Ui::MainWidget *ui;
    ClerkSqlQueryModel* m_pClerkQuery;
};

#endif // MAINWIDGET_H
