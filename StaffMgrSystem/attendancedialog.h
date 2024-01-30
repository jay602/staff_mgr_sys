#ifndef ATTENDANCEDIALOG_H
#define ATTENDANCEDIALOG_H

#include <QDialog>

#include "StData.h"

namespace Ui {
class AttendanceDialog;
}

class AttendanceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AttendanceDialog(QWidget *parent = nullptr);
    ~AttendanceDialog();

private slots:
    void on_BtnCommitAttendance_clicked();
    void on_BtnCancelAtten_clicked();
    void on_comboBox_currentIndexChanged(const QString &arg1);
    void on_comboBox_currentIndexChanged2(const QString &arg1);
    void setType(int type);

private:
    Ui::AttendanceDialog *ui;
    int m_addtendanceId;
    int m_type = 1;  // 1--add  2--delete 3--modify;
};

#endif // ATTENDANCEDIALOG_H
