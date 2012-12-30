#ifndef KDISTANT_H
#define KDISTANT_H

#include <QtNetwork>
#include <QThread>

#include "kcore.h"

class kDistant : public kCore, public QThread
{
public:
	kDistant(QTcpSocket*);
	kDistant(const QDomNode&);
	~kDistant();

	//XML
	virtual void readXml(const QString&, const QDomElement&);
	virtual void writeXml(QDomNode&);

	void run();

private:
	kDistant(const kDistant&): kCore(), QThread() {}
	kDistant& operator=(const kDistant&) { return *this; }

private:
	bool m_responsible;
	QTcpSocket* m_socket;
};

#endif // KDISTANT_H
