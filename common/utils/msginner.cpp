#include "msginner.h"

#include <QtXml>

using namespace ksir;


/* $Desc Create a message with correspondign name and type.
 *	Names are used for ownership in the mailman while types
 *	are useless.
 * $Parm p_name Message name.
 * $Parm p_type Message type.
 * $Rtrn /.
 */
MsgInner::MsgInner(const QString& p_name, Type p_type):
	Msg(p_name, p_type)
{

}

/* $Desc Copy constructor.
 * $Parm p_msg Message to copy.
 * $Rtrn /.
 */
MsgInner::MsgInner(const MsgInner& p_msg):
	Msg(p_msg),
	m_map(p_msg.m_map)
{

}

/* $Desc Destructor.
 * $Parm /.
 * $Rtrn /.
 */
MsgInner::~MsgInner()
{

}

/* $Desc Copy oerator.
 * $Parm p_msg Message to copy.
 * $Rtrn Reference to the modified object.
 */
MsgInner&
MsgInner::operator=(const MsgInner& p_msg)
{
	m_id = p_msg.m_id;
	m_name = p_msg.m_name;
	m_type = p_msg.m_type;
	m_map = p_msg.m_map;

	return *this;
}

/* $Desc Add an entity to the message. The entity is any class
 *	that inherits from XmlBehvaior to allow a conversion to an
 *	XML format.
 * $Parm p_tag Named used to retrieve the entity.
 * $Parm p_entity PRC over an entity.
 * $Rtrn /.
 */
void
MsgInner::add(const QString& p_tag, const XmlBehavior* p_entity)
{
	m_map.insert(p_tag, *p_entity);
}

/* $Desc Reconstruct the input entry from the entity map of the message.
 * $Parm p_tag Named used to retrieve the entity.
 * $Parm p_entity PRC over an entity.
 * $Rtrn /.
 */
void
MsgInner::get(const QString& p_tag, XmlBehavior* p_entity)
{
	*p_entity = m_map[p_tag];
}

/* $Desc Check the existence of an entry in the message s map.
 * $Parm p_tag Named used to retrieve the entity.
 * $Rtrn True if an entity exists under the provided tag.
 */
bool
MsgInner::exist(const QString& p_tag)
{
	return m_map.contains(p_tag);
}

/* $Desc Fill up a node with the message s attributes. Children are
 *	also added per entry.
 * $Parm p_node Node in which the message must be written.
 * $Rtrn /.
 */
void
MsgInner::writeXml(QDomNode& p_node) const
{
	QMap<QString, XmlBehavior>::const_iterator iter;

	for(iter = m_map.begin(); iter != m_map.end(); iter++)
		iter.value().to(p_node, iter.key());

	addAttribute(p_node, "id", QString::number(m_id));
	addAttribute(p_node, "name", m_name);
	addAttribute(p_node, "type", QString::number(m_type));
}
