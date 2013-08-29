#ifndef KQUEUE_H
#define KQUEUE_H

#include <QMutex>
#include <QQueue>

#include "kmsg.h"

class kQueueW : public QQueue<kMsg>
{
public:
	kQueueW();

	void push(const kMsg&);

protected:
	QMutex m_mutex;
};

class kQueueR : public kQueueW
{
public:
	kQueueR();

	bool pop(kMsg&);
};

#endif // KQUEUE_H
