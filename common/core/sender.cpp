#include "sender.h"

#include <QByteArray>
#include <QDomDocument>

using namespace ksir;


/* $Desc Constructor called from a distant system in which the socket
 *		has already been connected. The local socket is a simple pointer
 *		to the original.
 *	The thread sending the queued messages is launched at the construction.
 * $Parm p_socket descriptor of the socket to the distant system.
 * $Rtrn /.
 */
Sender::Sender(QTcpSocket* p_socket):
	pLogBehavior("Sender"),
	m_socket(p_socket),
	m_blurer(NULL)
{
	start();
}

/* $Desc Destructor, stop the thread and delete the blurer if any.
 * $Parm /.
 * $Rtrn /.
 */
Sender::~Sender()
{
	terminate();

	m_mutex.lock();
		if(m_blurer != NULL)
			delete m_blurer;
	m_mutex.unlock();
}

/* $Desc Initialize (or reinitialize) the blurer for encryption.
 * $Parm p_crypt Crypt kernel needed for bluring.
 * $Rtrn /.
 */
void
Sender::setCrypt(const Crypt& p_crypt)
{
	m_mutex.lock();
		if(m_blurer != NULL)
			delete m_blurer;
		m_blurer = new kBlurer(p_crypt);
	m_mutex.unlock();
}

/* $Desc QThread loop function. Waits for the socket to be connected
 *	and for a message to be queued in the comLink. Once both conditions
 *	are met, the message is formatted to XML content and blured if
 *	an encryption kernel has been provided.
 *	The formatted (and encrypted) message is then sent through the socket
 *	with additionnal uncrypted informations (msg length + encryption flag).
 * $Parm /.
 * $Rtrn /.
 */
void
Sender::run()
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
