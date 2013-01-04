#ifndef KSERVER_H
#define KSERVER_H

#include <QMap>
#include <QList>
#include <QFile>
#include <QThread>
#include <QtNetwork>
#include <QtXml>

#include "ksir_common.h"
#include "utils/kdatabase.h"

class kServer : public kCore, public QThread
{
public:
	kServer(const QDomNode&);
	~kServer();

	void run();

	//XML
	virtual void readXml(const QString&, const QDomElement&);

private:
	kDatabase m_database;
	QTcpServer m_tcpServer;
	QList <kDistant*> m_distantList;
};

#endif // KSERVER_H
