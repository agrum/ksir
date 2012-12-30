#ifndef KDISTANT_H
#define KDISTANT_H

#include <QtNetwork>
#include <QThread>
#include <QMutex>
#include "pomelog.h"

#include "kcore.h"
#include "kmsg.h"

class kDistant : public kCore, public QThread, public pLog
{
public:
	kDistant(QTcpSocket*);
	kDistant(const QDomNode&);
	~kDistant();

	bool sendMsg(QList<kMsg>);
	QList<kMsg> getMsg();

	void run();

	//XML
	virtual void readXml(const QString&, const QDomElement&);
	virtual void writeXml(QDomNode&) {}

private:
	kDistant(const kDistant&): kCore(), QThread() {}
	kDistant& operator=(const kDistant&) { return *this; }

private:
	QString m_addr;
	int m_port;

	QList <kMsg> m_sendList;
	QList <kMsg> m_receiveList;
	QMutex m_mutex;

	bool m_responsible;
	QTcpSocket* m_socket;
};

#endif // KDISTANT_H
