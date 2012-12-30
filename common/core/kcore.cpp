#include "kcore.h"

kCore::kCore()
{

}

kCore::kCore(const QDomNode& p_root):
	kXmlBehavior(p_root)
{

}

kCore::kCore(const kCore& p_core):
	kXmlBehavior(),
	m_id(p_core.m_id),
	m_type(p_core.m_type),
	m_addr(p_core.m_addr)
{

}

kCore& kCore::operator=(const kCore& p_core)
{
	m_id = p_core.m_id;
	m_type = p_core.m_type;
	m_addr = p_core.m_addr;

	return *this;
}

bool kCore::operator==(const kCore& p_core) const
{
	return (m_id == p_core.m_id && m_type == p_core.m_type);
}

void kCore::readXml(const QString& p_tag, const QDomElement& p_node)
{
	if( p_tag == XML_ID )
		m_id = p_node.text();
	else if( p_tag == XML_TYPE )
		m_type = p_node.text();
	else if( p_tag == XML_ADDR )
		m_addr = p_node.text();
}

void kCore::writeXml(QDomNode& p_tag)
{
	addToElement(p_tag, XML_ID, m_id);
	addToElement(p_tag, XML_TYPE, m_type);
	addToElement(p_tag, XML_ADDR, m_addr);
}
