//***********************************************
//日志类, 记录日志
//***********************************************
#ifndef UILOG_H
#define UILOG_H

#include <QFile>
#include <QTextStream>
#include <QMutex>

class UiLog
{
public:
    explicit UiLog(QString path, QString logName, QString version);
    ~UiLog();

    int WriteLog(QtMsgType msgType, const QString& msg);

private:
    QString MakeMutiDir(const QString path);

private:
    QFile* m_file;
    QTextStream m_stream;
    QMutex m_mutex;
};

#endif // UILOG_H
