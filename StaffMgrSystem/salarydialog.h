#ifndef SALARYDIALOG_H
#define SALARYDIALOG_H

#include <QDialog>
#include "StData.h"

namespace Ui {
class SalaryDialog;
}

class SalaryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SalaryDialog(QWidget *parent = nullptr);
    ~SalaryDialog();

    void setType(int type);
    void setSalary(StSalary& data);

private slots:
    void on_pushButtonCommit_clicked();

    void on_pushButtonCancel_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

private:
    bool addSalary();
    bool deleteSalary();

private:
    Ui::SalaryDialog *ui;
    int m_type =  1;  // 1--add 2--delete  3-modify
};

#endif // SALARYDIALOG_H
