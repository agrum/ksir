#ifndef KSENDER_H
#define KSENDER_H

#include <QtNetwork>
#include <QThread>
#include <QMutex>

#include <pomelog.h>

#include "kcomlink.h"
#include "../utils/kcrypt.h"

class kSender : public QThread, public pLogBehavior
{
public:
	kSender(QTcpSocket*);
	~kSender();

	kComLink& comLink() { return m_comLink; }
	void setCrypt(const kCrypt&);

	void run();

private:
	QTcpSocket* m_socket;
	QMutex m_mutex;

	kComLink m_comLink;
	kBlurer* m_blurer;
};

#endif // KSENDER_H
