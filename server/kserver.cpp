#include "kserver.h"

kServer::kServer(const QDomNode& p_root):
	kCore(p_root)
{
	start();
}

kServer::~kServer()
{
	while(!m_distantList.empty())
		delete m_distantList.takeFirst();
}

void kServer::run()
{

}

//XML
void kServer::readXml(const QString& p_tag, const QDomElement& p_node)
{
	kCore::readXml(p_tag, p_node);
	if(p_tag == XML_SERVER){
		kDistant* tmp = new kDistant(p_node);
		m_distantList.push_back(tmp);
		if(*(m_distantList.last()) == *this) //Either connect with all because unknown from all
			m_distantList.clear();	//Either connect the subset after it to avoid double
	}

}
