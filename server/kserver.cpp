#include "kserver.h"

kServer::kServer(const QDomNode& p_root):
	kCore(p_root)
{

}

void kServer::run()
{

}

//XML
void kServer::readXml(const QString& p_tag, const QDomElement& p_node)
{
	if(p_tag == XML_SERVER){
		m_serverList.push_back(p_node.text());
		if(p_node.text() == m_addr)
			m_serverList.clear();
	}

}

void kServer::writeXml(QDomNode&, QString)
{

}
