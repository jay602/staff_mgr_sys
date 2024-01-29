#ifndef ADDUSERDIALOG_H
#define ADDUSERDIALOG_H

#include <QDialog>

namespace Ui {
class AddUserDialog;
}

class AddUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddUserDialog(QWidget *parent = nullptr);
    ~AddUserDialog();
    int GetUserId() { return id; }

private slots:
    void on_pushButtonCommit_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::AddUserDialog *ui;
    int id;
};

#endif // ADDUSERDIALOG_H
