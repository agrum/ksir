#include "kdistant.h"

kDistant::kDistant(QTcpSocket* p_socket):
	m_responsible(false),
	m_socket(p_socket)
{
	start();
}

kDistant::kDistant(const QDomNode& p_root):
	kCore(p_root),
	pLogBehavior("kDistant"),
	m_responsible(true),
	m_socket(new QTcpSocket())
{
	if(isNull())
		pLog::logE(this, pLog::ERROR_NULL, "Responsible distant system null");

	start();
}

kDistant::~kDistant()
{
	terminate();
	wait();
	if(m_responsible)
		delete m_socket;
}

bool kDistant::sendMsg(QList<kMsg> p_list)
{
	m_mutex.lock();
	m_sendList.append(p_list);
	m_mutex.unlock();
}

QList<kMsg> kDistant::getMsg()
{
	QList<kMsg> rtn;

	m_mutex.lock();
	rtn = m_receiveList;
	m_receiveList.clear();
	m_mutex.unlock();

	if(isNull())
		*this = rtn.first().header().receiver();

	return rtn;
}

void kDistant::run(){
	while(true){
		if(!m_socket->isValid() && m_responsible)
			m_socket->connectToHost(m_addr, m_port);
		else{
			m_mutex.lock();
			//Send outgoing messages
			if(!m_sendList.empty())
				m_socket->write(m_sendList.takeFirst().toMsg());

			//Get pending messages
			if(m_socket->canReadLine())
				m_receiveList.push_back(kMsg (m_socket->readLine()));
			m_mutex.unlock();
		}
		msleep(250);
	}
}

void kDistant::readXml(const QString& p_tag, const QDomElement& p_node)
{
	kCore::readXml(p_tag, p_node);
	if( p_tag == XML_ADDR )
		m_addr = p_node.text();
	if( p_tag == XML_PORT )
		m_port = p_node.text().toInt();
}
