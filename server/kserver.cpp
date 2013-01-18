#include "kserver.h"

kServer::kServer(const QDomNode& p_root):
	kCore(p_root)
{
	from(p_root);
	for(int i = 0; i < m_distantList.size(); i++)
		m_distantList[i]->start();

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
		if(m_tcpServer.hasSocketDesc()){
			qDebug() << "lalala";
			kDistant* tmp = new kDistant(this, m_tcpServer.socketDesc());
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

		for(int i = 0; i < m_distantList.size(); i++){
			m_distantList[i]->getMsg();
		}

		msleep(100);
	}
}

//XML
void kServer::readXml(const QString& p_tag, const QDomElement& p_node)
{
	if(p_tag == XML_DATABASE){
		m_database.from(p_node);
		m_database.open();
	}
	else if(p_tag == XML_SERVER){
		kDistant* tmp = new kDistant(this, p_node);
		if(*tmp == *this){
			qDebug() << m_tcpServer.listen(QHostAddress::Any, tmp->port()) << tmp->port();
			while(!m_distantList.empty())
				delete m_distantList.takeFirst();
		}
		else
			m_distantList.push_back(tmp);
	}

}
