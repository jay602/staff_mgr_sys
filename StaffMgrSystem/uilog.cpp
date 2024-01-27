#include "uilog.h"

#include <QDir>
#include <QDateTime>

UiLog::UiLog(QString path, QString logName, QString version) : m_file(NULL)
{
    QString date = QDate::currentDate().toString("yyyyMMdd");
    QString rootPath = path + date;
    QDir logDir(rootPath);
    if(!logDir.exists())
        MakeMutiDir(rootPath);

    QString BackerLog = rootPath + "/" + logName;

    m_file = new QFile(BackerLog);
    m_file->open(QIODevice::WriteOnly | QIODevice::Append);

    m_stream.setDevice(m_file);

    m_stream << version << "Start programe\n";
}

UiLog::~UiLog()
{
    if(m_file)
    {
        m_file->flush();
        m_file->close();
        m_file->deleteLater();
    }
}


int UiLog::WriteLog(QtMsgType msgType, const char* msg)
{
    m_mutex.lock();
    m_stream << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");
    m_stream << QString::fromLocal8Bit(msg) << '\n';
 //   m_stream << msg << '\n';
    m_stream.flush();
    m_mutex.unlock();

    return 0;
}

QString UiLog::MakeMutiDir(const QString path)
{
    QDir dir(path);
    if ( dir.exists(path))
        return path;

    QString parentDir = MakeMutiDir(path.mid(0,path.lastIndexOf('/')));
    QString dirname = path.mid(path.lastIndexOf('/') + 1);
    QDir parentPath(parentDir);
    if ( !dirname.isEmpty() )
        parentPath.mkpath(dirname);
    return parentDir + "/" + dirname;
}
