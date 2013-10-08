#include "distant.h"

#include <QTime>
#include <assert.h>

#include "../utils/msg.h"
#include "../utils/string.h"

#include "mailman.h"

using namespace ksir;


/* $Desc Constructor called for a distant system from which the socket
 *		has already been connected, Normally a client.
 * $Parm p_socketDesc descriptor of the socket to the distant system.
 * $Rtrn /.
 */
Distant::Distant(int p_socketDesc):
	XmlBehavior("Distant"),
	m_connected(false),
	m_responsible(false),
	m_receiver(&m_socket),
	m_sender(&m_socket)
{
	//Set socket
	m_socket.setSocketDescriptor(p_socketDesc);
}

/* $Desc Constructor called for a distant system only known from
 *		a conf file. Normally a server. This kind of system is responsible
 *		for keeping its socket opened.
 * $Parm p_root DOM node holding the information of the distant system.
 * $Rtrn /.
 */
Distant::Distant(const QDomNode& p_node):
	XmlBehavior("Distant"),
	m_connected(false),
	m_responsible(true),
	m_receiver(&m_socket),
	m_sender(&m_socket)
{
	//Init system from XML node
	from(p_node);
	m_id = getAttribute(p_node, "id");
	m_addr = getAttribute(p_node, "addr");
	m_port = getAttribute(p_node, "port").toInt();

	//Throw exception if the system is null after init
	if(m_id.isNull())
		logE("Responsible distant system null");
}

/* $Desc Destructor stoping the looping threads. Wait for them to terminate.
 * $Parm /.
 * $Rtrn /.
 */
Distant::~Distant()
{

}

/* $Desc Destructor stoping the looping threads. Wait for them to terminate.
 * $Parm /.
 * $Rtrn /.
 */
void
Distant::run()
{
	QString sysIdentifier = QString("%1 %3:%4")
			.arg(m_id)
			.arg(m_addr)
			.arg(m_port);

	//Manage the socket if it s not connected
	if(m_socket.state() != QAbstractSocket::ConnectedState){
		//If it was previously connected, mention it
		if(m_connected){
			m_connected = false;

			//Write a report for disconnected distant system
			PRC<Msg> report = new Msg(MSG_DISC_SOCK, Msg::RPRT);
			report->add("system", new String(m_id));
			ComLink::write(report, MAILMAN);

			//Log loss
			logI(QString("System lost %1").arg(sysIdentifier));
		}
		//If this distant system is respopnsible for the connection,
		//	it tries to reconnect
		if(m_responsible){
			m_socket.abort();
			m_socket.connectToHost(m_addr, m_port);
			//If the connection succed, establish comm with the distant system
			if(m_socket.waitForConnected(1000)){
				PRC<Msg> aliveMsg = new Msg("Hello", Msg::INFO);

				m_sender.getComLink().write(aliveMsg);
			}
		}
	}

	//If the connected state is new, mention it
	if(!m_connected && m_socket.state() == QAbstractSocket::ConnectedState){
		m_connected = true;

		//Write a report for connected distant system
		PRC<Msg> report = new Msg(MSG_CONN_SOCK, Msg::RPRT);
		report->add("system", new String(m_id));
		ComLink::write(report, MAILMAN);

		//Log new acquitance
		logI(QString("System joined %1").arg(sysIdentifier));
	}
}

/* $Desc XML reading behavior.
 * $Parm p_tag Tag of the element provided.
 * $Parm p_node node holding the tag + content.
 * $Rtrn /.
 */
void
Distant::readXml(const QDomNode& p_node, const QString& p_tag)
{
	if( p_tag == "crypt" )
	{
		Crypt crypt(p_node);
		m_receiver.setCrypt(crypt);
		m_sender.setCrypt(crypt);
	}
}
