#include "ksender.h"

#include <QByteArray>
#include <QDomDocument>

kSender::kSender(QTcpSocket* p_socket):
	pLogBehavior("Sender"),
	m_socket(p_socket),
	m_blurer(NULL)
{
	start();
}

kSender::~kSender()
{
	m_mutex.lock();
		if(m_blurer != NULL)
			delete m_blurer;
	m_mutex.unlock();
}

void
kSender::setCrypt(const Crypt& p_crypt)
{
	m_mutex.lock();
		if(m_blurer != NULL)
			delete m_blurer;
		m_blurer = new kBlurer(p_crypt);
	m_mutex.unlock();
}

void
kSender::run()
{
	PRC<Msg> msg;
	QByteArray msgByteArray = "";
	QDomDocument doc;

	//Send outgoing messages
	if(m_socket->waitForConnected() && (msg = m_comLink.read()) != NULL)
	{
		int crypted = 0;
		msg->to(doc, "message");
		//qDebug() << "write\n" << tmp.toMsg();
		m_mutex.lock();
			if(m_blurer != NULL) //Send any message when a crypt is set
			{
				crypted = 1;
				msgByteArray = m_blurer->blur(doc.toByteArray());
			}
			else if(msg->name() == "Hello") //Only uncrypted ongoing message allowed
				msgByteArray = doc.toByteArray();
			else  //Throw exception
				logE("Try to send a non safe message uncrypted");
		m_mutex.unlock();

		//Compose and send the message through socket
		if(msgByteArray.length() > 0)
		{
			QString msgHeader = QString("%1_%2\r\n")
					.arg(QString::number(msgByteArray.length()))
					.arg(crypted);
			QByteArray fullMsg;
			fullMsg.append(msgHeader);
			fullMsg.append(msgByteArray);

			m_socket->write(fullMsg);
			m_socket->waitForBytesWritten(1000);
		}
	}
}
