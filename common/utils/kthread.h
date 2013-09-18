#ifndef KTHREAD_H
#define KTHREAD_H

#include <pthread.h>

#include <QMutex>
#include <QWaitCondition>

class kThread
{
public:
	kThread(void (*p_func)(void*), void* p_arg);
	~kThread();

	void execOnce();
	void execLoop();

	void stop();
	bool isTerminated();
	void waitTermination();

private:
	static void* threadLife(void* p_arg);

private:
	pthread_t m_thread;
	void (*m_func)(void*);
	void* m_arg;
	bool m_stop;
	bool m_running;
	QMutex m_lock;
};

#endif // KTHREAD_H
