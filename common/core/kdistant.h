#ifndef KDISTANT_H
#define KDISTANT_H

#include <QtNetwork>
#include <QMutex>
#include <QThread>

#include "pomelog.h"

#include "kcore.h"
#include "kmsg.h"
#include "kcomlink.h"
#include "kreceiver.h"
#include "ksender.h"

class kDistant : public QThread, public kCore, public pLogBehavior
{
public:
	kDistant(int);
	kDistant(const QDomNode&);
	~kDistant();

	int port() const { return m_port; }
	kReceiver& receiver() { return m_receiver; }
	kSender& sender() { return m_sender; }

	//bool isAlive();
	void run();

private:
	//XML
	virtual void readXml(const QString&, const QDomElement&);
	virtual void writeXml(QDomNode&) {} //No export of distant systems

	static void threadFuncSender(void* p_this);
	static void threadFuncReceiver(void* p_this);

private:
	QString m_addr;
	int m_port;

	bool m_connected;
	bool m_responsible;
	QTcpSocket m_socket;
	QMutex m_mutex;

	kReceiver m_receiver;
	kSender m_sender;
};

#define MSG_DISC_SOCK "socket disconnected"
#define MSG_CONN_SOCK "socket connected"

#endif // KDISTANT_H
