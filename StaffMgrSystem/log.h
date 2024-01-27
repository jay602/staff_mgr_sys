#ifndef LOG_H
#define LOG_H

#include <QDebug>

#define LOG_DEBUG qDebug() << __FILE__ << "(" << __LINE__ << "):"
#define LOG_WARNING qWarning() << __FILE__ << "(" << __LINE__ << "):"
#define LOG_CRITICAL qCritical() << __FILE__ << "(" << __LINE__ << "):"
#define LOG_FATAL qFatal() << __FILE__ << "(" << __LINE__ << "):"


#endif // LOG_H
