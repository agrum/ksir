#include "kserver.h"

kServer::kServer(const QDomNode& p_root):
	kCore(p_root)
{
	start();
}

void kServer::run()
{
	//Pending sockets
	while(m_tcpServer.hasPendingConnections()){
		m_socketMap.insert(kCore (), m_tcpServer.nextPendingConnection());
	}
}

//XML
void kServer::readXml(const QString& p_tag, const QDomElement& p_node)
{
	if(p_tag == XML_SERVER){
		m_serverList.push_back(p_node.text());
		if(p_node.text() == m_addr) //Either connect with all because unknown from all
			m_serverList.clear();	//Either connect the subset after it to avoid double
	}

}

void kServer::writeXml(QDomNode&, QString)
{

}
