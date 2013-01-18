#include "kdistant.h"

kDistant::kDistant(int p_socketDesc):
	pLogBehavior("kDistant"),
	m_connected(false),
	m_responsible(false),
	m_socketDesc(p_socketDesc),
	m_socket(NULL)
{
	start();
}

kDistant::kDistant(const QDomNode& p_root):
	kCore(p_root),
	pLogBehavior("kDistant"),
	m_connected(false),
	m_responsible(true),
	m_socket(NULL)
{
	from(p_root);

	if(isNull())
		pLog::logE(this, pLog::ERROR_NULL, "Responsible distant system null");
}

kDistant::~kDistant()
{
	terminate();
	wait();
	if(m_responsible && m_socket)
		delete m_socket;
}

bool kDistant::alive()
{
	if(m_socket->state() != QAbstractSocket::ConnectedState){
		if(m_connected){
			m_connected = false;
			pLog::logI(this, pLog::INFO_NONE,
				   QString("system lost : %1 %2").arg(m_id).arg(m_port));
		}
		if(m_responsible){
			m_socket->abort();
			m_socket->connectToHost(m_addr, m_port);
			if(m_socket->waitForConnected(1000)){
				kMsg aliveMsg("Hello", kMsgHeader::INFO, *this);

				m_mutex.lock();
				m_sendList.push_back(aliveMsg);
				m_mutex.unlock();
			}
		}
	}

	if(!m_connected && m_socket->state() == QAbstractSocket::ConnectedState){
		m_connected = true;
		pLog::logI(this, pLog::INFO_NONE,
				   QString("system joined : %1 %2").arg(m_id).arg(m_port));
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

	if(!rtn.empty() && isNull()){
		*(kCore*) this = rtn.first().header().sender();
		pLog::logI(this, pLog::INFO_NONE,
				   QString("system name acquired %1 %2").arg(m_id).arg(m_port));
	}

	return rtn;
}

void kDistant::run(){
	m_socket = new QTcpSocket();
	if(!m_responsible){
		m_socket->setSocketDescriptor(m_socketDesc);
	}

	while(true){
		if(alive()){
			m_mutex.lock();
			//Send outgoing messages
			while(!m_sendList.empty()){
				kMsg tmp = m_sendList.takeFirst();
				if(!tmp.outdated()){
					//qDebug() << "write\n" << tmp.toMsg();
					m_socket->write(tmp.toMsg());
					m_socket->waitForBytesWritten(100);
				}
				else
					pLog::logW(this, pLog::WARNING_NONE, "message outdated, not send");
			}

			//Get pending messages
			m_socket->waitForReadyRead(100);
			while(m_socket->canReadLine()){
				QByteArray line = m_socket->readLine();
				m_msgStack += line;

				if(line.left(9) == "</Header>"){
					//qDebug() << "read\n" << m_msgStack;
					kMsg tmp(m_msgStack);
					m_receiveList.push_back(kMsg (m_msgStack));
					m_msgStack.clear();
				}
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
