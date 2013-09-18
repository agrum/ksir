#ifndef KRECEIVER_H
#define KRECEIVER_H

#include <QtNetwork>
#include <QThread>
#include <QMutex>

#include <pomelog.h>

#include "kcomlink.h"
#include "../utils/kcrypt.h"

class kReceiver : public QThread, public pLogBehavior
{
public:
	kReceiver(QTcpSocket*);
	~kReceiver();

	void setCrypt(const kCrypt&);

	void run();

private:
	QTcpSocket* m_socket;
	QMutex m_mutex;

	kClearer* m_clearer;
};

#endif // KRECEIVER_H
