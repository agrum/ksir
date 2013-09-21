#include "kreceiver.h"

#include <QByteArray>
#include <QDomDocument>

#include "../utils/msgoutter.h"

kReceiver::kReceiver(QTcpSocket* p_socket):
	pLogBehavior("Receiver"),
	m_socket(p_socket),
	m_clearer(NULL)
{
	start();
}

kReceiver::~kReceiver()
{
	m_mutex.lock();
		if(m_clearer != NULL)
			delete m_clearer;
	m_mutex.unlock();
}

void
kReceiver::setCrypt(const Crypt& p_crypt)
{
	m_mutex.lock();
		if(m_clearer != NULL)
			delete m_clearer;
		m_clearer = new kClearer(p_crypt);
	m_mutex.unlock();
}

void
kReceiver::run()
{
	PRC<Msg> msg;
	QByteArray msgByteArray = "";
	QDomDocument doc;
	int msgLength = -1;
	bool fullyRead = false;
	bool crypted;

	//Collect ingoing messages
	while(!fullyRead)
	{
		m_socket->waitForConnected();
		m_socket->waitForReadyRead(1000);
		if(m_socket->canReadLine() || msgLength != -1)
		{
			//Get the uncrypted header (msgLength + crypt flag)
			if(msgLength == -1)
			{
				QByteArray line = m_socket->readLine();
				msgLength = line.left(line.size() - 4).toInt(NULL, 10);
				crypted = (bool) line.mid(line.size() - 3, 1).toInt(NULL, 10);
			}
			//Get the actual msg content
			else if(m_socket->bytesAvailable() >= msgLength)
			{
				msgByteArray = m_socket->read(msgLength);

				m_mutex.lock();
					if(crypted && m_clearer != NULL)
						msgByteArray = m_clearer->clear(msgByteArray, msgLength);
					else
						logE("Received an encrypted message without possibility to uncrypt");
				m_mutex.unlock();

				fullyRead = true;
				doc.setContent(msgByteArray);
				msg = new MsgOutter(doc);

				//No other msg than Hello accepted as uncrypted
				if(crypted || msg->name() == "Hello")
					ComLink::write(msg, "mailman");
				else
					logE("Received an uncrypted message not safe");
			}
		}
	}
}
