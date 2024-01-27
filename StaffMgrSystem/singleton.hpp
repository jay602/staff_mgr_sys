#ifndef SINGLETON_H
#define SINGLETON_H
#include <QAtomicPointer>
#include <QMutex>

template <class T>
class Singleton
{
public:
    static T &GetRef()
	{
#ifndef Q_ATOMIC_POINTER_TEST_AND_SET_IS_ALWAYS_NATIVE
		if(!QAtomicPointer::isTestAndSetNative())//运行时检测
			qDebug() << "Error: TestAndSetNative not supported!";
#endif

		//使用双重检测。

		/*! testAndSetOrders操作保证在原子操作前和后的的内存访问
		 * 不会被重新排序。
		 */
		if(instance.testAndSetOrdered(0, 0))//第一次检测
		{
			QMutexLocker locker(&mutex);//加互斥锁。

			instance.testAndSetOrdered(0, new T());//第二次检测。
		}

		return *instance;
	}
private:
    Singleton(const Singleton<T> &);//禁止拷贝构造函数。
    Singleton<T> & operator=(const Singleton<T> &);//禁止赋值拷贝函数。


    static QMutex mutex;//实例互斥锁。
    static QAtomicPointer<T> instance;
};

template <class T>
QAtomicPointer<T> Singleton<T>::instance = 0;

template <class T>
QMutex Singleton<T>::mutex;

#endif // SINGLETON_H
