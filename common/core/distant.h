#ifndef KDISTANT_H
#define KDISTANT_H

///Class defining a distant system. A distant system is an interface
///with an other program. The communication is going on through TCP socket.
///An internal thread tries to keep the connection alive (only if this
///distant system was the one initiating the connexion).
///A distant system holds two objects, a sender and a receiver.
///The sender has a ComLink. All the message in the queue of this comLink
///are sent as XML formated message to the system on the other end of the
///socket.
///The receiver is acquiring the incoming XML formated messages. The messages
///are directly forwarded to the mailman.

#include <QtNetwork>
#include <QMutex>
#include <QThread>

#include "pomelog.h"

#include "../utils/xmlbehavior.h"

#include "receiver.h"
#include "sender.h"

namespace ksir {

class Distant : public QThread, public XmlBehavior
{
public:
	//Lifetime
	Distant(int);
	Distant(const QDomNode&);
	~Distant();

	//Access
	const QString& addr() const { return m_addr; }
	int port() const { return m_port; }
	Receiver& getReceiver() { return m_receiver; }
	Sender& getSender() { return m_sender; }

	//QThread
	void run();

private:
	//XML
	void readXml(const QDomNode& p_node, const QString& p_tag);

private:
	QString m_id;
	QString m_addr;
	int m_port;

	bool m_connected;
	bool m_responsible;
	QTcpSocket m_socket;
	QMutex m_mutex;

	Receiver m_receiver;
	Sender m_sender;
};

}

#endif // KDISTANT_H
