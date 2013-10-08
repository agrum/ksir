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
	m_type(p_type),
	m_doc(p_name)
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
	m_doc = p_node.cloneNode().toDocument();
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
	m_doc = p_msg.m_doc.cloneNode().toDocument();
}

/* $Desc Destructor.
 * $Parm /.
 * $Rtrn /.
 */
Msg::~Msg()
{

}

/* $Desc Copy oerator.
 * $Parm p_msg Message to copy.
 * $Rtrn Reference to the modified object.
 */
Msg&
Msg::operator=(const Msg& p_msg)
{
	m_id = p_msg.m_id;
	m_name = p_msg.m_name;
	m_type = p_msg.m_type;
	m_doc = p_msg.m_doc.cloneNode().toDocument();

	return *this;
}

/* $Desc Add an entity to the message. The entity is any class
 *	that inherits from XmlBehvaior to allow a conversion to an
 *	XML format.
 *	Since outgoing messages don t hold actual instances, the entity
 *	is converted to XML right away and pushed in the document.
 * $Parm p_tag Named used to retrieve the entity.
 * $Parm p_entity PRC over an entity.
 * $Rtrn /.
 */
void
Msg::add(const QString& p_tag, const PRC<XmlBehavior> p_entity)
{
	p_entity->to(m_doc, p_tag);
}

/* $Desc Reconstruct the input entry from the corresponding node
 *	in the document.
 * $Parm p_tag Named used to retrieve the entity.
 * $Parm p_entity PRC over an entity.
 * $Rtrn /.
 */
void
Msg::get(const QString& p_tag, XmlBehavior* p_entity)
{
	QByteArray meh = m_doc.toByteArray();
	for (QDomNode n = m_doc.firstChild(); !n.isNull(); n = n.nextSibling())
		if (n.nodeName() == p_tag)
			p_entity->from(n);
}

/* $Desc Check the existence of an entry in the message s document.
 * $Parm p_tag Named used to retrieve the entity.
 * $Rtrn True if an entity exists under the provided tag.
 */
bool
Msg::exist(const QString& p_tag)
{
	for (QDomNode n = m_doc.firstChild(); !n.isNull(); n = n.nextSibling())
		if (n.nodeName() == p_tag)
			return true;
	return false;
}

/* $Desc Fill up a node with the message s attributes.
 * $Parm p_node Node in which the message must be written.
 * $Rtrn /.
 */
void
Msg::writeXml(QDomNode& p_node) const
{
	addAttribute(p_node, "id", QString::number(m_id));
	addAttribute(p_node, "name", m_name);
	addAttribute(p_node, "type", QString::number(m_type));
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
