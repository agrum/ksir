#include "kqueue.h"

kQueueW::kQueueW()
{
}

void kQueueW::push(const kMsg& p_msg)
{
	m_mutex.lock();
	push_back(p_msg);
	m_mutex.unlock();
}

kQueueR::kQueueR()
{
}

bool kQueueR::pop(kMsg& p_msg)
{
	m_mutex.lock();
	if(empty()){
		m_mutex.unlock();
		return false;
	}
	p_msg = first();
	pop_front();
	m_mutex.unlock();
	return true;
}
