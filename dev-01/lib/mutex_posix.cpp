/**
 * @file    mutex_posix.cpp
 *
 * multex implementation for posix.
 *
 *
 */


#include <pthread.h>


class MutexImpl
{
protected:
    MutexImpl();
    MutexImpl(bool fast);
    ~MutexImpl();
    void lockImpl();
    bool tryLockImpl();
    bool tryLockImpl(long milliseconds);
    void unlockImpl();

private:
    pthread_mutex_t _mutex;
};


/**
 * Constructor.
 *
 * @param
 * @throw
 */
MutexImpl::MutexImpl()
{
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);

	if (pthread_mutex_init(&_mutex, &attr))
	{
		pthread_mutexattr_destroy(&attr);
		throw SystemException("cannot create mutex");
	}
	pthread_mutexattr_destroy(&attr);
}



class Mutex: private MutexImpl
{

};
