#ifndef KCLIENT_H
#define KCLIENT_H

#include <QMap>
#include <QList>
#include <QFile>
#include <QThread>
#include <QtNetwork>
#include <QtXml>
#include <QPair>
#include "pomelog.h"

#include "ksir_common.h"

using namespace ksir;

class kClient : public XmlBehavior, public QThread
{
public:
	kClient(const QDomNode&);
	~kClient();

	void run();

private:
	//XML
	void readXml(const QDomNode&, const QString&);

private:
	QList<Distant*> m_serverList;
	Distant* m_currentServer;
};

#endif // KCLIENT_H
