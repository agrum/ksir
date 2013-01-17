#include "ktcpserver.h"

kTcpServer::kTcpServer(QObject *parent):
	QTcpServer(parent)
{
}

bool kTcpServer::hasSocketDesc()
{
	return !m_socketDescList.empty();
}

int kTcpServer::socketDesc()
{
	return m_socketDescList.takeFirst();
}

void kTcpServer::incomingConnection(int p_socketDesc)
{
	m_socketDescList.push_back(p_socketDesc);
}
