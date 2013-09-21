#include "msginner.h"

#include <QtXml>

using namespace ksir;

MsgInner::MsgInner(const QString& p_name, Type p_type):
	Msg(p_name, p_type)
{

}

MsgInner::MsgInner(const MsgInner& p_msg):
	Msg(p_msg),
	m_map(p_msg.m_map)
{

}

MsgInner::~MsgInner()
{

}

MsgInner&
MsgInner::operator=(const MsgInner& p_msg)
{
	m_id = p_msg.m_id;
	m_name = p_msg.m_name;
	m_type = p_msg.m_type;
	m_map = p_msg.m_map;

	return *this;
}


//Operation
void
MsgInner::add(const QString& p_tag, const PRC<XmlBehavior>& p_entity)
{
	m_map.insert(p_tag, p_entity);
}

void
MsgInner::get(const QString& p_tag, PRC<XmlBehavior>& p_entity)
{
	p_entity = m_map[p_tag];
}

bool
MsgInner::exist(const QString& p_tag)
{
	return m_map.contains(p_tag);
}

void
MsgInner::writeXml(QDomNode& p_node) const
{
	QMap<QString, PRC<XmlBehavior> >::const_iterator iter;

	for(iter = m_map.begin(); iter != m_map.end(); iter++)
		iter.value()->to(p_node, iter.key());

	addAttribute(p_node, "id", QString::number(m_id));
	addAttribute(p_node, "name", m_name);
	addAttribute(p_node, "type", QString::number(m_type));
}
