#include "msg.h"

using namespace ksir;

unsigned int Msg::m_idCount = 0;
QMutex Msg::m_mutex;

Msg::Msg(const QString& p_name, Type p_type) :
	XmlBehavior("Msg_" + p_name),
	m_name(p_name),
	m_type(p_type)
{
	m_mutex.lock();
		m_id = m_idCount++;
	m_mutex.unlock();
}

Msg::Msg(const QDomNode& p_node) :
	XmlBehavior("Msg_" + getAttribute(p_node, "name"))
{
	m_id = getAttribute(p_node, "id").toInt();
	m_name = getAttribute(p_node, "name");
	m_type = (Type) getAttribute(p_node, "type").toInt();
}

Msg::Msg(const Msg& p_info) :
	XmlBehavior("Msg_" + p_info.m_name),
	m_id(p_info.m_id),
	m_name(p_info.m_name),
	m_type(p_info.m_type)
{

}
