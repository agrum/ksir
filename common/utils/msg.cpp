#include "msg.h"

using namespace ksir;

unsigned int Msg::s_idCount = 0;
QMutex Msg::s_mutex;

/* $Desc Create a message with correspondign name and type.
 *	Names are used for ownership in the mailman while types
 *	are useless.
 * $Parm p_name Message name.
 * $Parm p_type Message type.
 * $Rtrn /.
 */
Msg::Msg(const QString& p_name, Type p_type) :
	XmlBehavior("Msg_" + p_name),
	m_name(p_name),
	m_type(p_type)
{
	s_mutex.lock();
		m_id = s_idCount++;
	s_mutex.unlock();
}

/* $Desc Create a message out of an XML node. The informations
 *	extracted only come from the attributes of this node.
 *	Children are reserved for the entries added to the message.
 * $Parm p_node.
 * $Rtrn /.
 */
Msg::Msg(const QDomNode& p_node) :
	XmlBehavior("Msg_" + getAttribute(p_node, "name"))
{
	m_id = getAttribute(p_node, "id").toInt();
	m_name = getAttribute(p_node, "name");
	m_type = (Type) getAttribute(p_node, "type").toInt();
}

/* $Desc Copy constructor.
 * $Parm p_msg Message to copy.
 * $Rtrn /.
 */
Msg::Msg(const Msg& p_msg) :
	XmlBehavior("Msg_" + p_msg.m_name),
	m_id(p_msg.m_id),
	m_name(p_msg.m_name),
	m_type(p_msg.m_type)
{

}

/* $Desc If the type is RPRT (report), the function will be locked until
 *	someone responsible acknowledge it.
 * $Parm /.
 * $Rtrn /.
 */
void
Msg::waitForAck()
{
	Type type;

	m_mutex.lock();
		type = m_type;
	m_mutex.unlock();

	if(type != Msg::RPRT)
		return;

	m_mutex.lock();
		m_reportWaitCondition.wait(&m_mutex);
	m_mutex.unlock();
}



/* $Desc If the type is RPRT (report), the function will awake the
 *	waiting thread for an acknowledgment of this report. Once a
 *	message has been acknowledged, it is transformed to an INFO
 *	message, meaning it can t be acknowledged once again.
 * $Parm /.
 * $Rtrn /.
 */
void
Msg::ack()
{
	Type type;

	m_mutex.lock();
		type = m_type;
	m_mutex.unlock();

	if(type != Msg::RPRT)
		return;

	m_mutex.lock();
		m_type = Msg::INFO;
	m_mutex.unlock();

	m_reportWaitCondition.wakeAll();
}
