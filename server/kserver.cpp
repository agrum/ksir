#include "kserver.h"

kServer::kServer(const QDomNode& p_root):
	kCore(p_root)
{
	from(p_root);
	for(int i = 0; i < m_distantList.size(); i++)
		m_distantList[i]->start();

	kMsgHeader::setSender(*(kCore*) this);

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
			kDistant* tmp = new kDistant(m_tcpServer.socketDesc());
			m_distantList.push_front(tmp);
		}

		QList<kCore> distantList;
		for(int i = 0; i < m_distantList.size(); i++){
			kDistant* tmp = m_distantList[i];

			if(tmp->mustDestroy())
				delete m_distantList.takeAt(i--);
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
		m_database.login();
		//m_database.open();
	}
	else if(p_tag == XML_SERVER){
		kDistant* tmp = new kDistant(p_node);
		if(*tmp == *this){
			qDebug() << "Server " << m_id;
			qDebug() << "Try listening on port " << tmp->port() << "...";
			if(m_tcpServer.listen(QHostAddress::Any, tmp->port()))
				qDebug() << "Succes";
			else {
				qDebug() << "Fail";
				abort();
			}
			while(!m_distantList.empty())
				delete m_distantList.takeFirst();
		}
		else
			m_distantList.push_back(tmp);
	}

}
