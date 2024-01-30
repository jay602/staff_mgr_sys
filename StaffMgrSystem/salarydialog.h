#ifndef SALARYDIALOG_H
#define SALARYDIALOG_H

#include <QDialog>

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

private slots:
    void on_pushButtonCommit_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::SalaryDialog *ui;
    int m_type =  1;  // 1--add 2--delete  3-modify
};

#endif // SALARYDIALOG_H
