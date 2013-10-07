#include "msgoutter.h"

using namespace ksir;


/* $Desc Create a message with correspondign name and type.
 *	Names are used for ownership in the mailman while types
 *	are useless.
 * $Parm p_name Message name.
 * $Parm p_type Message type.
 * $Rtrn /.
 */
MsgOutter::MsgOutter(const QString& p_name, Type p_type):
	Msg(p_name, p_type)
{

}

/* $Desc Create a message out of an XML node. The informations
 *	extracted from the attributes of this node create the super
 *	class.
 *	Children are reserved for the entries added to the message.
 *	Since objects can t be reconstruct without proper function
 *	call, the node is simply cloned to the local DOM document.
 * $Parm p_node.
 * $Rtrn /.
 */
MsgOutter::MsgOutter(const QDomNode& p_node):
	Msg(p_node)
{
	m_doc = p_node.cloneNode().toDocument();
}

/* $Desc Copy constructor.
 * $Parm p_msg Message to copy.
 * $Rtrn /.
 */
MsgOutter::MsgOutter(const MsgOutter& p_msg):
	Msg(p_msg)
{
	m_doc = p_msg.m_doc.cloneNode().toDocument();
}

/* $Desc Destructor.
 * $Parm /.
 * $Rtrn /.
 */
MsgOutter::~MsgOutter()
{

}

/* $Desc Copy oerator.
 * $Parm p_msg Message to copy.
 * $Rtrn Reference to the modified object.
 */
MsgOutter&
MsgOutter::operator=(const MsgOutter& p_msg)
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
MsgOutter::add(const QString& p_tag, const XmlBehavior* p_entity)
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
MsgOutter::get(const QString& p_tag, XmlBehavior* p_entity)
{
	for (QDomNode n = m_doc.firstChild(); !n.isNull(); n = n.nextSibling())
		if (n.nodeName() == p_tag)
			p_entity->from(n);
}

/* $Desc Check the existence of an entry in the message s document.
 * $Parm p_tag Named used to retrieve the entity.
 * $Rtrn True if an entity exists under the provided tag.
 */
bool
MsgOutter::exist(const QString& p_tag)
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
MsgOutter::writeXml(QDomNode& p_node) const
{
	addAttribute(p_node, "id", QString::number(m_id));
	addAttribute(p_node, "name", m_name);
	addAttribute(p_node, "type", QString::number(m_type));
}
