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

#include "kclientuimngr.h"

class kClient : public kCore, public QThread, public pLogBehavior
{
public:
	kClient(const QDomNode&);
	~kClient();

	void run();

	//XML
	virtual void readXml(const QString&, const QDomElement&);

private:
	void manageQueue();

private:
	QList<kDistant*> m_serverList;
	kDistant* m_currentServer;

	kQueueR m_queue;
	kClientUIMngr m_uiMngr;
};

#endif // KCLIENT_H
