#ifndef ADDCLERKDIALOG_H
#define ADDCLERKDIALOG_H

#include <QDialog>

namespace Ui {
class AddClerkDialog;
}

class AddClerkDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddClerkDialog(QWidget *parent = nullptr);
    ~AddClerkDialog();
    void setUserId(int id) { id_ = id;}

private:
    Ui::AddClerkDialog *ui;
    int id_;
};

#endif // ADDCLERKDIALOG_H
