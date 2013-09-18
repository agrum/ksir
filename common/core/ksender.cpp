#include "ksender.h"

#include <QByteArray>

kSender::kSender(QTcpSocket* p_socket):
	pLogBehavior("kSender"),
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
kSender::setCrypt(const kCrypt& p_crypt)
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
	kMsg* msg;
	QByteArray msgByteArray = "";

	//Send outgoing messages
	if(m_socket->waitForConnected() && (msg = m_comLink.read()) != NULL)
	{
		if(!msg->outdated())
		{
			int crypted = 0;
			//qDebug() << "write\n" << tmp.toMsg();
			m_mutex.lock();
				if(m_blurer != NULL) //Send any message when a crypt is set
				{
					crypted = 1;
					msgByteArray = m_blurer->blur(msg->toMsg());
				}
				else if(msg->name() == "Hello") //Only uncrypted ongoing message allowed
					msgByteArray = msg->toMsg();
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
		else
			logW("Message outdated not send");
		delete msg;
	}
}
