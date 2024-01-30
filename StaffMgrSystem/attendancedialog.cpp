#include "attendancedialog.h"
#include "ui_attendancedialog.h"
#include "sqlserver.h"
#include "log.h"
#include <QDate>

AttendanceDialog::AttendanceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AttendanceDialog)
{
    ui->setupUi(this);
    QStringList idList;
    SqlServerInstance::GetRef().GetClerkIdList(idList);
    if(idList.size())
    {
        ui->comboBoxClerkId->addItems(idList);
        connect(ui->comboBoxClerkId, SIGNAL(currentIndexChanged(QString)), this, SLOT(on_comboBox_currentIndexChanged2(QString)));
    }

    QMap<int, QString> attenceMap;
    SqlServerInstance::GetRef().GetAttendanceNameMap(attenceMap);
    if(attenceMap.size())
    {
        foreach(const int &id,attenceMap.keys())
            ui->comboBoxAttence->addItem(attenceMap.value(id), id);
        connect(ui->comboBoxAttence, SIGNAL(currentIndexChanged(QString)), this, SLOT(on_comboBox_currentIndexChanged(QString)));
    }
    setWindowTitle("添加考勤情况");
    setFixedSize(500, 400);
}

AttendanceDialog::~AttendanceDialog()
{
    delete ui;
}

void AttendanceDialog::on_comboBox_currentIndexChanged(const QString &arg1)
{
    int id = ui->comboBoxAttence->currentData().toInt();
    m_addtendanceId =  id;
    LOG_DEBUG << "<on_comboBox_currentIndexChanged> m_addtendanceId= " << m_addtendanceId;
}

void AttendanceDialog::on_comboBox_currentIndexChanged2(const QString &arg1)
{
    LOG_DEBUG << "<on_comboBox_currentIndexChanged2> arg1= " << arg1;
    QString strClerkId = ui->comboBoxClerkId->currentText();
    LOG_DEBUG << "<on_comboBox_currentIndexChanged2> strClerkId =" << strClerkId;
    int id = strClerkId.toInt();
    QString name;
    if(SqlServerInstance::GetRef().GetClerkName(id, name))
    {
        ui->lineEditClerkName->setText(name);
    }
}

void AttendanceDialog::setType(int type)
{
    m_type = type;
    if(type == 1)
    {
        setWindowTitle("添加考勤情况");
    }
    else if(type == 2)
    {
        setWindowTitle("删除考勤情况");
    }
    else if(type == 3)
    {
        setWindowTitle("修改考勤情况");
    }
}

void AttendanceDialog::on_BtnCommitAttendance_clicked()
{
    StAttendance data;
    data.clerk_id = ui->comboBoxClerkId->currentText().toInt();
    data.status = ui->comboBoxAttence->currentData().toInt();
    QDate dd = ui->dateEdit->date();
    data.date = dd.toString("yyyy-MM-dd");

   // if(m_type == 1)
    {
        SqlServerInstance::GetRef().AddAttendance(data);
    }
}


void AttendanceDialog::on_BtnCancelAtten_clicked()
{
    reject();
}

