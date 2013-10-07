#ifndef KSENDER_H
#define KSENDER_H

///This class is an interface with an other system communicating through
///a connected TCP socket.
///It got its own ComLink which is fed by others. All the messages in this
///link are formatted to XML messages and send through the socket.
///The content may be encrypted if a crypter has been set.

#include <QtNetwork>
#include <QThread>
#include <QMutex>

#include <pomelog.h>

#include "../utils/crypt.h"

#include "comlink.h"

namespace ksir {

class Sender : public QThread, public pLogBehavior
{
public:
	//Lifetime
	Sender(QTcpSocket*);
	~Sender();

	//Access
	ComLink& getComLink() { return m_comLink; }

	//Operation
	void setCrypt(const Crypt&);

	//QThread
	void run();

private:
	QTcpSocket* m_socket;
	QMutex m_mutex;

	ComLink m_comLink;
	kBlurer* m_blurer;
};

}

#endif // KSENDER_H
