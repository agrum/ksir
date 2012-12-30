#ifndef KSERVER_H
#define KSERVER_H

#include <QMap>
#include <QList>
#include <QFile>
#include <QThread>
#include <QtNetwork>
#include <QtXml>

#include "../common/core/kcore.h"

class kServer : public QThread, public kCore
{
public:
	kServer(const QDomNode&);

	void run();

	//XML
	virtual void readXml(const QString&, const QDomElement&);
	virtual void writeXml(QDomNode&, QString);

private:
	QTcpServer m_tcpServer;
	QMap <kCore, QTcpSocket*> m_socketMap;
	QList <QString> m_serverList;
};

#endif // KSERVER_H
