#ifndef KSERVER_H
#define KSERVER_H

#include <QMap>
#include <QFile>
#include <QThread>
#include <QtNetwork>
#include <QtXml>

#include "../common/core/kcore.h"

class kServer : public QThread, public kCore
{
public:
	kServer(QFile&);

	void run();

	//XML
	virtual void readXml(const QDomNode&);
	virtual void writeXml(QDomNode&, QString);

private:
	QTcpServer m_tcpServer;
	QMap <kCore, QTcpSocket*> m_socketMap;
};

#endif // KSERVER_H
