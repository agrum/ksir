#include "kmsg.h"

unsigned int kMsgHeader::m_idCount = 0;
QMutex kMsgHeader::m_mutex;

kMsg::kMsg(const QString& p_name, Type p_type) :
	m_name(p_name),
	m_type(p_type)
{
	m_mutex.lock();
		m_id = m_idCount++;
	m_mutex.unlock();
}

kMsg::kMsg(const QDomNode& p_node)
{
	m_id = getAttribute(p_node, "id");
	m_name = getAttribute(p_node, "name");
	m_type = getAttribute(p_node, "type");
}

kMsg::kMsg(const kMsg& p_info) :
	m_id(p_info.m_id),
	m_name(p_info.m_name),
	m_type(p_info.m_type)
{

}
