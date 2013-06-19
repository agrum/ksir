#include "kdistant.h"

kDistant::kDistant(int p_socketDesc, kQueueW& p_sysQueue):
	pLogBehavior("kDistant"),
	m_sysQueue(p_sysQueue),
	m_mustDestroy(false),
	m_connected(false),
	m_responsible(false),
	m_socketDesc(p_socketDesc),
	m_socket(NULL),
	m_crypt(NULL),
	m_canCrypt(false)
{
	start();
}

kDistant::kDistant(const QDomNode& p_root, kQueueW& p_sysQueue):
	kCore(p_root),
	pLogBehavior("kDistant"),
	m_sysQueue(p_sysQueue),
	m_mustDestroy(false),
	m_connected(false),
	m_responsible(true),
	m_socket(NULL),
	m_crypt(NULL),
	m_canCrypt(false)
{
	from(p_root);

	if(isNull())
		logE(pLog::ERROR_NULL, "Responsible distant system null");
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
	QString sysIdentifier = QString("%1 %2 %3:%4")
			.arg(m_id)
			.arg(m_type)
			.arg(m_addr)
			.arg(m_port);

	if(m_socket->state() != QAbstractSocket::ConnectedState){
		if(m_connected){
			m_connected = false;

			kMsg report(MSG_DISC_SOCK, kMsgHeader::REP);
			report.add("who", m_id);
			m_sysQueue.push(report);

			logI(kCommonLogExtension::INFO_LOST, sysIdentifier);
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
		else{ //Will never be used anyway
			m_mutex.lock();
			delete m_crypt;
			m_crypt = NULL;
			m_mustDestroy = true;
			m_mutex.unlock();
		}
	}

	if(!m_connected && m_socket->state() == QAbstractSocket::ConnectedState){
		m_connected = true;

		kMsg report(MSG_CONN_SOCK, kMsgHeader::REP);
		report.add("who", m_id);
		m_sysQueue.push(report);

		logI(kCommonLogExtension::INFO_JOINED, sysIdentifier);
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

	if(!rtn.empty() && (isNull() || m_temporaryName)){
		m_id = rtn.first().header().sender();
		if(m_id == "" && m_type == "client"){ //Give an unique name to the client
			m_id = rtn.first().header().receiver() + "_" + QTime::currentTime().toString();

			kMsg aliveMsg("GotYourName", kMsgHeader::INFO, *this);

			m_mutex.lock();
			m_sendList.push_back(aliveMsg);
			m_mutex.unlock();
		}
		logI(kCommonLogExtension::INFO_NAME,
				   QString("acquired %1 %2 %3").arg(m_id).arg(m_type).arg(m_port));
	}

	return rtn;
}

void kDistant::run(){
	QByteArray tmpBA;
	bool helpExpected = true;
	int msgLength;

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
					tmp.header().setSender(m_sender);
					tmpBA = tmp.toMsg();
					if(m_canCrypt)
						m_socket->write(QByteArray::number(256 * (2 + tmpBA.size()/256)) + "\r\n" + m_crypt->blur(tmpBA) + "\r\n");
					else if(tmp.name() == "Hello")
						m_socket->write(QByteArray::number(tmpBA.size()) + "\r\n" + tmpBA + "\r\n");
					m_socket->waitForBytesWritten(100);
				}
				else
					logW(kCommonLogExtension::WARNING_OUTDATED, "Not send");
			}

			//Get pending messages
			m_socket->waitForReadyRead(100);
			while(m_socket->canReadLine()){
				if(helpExpected){
					QByteArray line = m_socket->readLine();
					msgLength = line.left(line.size() - 2).toInt(NULL, 10);
					helpExpected = false;
				}
				if(!helpExpected && m_socket->bytesAvailable() >= msgLength) {
					QByteArray msg = m_socket->read(msgLength);
					if(m_canCrypt)
						msg = m_crypt->clear(msg, msgLength);
					helpExpected = true;

					//qDebug() << "read\n" << m_msg;
					m_receiveList.push_back(kMsg (msg));
				}
			}
			m_mutex.unlock();
		}
		msleep(20);
	}
}

void kDistant::readXml(const QString& p_tag, const QDomElement& p_node)
{
	kCore::readXml(p_tag, p_node);
	if( p_tag == XML_ADDR )
		m_addr = p_node.text();
	if( p_tag == XML_PORT )
		m_port = p_node.text().toInt();
	if( p_tag == XML_KNOWNAS )
		m_sender = p_node.text();
	if( p_tag == XML_CRYPT )
		m_crypt = new kCrypt(p_node);
}
