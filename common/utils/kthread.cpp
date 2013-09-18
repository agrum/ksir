#include "kthread.h"

#include "assert.h"

kThread::kThread(void (*p_func)(void*), void* p_arg):
m_func(p_func),
m_arg(p_arg),
m_stop(false),
m_running(false)
{
	pthread_create(&m_thread, NULL, &threadLife, (void*) p_arg);
}

kThread::~kThread()
{
	bool running;

	m_lock.lock();
		m_stop = true;
		running = m_running;
	m_lock.unlock();

	if(running)
		pthread_join(m_thread, NULL);
}

void
kThread::execOnce()
{
	m_lock.lock();
		assert(!m_running);

		m_stop = true;
		m_running = true;
	m_lock.unlock();

	pthread_create(&m_thread, NULL, &threadLife, (void*) this);
}

void
kThread::execLoop()
{
	m_lock.lock();
		assert(!m_running);

		m_running = true;
	m_lock.unlock();

	pthread_create(&m_thread, NULL, &threadLife, (void*) this);
}

void
kThread::stop()
{
	m_lock.lock();
		m_stop = true;
	m_lock.unlock();
}

bool
kThread::isTerminated()
{
	bool running;

	m_lock.lock();
		running = m_running;
	m_lock.unlock();

	return running;
}

void
kThread::waitTermination()
{
	bool running;

	m_lock.lock();
		running = m_running;
	m_lock.unlock();

	if(running)
		pthread_join(m_thread, NULL);
}

void*
kThread::threadLife(void* p_this)
{
	kThread* owner = (kThread*) p_this;
	bool stop;

	do
	{
		owner->m_lock.lock();
			(*owner->m_func)(owner->m_arg);
			stop = owner->m_stop;
		owner->m_lock.unlock();
	}while(!stop);

	owner->m_lock.lock();
		owner->m_running = false;
	owner->m_lock.unlock();

	pthread_exit(NULL);
}

