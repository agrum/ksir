#ifndef KCLIENTUIMNGR_H
#define KCLIENTUIMNGR_H

#include <QThread>
#include "pomelog.h"

#include "ksir_common.h"

#include "kclientwidget.h"

class kClientUIMngr : public QThread, public pLogBehavior
{
public:
	kClientUIMngr(kQueueW&);
	~kClientUIMngr();

	void run();

	inline kQueueW& queue() { return *(kQueueW*) &m_queue; }

private:
	kQueueR m_queue;
	kClientWidget m_widget;
	kQueueW& m_sysQueue;
};

#endif // KCLIENTUIMNGR_H
