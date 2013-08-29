#ifndef KDISTANT_H
#define KDISTANT_H

#include <QtNetwork>
#include <QThread>
#include <QMutex>
#include <QTime>
#include "pomelog.h"

#include "../utils/kcommonlogextension.h"
#include "../utils/kcrypt.h"
#include "kcore.h"
#include "kmsg.h"
#include "kqueue.h"

class kDistant : public kCore, public QThread, public pLogBehavior
{
public:
	kDistant(int, kQueueW&);
	kDistant(const QDomNode&, kQueueW&);
	~kDistant();

	int port() const { return m_port; }
	bool mustDestroy() const { return m_mustDestroy; }

	bool alive();
	bool sendMsg(QList<kMsg>);
	QList<kMsg> getMsg();

	void run();

	//XML
	virtual void readXml(const QString&, const QDomElement&);
	virtual void writeXml(QDomNode&) {}

private:
	QString m_addr;
	QString m_sender;
	int m_port;
	QTime m_time;
	QByteArray m_msgStack;
	int m_msgStackSize;

	kQueueW& m_sysQueue;
	QList <kMsg> m_sendList;
	QList <kMsg> m_receiveList;
	QMutex m_mutex;

	bool m_mustDestroy;
	bool m_connected;
	bool m_responsible;
	int m_socketDesc;
	QTcpSocket* m_socket;

	kCrypt* m_crypt;
	bool m_canCrypt;
};

#define MSG_DISC_SOCK "socket disconnected"
#define MSG_CONN_SOCK "socket connected"

#endif // KDISTANT_H
