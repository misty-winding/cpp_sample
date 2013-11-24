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

}



class Mutex: private MutexImpl
{

};
