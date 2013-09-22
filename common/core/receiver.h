#ifndef KRECEIVER_H
#define KRECEIVER_H

#include <QtNetwork>
#include <QThread>
#include <QMutex>

#include <pomelog.h>

#include "../utils/comlink.h"
#include "../utils/crypt.h"

class Receiver : public QThread, public pLogBehavior
{
public:
	Receiver(QTcpSocket*);
	~Receiver();

	void setCrypt(const Crypt&);

	void run();

private:
	QTcpSocket* m_socket;
	QMutex m_mutex;

	kClearer* m_clearer;
};

#endif // KRECEIVER_H
