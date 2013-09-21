#include "kmsginner.h"

#include <QtXml>

kMsgInner::kMsgInner(const QString& p_name, Type p_type):
	kMsg(p_name, p_type)
{

}

kMsgInner::kMsgInner(const kMsgInner& p_msg):
	kMsg(p_msg),
	m_map(p_msg.m_map)
{

}

kMsgInner::~kMsgInner()
{

}

kMsgInner&
kMsgInner::operator=(const kMsgInner& p_msg)
{
	m_id = p_msg.m_id;
	m_name = p_msg.m_name;
	m_type = p_msg.m_type;
	m_map = p_msg.m_map;
}


//Operation
void
kMsgInner::add(const QString& p_tag, const kPRC<kXmlBehavior>& p_entity)
{
	m_map.insert(p_tag, p_entity);
}

void
kMsgInner::get(const QString& p_tag, kPRC<kXmlBehavior>& p_entity)
{
	p_entity = m_map[p_tag];
}

bool
kMsgInner::exist(const QString& p_tag)
{
	return m_map.contains(p_tag);
}

void kMsgInner::readXml(const QDomNode&, const QString&)
{
	logE("Can t set an internal message from XML content");
}

void
kMsgInner::writeXml(QDomNode& p_node)
{
	for(iter = m_map.begin(); iter != m_map.end(); iter++)
		iter.value()->to(p_node, iter.key());

	addAttribute(p_node, "id", m_id);
	addAttribute(p_node, "name", m_name);
	addAttribute(p_node, "type", m_type);
}
