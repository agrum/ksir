#include "kdistant.h"

kDistant::kDistant(int p_socketDesc):
	m_front(QTime::currentTime()),
	m_end(QTime::currentTime()),
	m_responsible(false),
	m_socketDesc(p_socketDesc)
{
	start();
}

kDistant::kDistant(const QDomNode& p_root):
	kCore(p_root),
	pLogBehavior("kDistant"),
	m_front(QTime::currentTime()),
	m_end(QTime::currentTime()),
	m_responsible(true)
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

bool kDistant::alive()
{
	if(m_end < QTime::currentTime().addMSecs(-2000)){
		pLog::logW(this, pLog::WARNING_NONE,
				   QString("system outdated %1 %2").arg(m_id).arg(m_port));
		if(m_responsible){
			m_socket->abort();
			m_socket->connectToHost(m_addr, m_port);
			if(m_socket->waitForConnected(1000))
				m_end = QTime::currentTime();
			else
				msleep(2000);
		}
	}
	if(m_front < QTime::currentTime().addMSecs(-1000)
			&& m_socket->state() == QAbstractSocket::ConnectedState){
		kMsg tmp("Alive", kMsgHeader::INFO, *this);

		m_front = QTime::currentTime();

		m_mutex.lock();
		m_sendList.push_back(tmp);
		m_mutex.unlock();
	}
	return m_socket->state() == QAbstractSocket::ConnectedState;
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

	if(!rtn.empty() && isNull())
		*(kCore*) this = rtn.first().header().receiver();

	if(rtn.removeAll(kMsg ("Alive", kMsgHeader::INFO)) > 0)
		m_end = QTime::currentTime();

	return rtn;
}

void kDistant::run(){
	m_socket = new QTcpSocket();
	if(!m_responsible)
		m_socket->setSocketDescriptor(m_socketDesc);

	while(true){
		if(alive()){
			m_mutex.lock();
			//Send outgoing messages
			while(!m_sendList.empty()){
				kMsg tmp = m_sendList.takeFirst();
				if(!tmp.outdated()){
					m_socket->write(tmp.toMsg());
				}
				else
					pLog::logW(this, pLog::WARNING_NONE, "message outdated, not send");
			}

			//Get pending messages
			while(m_socket->canReadLine()){
				qDebug() << "read";
				m_receiveList.push_back(kMsg (m_socket->readLine()));
			}
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
