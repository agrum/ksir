#include "kmsgoutter.h"

kMsgOutter::kMsgOutter(const QString& p_name, Type p_type):
	kMsg(p_name, p_type)
{

}

kMsgOutter::kMsgOutter(const QDomNode& p_node):
	kMsg(p_node)
{
	m_doc = p_node.cloneNode();
}

kMsgOutter::kMsgOutter(const kMsgOutter& p_msg):
	kMsg(p_msg)
{
	m_doc = p_msg.m_doc.cloneNode();
}

kMsgOutter::~kMsgOutter()
{

}

kMsgOutter&
kMsgOutter::operator=(const kMsgOutter& p_msg)
{
	m_id = p_msg.id;
	m_name = p_msg.name;
	m_type = p_msg.type;
	m_doc = p_msg.m_doc.cloneNode();
}

//Operation
void
kMsgOutter::add(const QString& p_tag, const kPRC<kXmlBehavior>& p_entity)
{
	p_entity->to(m_doc, p_tag);
}

void
kMsgOutter::get(const QString& p_tag, kPRC<kXmlBehavior>& p_entity)
{
	for (QDomNode n = m_info.firstChild(); !n.isNull(); n = n.nextSibling())
		if (n.nodeName() == p_tag)
			p_entity->from(n);
}

bool
kMsgOutter::exist(const QString& p_tag)
{
	for (QDomNode n = m_doc.firstChild(); !n.isNull(); n = n.nextSibling())
		if (n.nodeName() == p_tag)
			return true;
	return false;
}

//XML
void
kMsgOutter::writeXml(QDomNode& p_node)
{
	addAttribute(p_node, "id", m_id);
	addAttribute(p_node, "name", m_name);
	addAttribute(p_node, "type", m_type);
}
