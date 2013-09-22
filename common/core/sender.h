#ifndef KSENDER_H
#define KSENDER_H

#include <QtNetwork>
#include <QThread>
#include <QMutex>

#include <pomelog.h>

#include "../utils/comlink.h"
#include "../utils/crypt.h"

class Sender : public QThread, public pLogBehavior
{
public:
	Sender(QTcpSocket*);
	~Sender();

	ComLink& comLink() { return m_comLink; }
	void setCrypt(const Crypt&);

	void run();

private:
	QTcpSocket* m_socket;
	QMutex m_mutex;

	ComLink m_comLink;
	kBlurer* m_blurer;
};

#endif // KSENDER_H
