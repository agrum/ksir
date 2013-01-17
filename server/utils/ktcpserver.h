#ifndef KTCPSERVER_H
#define KTCPSERVER_H

#include <QtNetwork>

class kTcpServer : public QTcpServer
{
	Q_OBJECT

public:
	explicit kTcpServer(QObject *parent = 0);


	bool hasSocketDesc();
	int socketDesc();

private:
	void incomingConnection(int);

private:
	QList<int> m_socketDescList;
};

#endif // KTCPSERVER_H
