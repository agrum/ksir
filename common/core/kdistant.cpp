#include "kdistant.h"

kDistant::kDistant(QTcpSocket* p_socket):
	m_front(QTime::currentTime()),
	m_end(QTime::currentTime()),
	m_responsible(false),
	m_socket(p_socket)
{
	start();
}

kDistant::kDistant(const QDomNode& p_root):
	kCore(p_root),
	pLogBehavior("kDistant"),
	m_front(QTime::currentTime()),
	m_end(QTime::currentTime()),
	m_responsible(true),
	m_socket(new QTcpSocket())
{
	from(p_root);

	if(isNull())
		pLog::logE(this, pLog::ERROR_NULL, "Responsible distant system null");
}

kDistant::~kDistant()
{
	terminate();
	wait();
	if(m_responsible)
		delete m_socket;
}

void kDistant::setSocket(QTcpSocket* p_socket){
	m_mutex.lock();
	m_socket = p_socket;
	m_mutex.unlock();
}

bool kDistant::alive()
{
	if(!m_socket->isValid()){
		pLog::logW(this, pLog::WARNING_NONE, "alive - invalid socket");
		return false;
	}
	if(m_end < QTime::currentTime().addMSecs(2000)){
		pLog::logW(this, pLog::WARNING_NONE, "alive - end outdated");
		return false;
	}
	if(m_front < QTime::currentTime().addMSecs(2000)){
		pLog::logW(this, pLog::WARNING_NONE, "alive - front outdated");
		return false;
	}
	return true;
}

bool kDistant::sendMsg(QList<kMsg> p_list)
{
	m_mutex.lock();
	m_sendList.append(p_list);
	m_mutex.unlock();

	return true;
}

QList<kMsg> kDistant::getMsg()
{
	QList<kMsg> rtn;

	m_mutex.lock();
	rtn = m_receiveList;
	m_receiveList.clear();
	m_mutex.unlock();

	if(isNull())
		*(kCore*) this = rtn.first().header().receiver();

	if(rtn.removeAll(kMsg ("Alive", kMsgHeader::INFO)) > 0)
		m_end = QTime::currentTime();

	return rtn;
}

void kDistant::run(){
	while(true){
		if(!m_socket->isValid() && m_responsible)
			m_socket->connectToHost(m_addr, m_port);
		else{
			m_mutex.lock();
			//Alive
			if(QTime::currentTime().addMSecs(-1000) > m_front){
				kMsg tmp("Alive", kMsgHeader::INFO, *this);

				m_front = QTime::currentTime();
				m_sendList.push_back(tmp);
			}
			//Send outgoing messages
			while(!m_sendList.empty()){
				kMsg tmp = m_sendList.takeFirst();
				if(!tmp.outdated())
					m_socket->write(tmp.toMsg());
				else
					pLog::logW(this, pLog::WARNING_NONE, "message outdated, not send");
			}

			//Get pending messages
			while(m_socket->canReadLine())
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
