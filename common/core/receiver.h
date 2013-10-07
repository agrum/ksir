#ifndef KRECEIVER_H
#define KRECEIVER_H

///Class interfacing with an other system through a connected socket.
///This class only manage the receiving part of the process.
///Each time content is available for reading, the receiver will acquire it.
///The header of this content gives the idea of how to process what s
///following (length, encryption).
///The receiver reconstructs the message and send it to the mailman.

#include <QtNetwork>
#include <QThread>
#include <QMutex>

#include <pomelog.h>

#include "../utils/crypt.h"

#include "comlink.h"

namespace ksir {

class Receiver : public QThread, public pLogBehavior
{
public:
	//Lifetime
	Receiver(QTcpSocket*);
	~Receiver();

	//Operation
	void setCrypt(const Crypt&);

	//QThread
	void run();

private:
	QTcpSocket* m_socket;
	QMutex m_mutex;

	kClearer* m_clearer;
};

}

#endif // KRECEIVER_H
