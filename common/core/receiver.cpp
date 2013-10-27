#include "receiver.h"

#include <QByteArray>
#include <QDomDocument>

#include "../utils/msg.h"
#include "../utils/crypt.h"

#include "mailman.h"
#include "comlink.h"

using namespace ksir;


/* $Desc Constructor called from a distant system in which the socket
 *		has already been connected. The local socket is a simple pointer
 *		to the original.
 *	The thread sending the queued messages is launched at the construction.
 * $Parm /.
 * $Rtrn /.
 */
Receiver::Receiver(QTcpSocket* p_socket):
	pLogBehavior("Receiver"),
	m_socket(p_socket),
	m_clearer(NULL)
{
	start();
}

/* $Desc Destructor, stop the thread and delete the blurer if any.
 * $Parm /.
 * $Rtrn /.
 */
Receiver::~Receiver()
{
	terminate();

	m_mutex.lock();
		if(m_clearer != NULL)
			delete m_clearer;
	m_mutex.unlock();
}

/* $Desc Initialize (or reinitialize) the blurer for encryption.
 * $Parm p_crypt Crypt kernel needed for bluring.
 * $Rtrn /.
 */
void
Receiver::setCrypt(const Crypt& p_crypt)
{
	m_mutex.lock();
		if(m_clearer != NULL)
			delete m_clearer;
		m_clearer = new Clearer(p_crypt);
	m_mutex.unlock();
}

/* $Desc QThread loop function. Waits for the socket to be connected
 *	and for packets to arrive inside. When the socket is ready to read
 *	a line it does it. The line holds two informations. The length of
 *	following message and the encryption flag (0 or 1 whether it is or
 *	not). The thread waits for the socket to be able to read at least
 *	a chunk of data as long as the message is excpected to be.
 *	Once the chunk acquired, it is uncrypted if necessary then a msg
 *	is created out of it. The  message is then forwarded to the mailman.
 * $Parm /.
 * $Rtrn /.
 */
void
Receiver::run()
{
	PRC<Msg> msg;
	QByteArray msgByteArray = "";
	QDomDocument doc;
	int msgLength = -1;
	bool fullyRead = false;
	bool crypted = false;

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
				msg = new Msg(doc);

				//No other msg than Hello accepted as uncrypted
				if(crypted || msg->name() == "Hello")
					ComLink::write(msg, MAILMAN);
				else
					logE("Received an uncrypted message not safe");
			}
		}
	}
}
