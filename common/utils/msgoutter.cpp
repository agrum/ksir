#include "msgoutter.h"

using namespace ksir;

MsgOutter::MsgOutter(const QString& p_name, Type p_type):
	Msg(p_name, p_type)
{

}

MsgOutter::MsgOutter(const QDomNode& p_node):
	Msg(p_node)
{
	m_doc = p_node.cloneNode().toDocument();
}

MsgOutter::MsgOutter(const MsgOutter& p_msg):
	Msg(p_msg)
{
	m_doc = p_msg.m_doc.cloneNode().toDocument();
}

MsgOutter::~MsgOutter()
{

}

MsgOutter&
MsgOutter::operator=(const MsgOutter& p_msg)
{
	m_id = p_msg.m_id;
	m_name = p_msg.m_name;
	m_type = p_msg.m_type;
	m_doc = p_msg.m_doc.cloneNode().toDocument();

	return *this;
}

//Operation
void
MsgOutter::add(const QString& p_tag, const PRC<XmlBehavior>& p_entity)
{
	p_entity->to(m_doc, p_tag);
}

void
MsgOutter::get(const QString& p_tag, PRC<XmlBehavior>& p_entity)
{
	for (QDomNode n = m_doc.firstChild(); !n.isNull(); n = n.nextSibling())
		if (n.nodeName() == p_tag)
			p_entity->from(n);
}

bool
MsgOutter::exist(const QString& p_tag)
{
	for (QDomNode n = m_doc.firstChild(); !n.isNull(); n = n.nextSibling())
		if (n.nodeName() == p_tag)
			return true;
	return false;
}

//XML
void
MsgOutter::writeXml(QDomNode& p_node) const
{
	addAttribute(p_node, "id", QString::number(m_id));
	addAttribute(p_node, "name", m_name);
	addAttribute(p_node, "type", QString::number(m_type));
}
