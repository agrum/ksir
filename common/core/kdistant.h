#ifndef KDISTANT_H
#define KDISTANT_H

#include <QtNetwork>
#include <QMutex>
#include <QThread>

#include "pomelog.h"

#include "../utils/comlink.h"
#include "../utils/xmlbehavior.h"

#include "kreceiver.h"
#include "ksender.h"

class kDistant : public QThread, public XmlBehavior
{
public:
	kDistant(int);
	kDistant(const QDomNode&);
	~kDistant();

	const QString& addr() const { return m_addr; }
	int port() const { return m_port; }
	kReceiver& receiver() { return m_receiver; }
	kSender& sender() { return m_sender; }

	//bool isAlive();
	void run();

private:
	//XML
	void to(QDomNode&, const QString&) {}
	void readXml(const QDomNode& p_node, const QString& p_tag);
	void writeXml(QDomNode&) const {}

	static void threadFuncSender(void* p_this);
	static void threadFuncReceiver(void* p_this);

private:
	QString m_id;
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
