#ifndef KDISTANT_H
#define KDISTANT_H

#include <QtNetwork>
#include <QThread>
#include <QMutex>
#include <QTime>
#include "pomelog.h"

#include "kcore.h"
#include "kmsg.h"

class kDistant : public kCore, public QThread, public pLogBehavior
{
public:
	kDistant(const kCore*, int);
	kDistant(const kCore*, const QDomNode&);
	~kDistant();

	int port() const { return m_port; }

	bool alive();
	bool sendMsg(QList<kMsg>);
	QList<kMsg> getMsg();

	void run();

	//XML
	virtual void readXml(const QString&, const QDomElement&);
	virtual void writeXml(QDomNode&) {}

private:
	kDistant(const kDistant&): kCore(), QThread(), pLogBehavior() {}
	kDistant& operator=(const kDistant&) { return *this; }

private:
	const kCore* m_core;

	QString m_addr;
	int m_port;
	QTime m_time;
	QByteArray m_msgStack;

	QList <kMsg> m_sendList;
	QList <kMsg> m_receiveList;
	QMutex m_mutex;

	bool m_connected;
	bool m_responsible;
	int m_socketDesc;
	QTcpSocket* m_socket;
};

#endif // KDISTANT_H
