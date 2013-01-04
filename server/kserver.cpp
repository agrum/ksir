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
	int err = 0;

	while(!err){
		if(m_tcpServer.hasPendingConnections()){
			kDistant* tmp = new kDistant(m_tcpServer.nextPendingConnection());
			m_distantList.push_front(tmp);
		}

		QList<kCore> distantList;
		for(int i = 0; i < m_distantList.size(); i++){
			kDistant* tmp = m_distantList[i];

			if(!tmp->isNull() && distantList.contains(*tmp))
				m_distantList.removeAt(i--);
			else
				distantList.push_back(*tmp);
		}
	}
}

//XML
void kServer::readXml(const QString& p_tag, const QDomElement& p_node)
{
	kCore::readXml(p_tag, p_node);
	if(p_tag == XML_DATABASE){
		m_database.from(p_node);
		m_database.open();
	}
	else if(p_tag == XML_SERVER){
		kDistant* tmp = new kDistant(p_node);
		m_distantList.push_back(tmp);
		if(*(m_distantList.last()) == *this) //Either connect with all because unknown from all
			m_distantList.clear();	//Either connect the subset after it to avoid double
	}

}
